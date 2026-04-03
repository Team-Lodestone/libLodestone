/** @file InfdevWorldIo.cpp
*
* @author Zero_DSRS_VX
* @date 3/29/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#include "Lodestone.Minecraft.Java/conversion/infdev/InfdevWorldIo.h"

#include <fstream>

#include "libnbt++/io/izlibstream.h"
#include "libnbt++/io/stream_reader.h"
#include <libnbt++/nbt_tags.h>

#include "Lodestone.Level/world/World.h"
#include "Lodestone.Minecraft.Java/conversion/infdev/InfdevZoneIo.h"
#include "Lodestone.Minecraft.Java/infdev/InfdevWorld.h"
#include "Lodestone.Minecraft.Java/infdev/InfdevZone.h"

namespace lodestone::minecraft::java::infdev::world {
    std::unique_ptr<level::world::World> InfdevWorldIo::read(
        const common::conversion::io::options::OptionPresets::CommonFilesystemOptions &options) const {

        if (!std::filesystem::exists(options.path))
            return nullptr;

        level::types::Vec3i spawnPos = {0, 64, 0};
        auto world = std::make_unique<level::world::World>();
        if (std::filesystem::exists(options.path / "level.dat")) {
            std::ifstream dat(options.path / "level.dat", std::ios::binary);
            zlib::izlibstream strm(dat);

            nbt::io::stream_reader nbt(strm);
            auto [nm, tag] = nbt.read_compound();

            nbt::tag_compound &data =
                (tag.get()->at("Data").as<nbt::tag_compound>());

            std::string name = options.path.filename().string();
            auto w = std::make_unique<InfdevWorld>(name);

            // todo handle player tag

            int spawnX = data["SpawnX"].get().as<nbt::tag_int>();
            int spawnY = data["SpawnY"].get().as<nbt::tag_int>();
            int spawnZ = data["SpawnZ"].get().as<nbt::tag_int>();
            spawnPos = {spawnX, spawnY, spawnZ};

            int64_t time = data["Time"].get().as<nbt::tag_long>();
            int64_t seed = data["RandomSeed"].get().as<nbt::tag_long>();
            int64_t lastPlayed = data["LastPlayed"].get().as<nbt::tag_long>();

            auto d = new common::world::data::LevelData{seed, lastPlayed, time};

            d->time = time;
            d->seed = seed;
            d->lastPlayed = lastPlayed;

            LOG_DEBUG(w->toString());
            world = std::move(w);
            dat.close();
        }

        const zone::InfdevZoneIo *io = this->getAsByRelation<const zone::InfdevZoneIo, &conversion::identifiers::LEVEL_IO>();

        auto pth = options.path / "data";
        for (std::filesystem::recursive_directory_iterator it{pth}, end{};
     it != end; ++it) {
            const std::filesystem::path file = it->path();

            // TODO: Read entities_x_z.dat
            if (file.filename().string().starts_with("entities_")) {

            }

            // Read zones_x_z.dat
            if (file.filename().string().starts_with("zone_")) {
                if (file.extension() != ".dat") continue;

                level::types::Vec2i coords = zone::InfdevZone::getCoordsFromFilename(file.filename().string());

                std::ifstream ifs(file, std::ifstream::binary);

                std::unique_ptr<level::Level> level =
                    io->read(common::conversion::io::options::OptionPresets::CommonChunkReadOptions {
                        common::conversion::io::options::ChunkOptions {
                            coords
                        },
                        common::conversion::io::options::OptionPresets::CommonReadOptions {
                            conversion::io::options::fs::file::FileReaderOptions {
                                ifs
                            },
                            conversion::io::options::versioned::VersionedOptions {
                                options.version
                            }
                        }
                    });

                auto defaultLevel = world->getDefaultLevel();
                if (!defaultLevel) {
                    world->addLevel(level::world::World::Dimension::OVERWORLD, std::move(level));
                } else {
                    defaultLevel->merge(std::move(level));
                }
            }
     }

        return world;
    }

    void InfdevWorldIo::write(level::world::World *w,
                              const common::conversion::io::options::OptionPresets::CommonFilesystemOptions &options) const {
        throw new std::runtime_error("Not implemented");
    }
}
