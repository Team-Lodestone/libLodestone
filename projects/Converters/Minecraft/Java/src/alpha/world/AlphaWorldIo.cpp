//
// Created by Zero on 11/20/25.
//

#include "Lodestone.Minecraft.Java/alpha/world/AlphaWorldIo.h"

#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/alpha/player/AlphaPlayerIo.h"
#include "Lodestone.Minecraft.Java/alpha/world/AlphaWorld.h"
#include "Lodestone.Minecraft.Java/mcr/chunk/McRegionChunk.h"
#include "Lodestone.Minecraft.Java/mcr/chunk/McRegionChunkIo.h"
#include "Lodestone.Minecraft.Java/mcr/player/McRegionPlayer.h"
#include "Lodestone.Minecraft.Java/mcr/player/McRegionPlayerIo.h"
#include <Lodestone.Common/Logging.h>
#include <Lodestone.Conversion/Identifiers.h>
#include <Lodestone.Conversion/chunk/ChunkIORegistry.h>
#include <Lodestone.Conversion/player/PlayerIORegistry.h>

#include <libnbt++/io/izlibstream.h>
#include <libnbt++/io/stream_reader.h>
#include <libnbt++/nbt_tags.h>

#include <fstream>
#include <iostream>

namespace lodestone::minecraft::java::alpha::world {
    const lodestone::conversion::level::PlayerIO *
    AlphaWorldIo::getLevelIO(int version) const {
        return nullptr;
    }

    std::unique_ptr<lodestone::level::world::World> AlphaWorldIo::read(
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
            const java::alpha::player::AlphaPlayerIO *pio = static_cast<
                const java::alpha::player::AlphaPlayerIO *>(
                lodestone::conversion::player::PlayerIORegistry::getInstance()
                    .getPlayerIO(java::identifiers::ALPHA));
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
        const mcr::chunk::McRegionChunkIO *chunkIo =
            dynamic_cast<const mcr::chunk::McRegionChunkIO *>(
                conversion::chunk::ChunkIORegistry::getInstance().getChunkIO(
                    java::identifiers::MCREGION));
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

                std::unique_ptr<mcr::chunk::McRegionChunk> c = CAST_UNIQUE_PTR(
                    mcr::chunk::McRegionChunk, chunkIo->read(strm, version));

                LOG_DEBUG(file.string());
                LOG_DEBUG(c->toString());
                dim->addChunk(c->getCoords().value(), std::move(c));
                ifs.close();
            }

            lodestone::common::registry::Identifier d =
                mcr::player::McRegionPlayer::dimensionIdToIdentifier(id);
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
            const mcr::player::McRegionPlayer *p =
                dynamic_cast<mcr::player::McRegionPlayer *>(plr.get());
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
        const std::filesystem::path &path, lodestone::level::world::World *w,
        int version,
        const conversion::world::options::AbstractWorldWriteOptions &options)
        const {}

} // namespace lodestone::minecraft::java::alpha::world