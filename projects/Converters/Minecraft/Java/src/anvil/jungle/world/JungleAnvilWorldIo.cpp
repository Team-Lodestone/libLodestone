//
// Created by Zero on 11/26/25.
//

#include "Lodestone.Minecraft.Java/anvil/jungle/world/JungleAnvilWorldIo.h"

#include <Lodestone.Conversion/chunk/ChunkIORegistry.h>

#include <libnbt++/io/ozlibstream.h>

#include <Lodestone.Common/util/Logging.h>
#include <Lodestone.Conversion/player/PlayerIORegistry.h>
#include <Lodestone.Conversion/region/RegionIORegistry.h>
#include <Lodestone.Level/region/Region.h>

#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/anvil/jungle/chunk/JungleAnvilChunkIo.h"
#include "Lodestone.Minecraft.Java/anvil/jungle/region/JungleAnvilRegionIo.h"
#include "Lodestone.Minecraft.Java/anvil/jungle/world/JungleAnvilWorld.h"
#include "Lodestone.Minecraft.Java/mcregion/player/McRegionPlayer.h"
#include "Lodestone.Minecraft.Java/mcregion/player/McRegionPlayerIo.h"
#include "Lodestone.Minecraft.Java/mcregion/region/McRegionRegion.h"
#include "Lodestone.Minecraft.Java/mcregion/region/McRegionRegionIo.h"
#include <libnbt++/io/izlibstream.h>
#include <libnbt++/io/stream_reader.h>
#include <libnbt++/nbt_tags.h>

#include <Lodestone.Conversion/level/LevelIORegistry.h>
#include <fstream>
#include <iostream>

namespace lodestone::minecraft::java::anvil::jungle::world {
    const conversion::level::LevelIO *
    JungleAnvilWorldIo::getLevelIO(int version) const {
        return conversion::level::LevelIoRegistry::getInstance().getLevelIO(
            identifiers::ANVIL_JUNGLE);
    }

    std::unique_ptr<level::world::World> JungleAnvilWorldIo::read(
        const std::filesystem::path &path, int version,
        const conversion::world::options::AbstractWorldReadOptions &options)
        const {
        if (!std::filesystem::exists(path))
            return nullptr;

        map_t<int, std::filesystem::path> dims;
        dims.emplace(0, path); // main dim

        // scan for dims
        for (auto &d : std::filesystem::directory_iterator(path)) {
            const std::string name = d.path().filename().string();

            if (!d.is_directory() || !name.starts_with("DIM"))
                continue;

            const std::string nm =
                name.substr(3, name.size() - 3); // remove dim

            int i = std::stoi(nm);
            dims.emplace(i, d.path());
        }

        level::types::Vec3i spawnPos = {0, 64, 0};
        std::unique_ptr<level::world::World> world =
            std::make_unique<level::world::World>();
        if (std::filesystem::exists(path / "level.dat")) {
            // TODO we can get DataVersion later and check for fields depending
            // on it another way is to just try to get fields and if they dont
            // exist then Too Bad.

            std::ifstream dat(path / "level.dat", std::ios::binary);
            zlib::izlibstream strm(dat);

            nbt::io::stream_reader nbt(strm);
            auto [nm, tag] = nbt.read_compound();

            nbt::tag_compound &data =
                (tag.get()->at("Data").as<nbt::tag_compound>());

            std::string name = data["LevelName"].get().as<nbt::tag_string>();
            std::unique_ptr<JungleAnvilWorld> w =
                std::make_unique<JungleAnvilWorld>(name);

            // todo handle player tag

            int spawnX = data["SpawnX"].get().as<nbt::tag_int>();
            int spawnY = data["SpawnY"].get().as<nbt::tag_int>();
            int spawnZ = data["SpawnZ"].get().as<nbt::tag_int>();
            spawnPos = {spawnX, spawnY, spawnZ};

            int64_t time = data["Time"].get().as<nbt::tag_long>();
            w->setTime(time);

            int rainTime = data["rainTime"].get().as<nbt::tag_int>();
            int thunderTime = data["thunderTime"].get().as<nbt::tag_int>();

            w->setRainTime(rainTime);
            w->setThunderTime(thunderTime);

            bool raining = data["raining"].get().as<nbt::tag_byte>();
            bool thundering = data["thundering"].get().as<nbt::tag_byte>();

            w->setIsRaining(raining);
            w->setIsThundering(thundering);

            int64_t seed = data["RandomSeed"].get().as<nbt::tag_long>();
            w->setSeed(seed);

            int ver = data["version"].get().as<nbt::tag_int>();
            w->setVersion(ver);

            int64_t lastPlayed = data["LastPlayed"].get().as<nbt::tag_long>();
            w->setLastPlayed(lastPlayed);

            LOG_DEBUG(w->toString());
            world = std::move(w);
            dat.close();
        }

        if (std::filesystem::exists(path / "players") &&
            std::filesystem::is_directory(path / "players")) {
            auto pio = static_cast<const mcregion::player::McRegionPlayerIO *>(
                getPlayerIO(version));
            for (const auto &f :
                 std::filesystem::directory_iterator(path / "players")) {
                if (!std::filesystem::is_regular_file(f))
                    continue;

                std::ifstream ifs(f.path(), std::ifstream::binary);
                zlib::izlibstream strm(ifs);

                nbt::io::stream_reader nbt(strm);
                auto [nm, root] = nbt.read_compound();

                std::unique_ptr<level::entity::Player> r =
                    pio->read(f, *root, version); // todo return value?

                LOG_DEBUG(r->toString());

                world->addPlayer(std::move(r), false);
                ifs.close();
            }
        }

        auto *io = static_cast<const region::JungleAnvilRegionIO *>(
            getRegionIO(version));

        int t = 2;
        // do I need to call exists?
        for (auto [id, pth] : dims) {
            if (std::filesystem::exists(pth / "region") &&
                std::filesystem::is_directory(pth / "region")) {

                LOG_DEBUG(pth);

                level::Level *dim = new level::Level();
#ifdef USE_OPENMP
                std::vector<std::filesystem::directory_entry> e;
                for (auto &f :
                     std::filesystem::directory_iterator(pth / "region"))
                    e.push_back(f);

#pragma omp parallel for
                for (size_t i = 0; i < e.size(); ++i) {
                    const auto &f = e[i];
#else
                for (const auto &f :
                     std::filesystem::directory_iterator(pth / "region")) {
#endif
                    if (!std::filesystem::is_regular_file(f) ||
                        f.path().extension() != ".mca")
                        continue;

                    level::types::Vec2i coords =
                        mcregion::region::McRegionRegion::getCoordsFromFilename(
                            f.path().filename().string());

                    std::ifstream ifs(f.path(), std::ifstream::binary);

                    std::unique_ptr<level::region::Region> r =
                        io->read(ifs, version, coords); // todo return value?

                    LOG_DEBUG(r->toString());

                    dim->merge(std::move(r));
                    ifs.close();
                }

                dim->setSpawnPos(
                    spawnPos); // in beta, only worlds have the spawn position
                // get dim (or temp name if conversion unknown)
                lodestone::common::registry::Identifier d =
                    mcregion::player::McRegionPlayer::dimensionIdToIdentifier(
                        id);
                if (d == level::world::World::Dimension::UNKNOWN)
                    d = lodestone::common::registry::Identifier(
                        "lodestone",
                        ("unknown_dim_" + std::to_string(t)).c_str());

                world->addLevel(
                    d, std::unique_ptr<level::Level>(
                           dim)); // todo move dimension id shit to world
            }
            t++;
        }

        // move players to correct level otherwise they're stuck at correct
        // coords in diff level
        for (const auto &[name, plr] : world->getPlayers()) {
            const mcregion::player::McRegionPlayer *p =
                dynamic_cast<mcregion::player::McRegionPlayer *>(plr.get());
            if (!p)
                continue;

            if (world->hasLevel(p->getDimension()))
                world->movePlayerToLevel(name, p->getDimension(), false);
        }

        return world;
    }

    void JungleAnvilWorldIo::write(
        const std::filesystem::path &path, level::world::World *w, int version,
        const conversion::world::options::AbstractWorldWriteOptions &options)
        const {
        if (!exists(path))
            std::filesystem::create_directories(path);
        if (!std::filesystem::is_directory(path))
            throw std::runtime_error(
                "Cannot write a world to a path that is not a directory");

        {
            // Leveldat
            // TODO incomplete
            std::ofstream dat(path / "level.dat", std::ios::binary);
            zlib::ozlibstream strm(dat, Z_DEFAULT_COMPRESSION, true);

            nbt::io::stream_writer nbt(strm);
            nbt::tag_compound root{};

            nbt::tag_compound data{};

            data["LevelName"] = w->getName();
            // TODO we need to figure out what fields were added in what
            // versions and read them accordingly.

            // int spawnX = data["SpawnX"].get().as<nbt::tag_int>();
            // int spawnY = data["SpawnY"].get().as<nbt::tag_int>();
            // int spawnZ = data["SpawnZ"].get().as<nbt::tag_int>();
            // spawnPos = {spawnX, spawnY, spawnZ};
            //
            // int64_t time = data["Time"].get().as<nbt::tag_long>();
            // w->setTime(time);
            //
            // int rainTime = data["rainTime"].get().as<nbt::tag_int>();
            // int thunderTime = data["thunderTime"].get().as<nbt::tag_int>();
            //
            // w->setRainTime(rainTime);
            // w->setThunderTime(thunderTime);
            //
            // bool raining = data["raining"].get().as<nbt::tag_byte>();
            // bool thundering = data["thundering"].get().as<nbt::tag_byte>();
            //
            // w->setIsRaining(raining);
            // w->setIsThundering(thundering);
            //
            // int64_t seed = data["RandomSeed"].get().as<nbt::tag_long>();
            // w->setSeed(seed);
            //
            // int ver = data["version"].get().as<nbt::tag_int>();
            // w->setVersion(ver);
            //
            // int64_t lastPlayed =
            // data["LastPlayed"].get().as<nbt::tag_long>();
            // w->setLastPlayed(lastPlayed);
            //
            // int64_t size = data["SizeOnDisk"].get().as<nbt::tag_long>();
            // w->setSize(size);

            root.emplace<nbt::tag_compound>("Data", data);
            nbt.write_tag("", root);
        }
        // Regions
        auto *io =
            static_cast<const anvil::jungle::region::JungleAnvilRegionIO *>(
                getRegionIO(version));

        std::filesystem::path p = path;

        int i = 2; // for writing other dims
        for (auto &[id, lvl] : w->getLevels()) {
            if (const int dim =
                    mcregion::player::McRegionPlayer::identifierToDimensionId(
                        id);
                dim != 0) {
                const int d = dim == 0x7FFFFFFF ? i : dim;
                p = path / ("DIM" + std::to_string(d));
            }
            i++;

            std::filesystem::path r = p / "region";
            if (!std::filesystem::exists(r))
                std::filesystem::create_directory(r);

            level::types::Bounds3i bounds = lvl->getChunkBounds();

            for (int rx = bounds.min.x; rx < bounds.max.x; rx += 32 * 32) {
                for (int rz = bounds.min.z; rz < bounds.max.z; rz += 32 * 32) {
                    std::ofstream o(r / ("r." + std::to_string(rx) + "." +
                                         std::to_string(rz) + ".mcr"));

                    io->write(lvl.get(), version, {rx, rz}, o);

                    o.close();
                }
            }
        }

        // TODO player data
        // TODO settings class for readers & writers, lets us pass a default
        // player to put in level.dat too!
        // TODO for block states we might be able to make registry that maps
        // fields to bits in data byte per block
    }
    const conversion::chunk::ChunkIO *
    JungleAnvilWorldIo::getChunkIO(int version) const {
        return static_cast<const chunk::JungleAnvilChunkIO *>(
            conversion::chunk::ChunkIORegistry::getInstance().getChunkIO(
                identifiers::ANVIL_JUNGLE));
    }

    const conversion::region::RegionIO *
    JungleAnvilWorldIo::getRegionIO(int version) const {
        return static_cast<const region::JungleAnvilRegionIO *>(
            conversion::region::RegionIORegistry::getInstance().getRegionIO(
                identifiers::ANVIL_JUNGLE));
    }

    const conversion::player::PlayerIO *
    JungleAnvilWorldIo::getPlayerIO(int version) const {
        return static_cast<const mcregion::player::McRegionPlayerIO *>(
            conversion::player::PlayerIORegistry::getInstance().getPlayerIO(
                identifiers::ANVIL_JUNGLE));
    }

} // namespace lodestone::minecraft::java::anvil::jungle::world