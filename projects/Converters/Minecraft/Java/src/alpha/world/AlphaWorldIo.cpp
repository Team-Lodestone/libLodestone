//
// Created by Zero on 11/20/25.
//

#include "Lodestone.Minecraft.Java/alpha/world/AlphaWorldIo.h"

#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/alpha/player/AlphaPlayerIo.h"
#include "Lodestone.Minecraft.Java/alpha/world/AlphaWorld.h"
#include "Lodestone.Minecraft.Java/mcregion/chunk/McRegionChunk.h"
#include "Lodestone.Minecraft.Java/mcregion/chunk/McRegionChunkIo.h"
#include "Lodestone.Minecraft.Java/mcregion/player/McRegionPlayer.h"
#include <libnbt++/io/ozlibstream.h>

#include <Lodestone.Common/util/Logging.h>
#include <Lodestone.Common/util/Math.h>
#include <Lodestone.Conversion/chunk/ChunkIORegistry.h>
#include <Lodestone.Conversion/player/PlayerIORegistry.h>

#include <libnbt++/io/izlibstream.h>
#include <libnbt++/io/stream_reader.h>
#include <libnbt++/nbt_tags.h>

#include <fstream>
#include <iostream>

namespace lodestone::minecraft::java::alpha::world {
    const conversion::level::LevelIO *
    AlphaWorldIo::getLevelIO(int version) const {
        return nullptr;
    }

    std::unique_ptr<level::world::World> AlphaWorldIo::read(
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
            std::ifstream dat(path / "level.dat", std::ios::binary);
            zlib::izlibstream strm(dat);

            nbt::io::stream_reader nbt(strm);
            auto [nm, tag] = nbt.read_compound();

            nbt::tag_compound &data =
                (tag.get()->at("Data").as<nbt::tag_compound>());

            std::string name = path.filename().string();
            std::unique_ptr<AlphaWorld> w = std::make_unique<AlphaWorld>(name);

            // todo handle player tag

            int spawnX = data["SpawnX"].get().as<nbt::tag_int>();
            int spawnY = data["SpawnY"].get().as<nbt::tag_int>();
            int spawnZ = data["SpawnZ"].get().as<nbt::tag_int>();
            spawnPos = {spawnX, spawnY, spawnZ};

            int64_t time = data["Time"].get().as<nbt::tag_long>();
            w->setTime(time);

            int64_t seed = data["RandomSeed"].get().as<nbt::tag_long>();
            w->setSeed(seed);

            int64_t lastPlayed = data["LastPlayed"].get().as<nbt::tag_long>();
            w->setLastPlayed(lastPlayed);

            LOG_DEBUG(w->toString());
            world = std::move(w);
            dat.close();
        }

        if (std::filesystem::exists(path / "players") &&
            std::filesystem::is_directory(path / "players")) {
            const player::AlphaPlayerIO *pio =
                static_cast<const player::AlphaPlayerIO *>(
                    conversion::player::PlayerIORegistry::getInstance()
                        .getPlayerIO(identifiers::ALPHA));
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

        int t = 2;
        const mcregion::chunk::McRegionChunkIO *chunkIo =
            dynamic_cast<const mcregion::chunk::McRegionChunkIO *>(
                conversion::chunk::ChunkIORegistry::getInstance().getChunkIO(
                    identifiers::MCREGION));
        for (auto [id, pth] : dims) {
            level::Level *dim = new level::Level();
            LOG_DEBUG("Reading " << dim->toString());

            for (std::filesystem::recursive_directory_iterator it{pth}, end{};
                 it != end; ++it) {
                const std::filesystem::path file = it->path();

                // Skip dimensions
                if (it->is_directory() &&
                    file.filename().string().starts_with("DIM-")) {
                    it.disable_recursion_pending();
                }

                if (!file.filename().string().starts_with("c.") ||
                    file.extension() != ".dat" || !is_regular_file(file))
                    continue;

                std::ifstream ifs(file, std::ifstream::binary);
                zlib::izlibstream strm(ifs);

                std::unique_ptr<mcregion::chunk::McRegionChunk> c =
                    CAST_UNIQUE_PTR(mcregion::chunk::McRegionChunk,
                                    chunkIo->read(strm, version));

                LOG_DEBUG(file.string());
                LOG_DEBUG(c->toString());
                dim->addChunk(c->getCoords().value(), std::move(c));
                ifs.close();
            }

            lodestone::common::registry::Identifier d =
                mcregion::player::McRegionPlayer::dimensionIdToIdentifier(id);
            if (d == level::world::World::Dimension::UNKNOWN)
                d = lodestone::common::registry::Identifier(
                    "lodestone", ("unknown_dim_" + std::to_string(t)).c_str());
            world->addLevel(d,
                            std::unique_ptr<level::Level>(
                                dim)); // todo move dimension id shit to world

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

        if (auto lvl = world->getDefaultLevel())
            lvl->setSpawnPos(spawnPos);

        return world;
    }
    void AlphaWorldIo::write(
        const std::filesystem::path &path, level::world::World *w, int version,
        const conversion::world::options::AbstractWorldWriteOptions &options)
        const {

        if (!std::filesystem::exists(path)) {
            std::filesystem::create_directories(path);
        }

        // Create level.dat
        {
            std::ofstream ofs(path / "level.dat", std::ifstream::binary);
            zlib::ozlibstream strm(ofs, Z_DEFAULT_COMPRESSION, true);

            nbt::io::stream_writer writer(strm);
            nbt::tag_compound root{};
            nbt::tag_compound data{};

            // Not the cleanest solution, but it definitely works.
            auto lastPlayed = w->getProperty("lastPlayed");
            data["LastPlayed"] =
                lastPlayed
                    ? lastPlayed
                          ->as<
                              level::properties::TemplatedProperty<int64_t &>>()
                          ->getValue()
                    : static_cast<int64_t>(0);

            auto seed = w->getProperty("seed");
            data["RandomSeed"] =
                seed
                    ? seed->as<
                              level::properties::TemplatedProperty<int64_t &>>()
                          ->getValue()
                    : static_cast<int64_t>(0);

            // TODO: Write default player tag here

            level::types::Vec3i sp = w->getDefaultLevel()->getSpawnPos();
            data["SpawnX"] = sp.x;
            data["SpawnY"] = sp.y;
            data["SpawnZ"] = sp.z;

            auto time = w->getProperty("time");
            data["Time"] =
                time
                    ? time->as<
                              level::properties::TemplatedProperty<int64_t &>>()
                          ->getValue()
                    : static_cast<int64_t>(0);

            data["SizeOnDisk"] = static_cast<int64_t>(0);

            root["Data"] = std::move(data);
            writer.write_tag("", root);
        }

        // Create chunk folders and output chunks (base36)
        const java::mcregion::chunk::McRegionChunkIO *io =
            static_cast<const java::mcregion::chunk::McRegionChunkIO *>(
                lodestone::conversion::chunk::ChunkIORegistry::getInstance()
                    .getChunkIO(java::identifiers::MCREGION));

        std::filesystem::path p = path;

        int i = 2; // for writing other dims
        for (auto &[id, lvl] : w->getLevels()) {
            if (const int dim =
                    mcregion::player::McRegionPlayer::identifierToDimensionId(
                        id);
                dim != 0) {
                const int d = dim == 0x7FFFFFFF ? i : dim;
                if (d != 0)
                    p = path / ("DIM" + std::to_string(d));
            }
            i++;

            // loop over level chunks here
            for (auto &[coords, chunk] : lvl->getChunks()) {
                int tX = coords.x;
                int tZ = coords.z;

                std::string fX = lodestone::common::util::Math::base36(tX & 63);
                std::string fZ = lodestone::common::util::Math::base36(tZ & 63);

                std::filesystem::path chunkOut = p / fX / fZ;
                if (!std::filesystem::exists(chunkOut)) {
                    std::filesystem::create_directories(chunkOut);
                }

                std::string cX = lodestone::common::util::Math::base36(tX);
                std::string cZ = lodestone::common::util::Math::base36(tZ);

                std::string cf = "c." + cX + "." + cZ + ".dat";
                std::ofstream ofs(chunkOut / cf, std::ofstream::binary);
                zlib::ozlibstream ozs(ofs, Z_DEFAULT_COMPRESSION, true);
                io->write(chunk.get(), coords, version, ozs);
            }
        }
    }
    const conversion::chunk::ChunkIO *
    AlphaWorldIo::getChunkIO(int version) const {
        return static_cast<const mcregion::chunk::McRegionChunkIO *>(
            conversion::chunk::ChunkIORegistry::getInstance().getChunkIO(
                identifiers::MCREGION));
    }

    const conversion::region::RegionIO *
    AlphaWorldIo::getRegionIO(int version) const {
        return nullptr;
    }

    const conversion::player::PlayerIO *
    AlphaWorldIo::getPlayerIO(int version) const {
        return static_cast<const player::AlphaPlayerIO *>(
            conversion::player::PlayerIORegistry::getInstance().getPlayerIO(
                identifiers::ALPHA));
    }

} // namespace lodestone::minecraft::java::alpha::world