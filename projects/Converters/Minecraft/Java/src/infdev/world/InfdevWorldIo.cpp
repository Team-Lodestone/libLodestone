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

#include <libnbt++/io/izlibstream.h>
#include <libnbt++/io/stream_reader.h>
#include <libnbt++/nbt_tags.h>

#include <Lodestone.Level/world/World.h>

#include <libnbt++/io/ozlibstream.h>

#include "Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilChunkIo.h"
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
        if (!std::filesystem::exists(options.path)) {
            std::filesystem::create_directories(options.path);
        }

        // Create level.dat
        {
            std::ofstream ofs(options.path / "level.dat", std::ifstream::binary);
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
                              level::properties::TemplatedProperty<int64_t>>()
                          ->getValue()
                    : static_cast<int64_t>(0);

            auto seed = w->getProperty("seed");
            data["RandomSeed"] =
                seed
                    ? seed->as<
                              level::properties::TemplatedProperty<int64_t>>()
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
                              level::properties::TemplatedProperty<int64_t>>()
                          ->getValue()
                    : static_cast<int64_t>(0);

            data["SizeOnDisk"] = static_cast<int64_t>(0);

            root["Data"] = std::move(data);
            writer.write_tag("", root);
        }

        // Write zones out
        const zone::InfdevZoneIo *io = this->getAsByRelation<const zone::InfdevZoneIo, &conversion::identifiers::LEVEL_IO>();

        std::filesystem::path p = options.path;

        std::filesystem::path dataDir = p / "data";
        if (!std::filesystem::exists(dataDir))
            std::filesystem::create_directory(dataDir);


        auto lvl = w->getDefaultLevel();
        level::types::Bounds3i bounds = lvl->getChunkBounds();

        for (int cX = 0; cX = bounds.min.x / chunk::InfdevChunkIO::CHUNK_WIDTH; cX++) {

        }

        for (int rx = bounds.min.x >> 5; rx <= bounds.max.x >> 5; rx++) {
            for (int rz = bounds.min.z >> 5; rz <= bounds.max.z >> 5; rz++) {
                auto zoneX = lodestone::common::util::Math::encodeBase36(rx);
                auto zoneZ = lodestone::common::util::Math::encodeBase36(rz);
                std::ofstream o(dataDir / ("zone_" + zoneX + "_" +
                                     zoneZ + ".dat"));

                io->write(lvl, common::conversion::io::options::OptionPresets::CommonChunkWriteOptions {
                              common::conversion::io::options::ChunkOptions {
                                      {rx, rz}
                              },
                              common::conversion::io::options::OptionPresets::CommonWriteOptions {
                                  conversion::io::options::fs::file::FileWriterOptions {
                                      o
                                  },
                                  conversion::io::options::versioned::VersionedOptions {
                                  options.version
                                  }
                              }
                });

                o.close();
            }
        }
    }
}
