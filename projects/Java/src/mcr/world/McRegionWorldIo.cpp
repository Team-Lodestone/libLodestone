//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#include "Lodestone.Java/mcr/world/McRegionWorldIo.h"

#include <fstream>
#include <iostream>

#include "Lodestone.Java/mcr/world/McRegionWorld.h"
#include <libnbt++/io/izlibstream.h>
#include <libnbt++/io/stream_reader.h>
#include <libnbt++/nbt_tags.h>
#include <Lodestone.Level/conversion/level/LevelIORegistry.h>
#include "Lodestone.Java/Identifiers.h"
#include <Lodestone.Level/conversion/region/RegionIORegistry.h>
#include "Lodestone.Java/mcr/chunk/McRegionChunk.h"
#include "Lodestone.Java/mcr/region/McRegionRegion.h"
#include "Lodestone.Java/mcr/region/McRegionRegionIo.h"

namespace lodestone::java::mcr::world {
    const lodestone::level::conversion::level::LevelIO * McRegionWorldIo::getLevelIO(int version) const {
        return level::conversion::level::LevelIORegistry::sInstance.getLevelIO(identifiers::MCREGION);
    }

    std::unique_ptr<lodestone::level::world::World> McRegionWorldIo::read(const std::filesystem::path &path, int version) const {
        if (!std::filesystem::exists(path)) return nullptr;

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
            w->setSpawnPos({spawnX, spawnY, spawnZ});

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


        const java::mcr::region::McRegionRegionIO *io = static_cast<const java::mcr::region::McRegionRegionIO *>(level::conversion::region::RegionIORegistry::sInstance.
            getRegionIO(java::identifiers::MCREGION));

        // do I need to call exists?
        if (std::filesystem::exists(path / "region") && std::filesystem::is_directory(path / "region")) {
            level::Level *overworld = new level::Level();
            for (const auto& f : std::filesystem::directory_iterator(path / "region")) {
                if (!std::filesystem::is_regular_file(f)) continue;

                level::types::Vec2i coords = region::McRegionRegion::getCoordsFromFilename(f.path().filename());

                std::ifstream ifs(f.path(), std::ifstream::binary);

                std::vector<uint8_t> mcr(f.file_size());
                ifs.read(reinterpret_cast<char *>(mcr.data()), mcr.size());

                std::unique_ptr<level::region::Region> r = io->read(mcr.data(), mcr.size(), version, coords); // todo return value?

                overworld->merge(std::move(r));
                ifs.close();

                std::cout << coords << std::endl;
            }

            world->addLevel(level::world::World::Dimension::OVERWORLD, std::unique_ptr<level::Level>(overworld));
        }

        return world;
    }

    void McRegionWorldIo::write(const std::filesystem::path &path, lodestone::level::world::World *w,
        int version) const {
    }
}
