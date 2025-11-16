//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#include "Lodestone.Java/mcr/world/McRegionWorldIo.h"

#include <fstream>
#include <iostream>
#include <ranges>

#include "Lodestone.Java/mcr/world/McRegionWorld.h"
#include <libnbt++/io/izlibstream.h>
#include <libnbt++/io/stream_reader.h>
#include <libnbt++/nbt_tags.h>
#include <Lodestone.Conversion/level/LevelIORegistry.h>
#include "Lodestone.Java/Identifiers.h"
#include <Lodestone.Conversion/region/RegionIORegistry.h>

#include <Lodestone.Conversion/player/PlayerIORegistry.h>
#include "Lodestone.Java/mcr/chunk/McRegionChunk.h"
#include "Lodestone.Java/mcr/region/McRegionRegion.h"
#include "Lodestone.Java/mcr/region/McRegionRegionIo.h"
#include "Lodestone.Java/mcr/player/McRegionPlayerIo.h"
#include "Lodestone.Java/mcr/player/McRegionPlayer.h"

namespace lodestone::java::mcr::world {
    const lodestone::conversion::level::PlayerIO * McRegionWorldIo::getLevelIO(int version) const {
        return lodestone::conversion::level::PlayerIORegistry::sInstance.getLevelIO(identifiers::MCREGION);
    }

    std::unique_ptr<lodestone::level::world::World> McRegionWorldIo::read(const std::filesystem::path &path, int version) const {
        if (!std::filesystem::exists(path)) return nullptr;

        level::types::Vec3i spawnPos = {0, 64, 0};
        std::unique_ptr<level::world::World> world = std::make_unique<level::world::World>();
        if (std::filesystem::exists(path / "level.dat")) {
            std::ifstream dat(path / "level.dat", std::ios::binary);
            zlib::izlibstream strm(dat);

            nbt::io::stream_reader nbt(strm);
            auto [nm, tag] = nbt.read_compound();

            nbt::tag_compound &data = (tag.get()->at("Data").as<nbt::tag_compound>());

            std::string name = data["LevelName"].get().as<nbt::tag_string>();
            std::unique_ptr<McRegionWorld> w = std::make_unique<McRegionWorld>(name);

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

            int64_t size = data["SizeOnDisk"].get().as<nbt::tag_long>();
            w->setSize(size);

            std::cout << w->toString() << std::endl;
            world = std::move(w);
            dat.close();
        }

        if (std::filesystem::exists(path / "players") && std::filesystem::is_directory(path / "players")) {
            const java::mcr::player::McRegionPlayerIO *pio = static_cast<const java::mcr::player::McRegionPlayerIO *>(lodestone::conversion::player::PlayerIORegistry::sInstance.getPlayerIO(java::identifiers::MCREGION));
            for (const auto& f : std::filesystem::directory_iterator(path / "players")) {
                if (!std::filesystem::is_regular_file(f)) continue;

                std::ifstream ifs(f.path(), std::ifstream::binary);
                zlib::izlibstream strm(ifs);

                nbt::io::stream_reader nbt(strm);
                auto [nm, root] = nbt.read_compound();

                std::unique_ptr<level::entity::Player> r = pio->read(f, *root, version); // todo return value?

                std::cout << r->toString() << std::endl;

                world->addPlayer(std::move(r));
                ifs.close();
            }
        }

        // do I need to call exists?
        if (std::filesystem::exists(path / "region") && std::filesystem::is_directory(path / "region")) {
            const java::mcr::region::McRegionRegionIO *io = static_cast<const java::mcr::region::McRegionRegionIO *>(lodestone::conversion::region::RegionIORegistry::sInstance.
    getRegionIO(java::identifiers::MCREGION));
            level::Level *overworld = new level::Level();
            for (const auto& f : std::filesystem::directory_iterator(path / "region")) {
                if (!std::filesystem::is_regular_file(f)) continue;

                level::types::Vec2i coords = region::McRegionRegion::getCoordsFromFilename(f.path().filename().string());

                std::ifstream ifs(f.path(), std::ifstream::binary);

                std::unique_ptr<level::region::Region> r = io->read(ifs, version, coords); // todo return value?

                overworld->merge(std::move(r));
                ifs.close();

                std::cout << coords << std::endl;
            }

            overworld->setSpawnPos(spawnPos); // in beta, only worlds have the spawn position
            world->addLevel(level::world::World::Dimension::OVERWORLD, std::unique_ptr<level::Level>(overworld));
        }

        // move players to correct level otherwise they're stuck at correct coords in diff level
        for (const auto &[name, plr]: world->getPlayers()) {
            const player::McRegionPlayer *p = dynamic_cast<player::McRegionPlayer *>(plr.get());
            if (!p) continue;

            if (world->hasLevel(p->getDimension()))
                world->movePlayerToLevel(name, p->getDimension(), false);
        }

        return world;
    }

    void McRegionWorldIo::write(const std::filesystem::path &path, lodestone::level::world::World *w,
        int version) const {
    }
}
