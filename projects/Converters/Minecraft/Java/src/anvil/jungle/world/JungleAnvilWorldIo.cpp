//
// Created by Zero on 11/26/25.
//

#include "Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilWorldIo.h"


#include <libnbt++/io/ozlibstream.h>

#include <Lodestone.Common/util/Logging.h>


#include <Lodestone.Minecraft.Common/region/Region.h>

#include "Lodestone.Minecraft.Java/LodestoneJava.h"
#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilChunkIo.h"
#include "Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilRegionIo.h"
#include "Lodestone.Minecraft.Java/anvil/jungle/JungleAnvilWorld.h"
#include "Lodestone.Minecraft.Java/mcregion/McRegionPlayer.h"
#include "Lodestone.Minecraft.Java/conversion/mcregion/McRegionPlayerIo.h"
#include "Lodestone.Minecraft.Java/mcregion/McRegionRegion.h"
#include "Lodestone.Minecraft.Java/conversion/mcregion/McRegionRegionIo.h"
#include <libnbt++/io/izlibstream.h>
#include <libnbt++/io/stream_reader.h>
#include <libnbt++/nbt_tags.h>
#include THREADING_HEADER
#include <format>

#include <fstream>
#include <iostream>

namespace lodestone::minecraft::java::anvil::jungle::world {
    std::unique_ptr<level::world::World> JungleAnvilWorldIo::read(const common::conversion::io::options::OptionPresets::CommonFilesystemOptions &options)
        const {
        if (!std::filesystem::exists(options.path))
            return nullptr;

        map_t<int, std::filesystem::path> dims;
        dims.emplace(0, options.path); // main dim

        // scan for dims
        for (auto &d : std::filesystem::directory_iterator(options.path)) {
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
        if (std::filesystem::exists(options.path / "level.dat")) {
            // TODO we can get DataVersion later and check for fields depending
            // on it another way is to just try to get fields and if they dont
            // exist then Too Bad.

            std::ifstream dat(options.path / "level.dat", std::ios::binary);
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
            int rainTime = data["rainTime"].get().as<nbt::tag_int>();
            int thunderTime = data["thunderTime"].get().as<nbt::tag_int>();
            bool raining = data["raining"].get().as<nbt::tag_byte>();
            bool thundering = data["thundering"].get().as<nbt::tag_byte>();
            int64_t seed = data["RandomSeed"].get().as<nbt::tag_long>();
            int ver = data["version"].get().as<nbt::tag_int>();
            int64_t lastPlayed = data["LastPlayed"].get().as<nbt::tag_long>();

            LOG_DEBUG(w->toString());
            world = std::move(w);
            dat.close();
        }

        if (std::filesystem::exists(options.path / "players") &&
            std::filesystem::is_directory(options.path / "players")) {

            auto pio = this->getAsByRelation<const mcregion::player::McRegionNbtPlayerIO, &identifiers::NBT_PLAYER_IO>();
            for (const auto &f :
                 std::filesystem::directory_iterator(options.path / "players")) {
                if (!std::filesystem::is_regular_file(f))
                    continue;

                std::ifstream ifs(f.path(), std::ifstream::binary);
                zlib::izlibstream strm(ifs);

                nbt::io::stream_reader nbt(strm);
                auto [nm, root] = nbt.read_compound();

                std::unique_ptr<level::entity::Player> r =
                    pio->read(common::conversion::io::options::OptionPresets::CommonNbtFilesystemReadOptions {
                        common::conversion::io::options::OptionPresets::CommonNbtReadOptions {
                            common::conversion::io::options::NbtReaderOptions {
                                *root
                            },
                            conversion::io::options::versioned::VersionedOptions {
                                options.version
                            }
                        },
                        conversion::io::options::fs::FilesystemPathOptions {
                            f
                        }
                    }); // todo return value?

                LOG_DEBUG(r->toString());

                world->addPlayer(std::move(r), false);
                ifs.close();
                 }
            }

        const region::JungleAnvilRegionIO *io = this->getAsByRelation<const region::JungleAnvilRegionIO, &lodestone::minecraft::common::identifiers::io::REGION_IO>();

        int t = 2;
        // do I need to call exists?
        for (auto [id, pth] : dims) {
            if (!std::filesystem::exists(pth / "region") ||
                !std::filesystem::is_directory(pth / "region"))
                continue;

                LOG_DEBUG(pth);

                level::Level *dim = new level::Level();
                std::vector<std::filesystem::path> paths;
                for (const auto &f : std::filesystem::directory_iterator(pth / "region")) {
                    if (!std::filesystem::is_regular_file(f) || f.path().extension() != ".mca")
                        continue;

                    paths.push_back(f);
                }

                THREADED_LOOP_START_VEC(paths, &io, &options, &dim)
                    const level::types::Vec2i coords =
                        mcregion::region::McRegionRegion::getCoordsFromFilename(
                            item.filename().string());

                    std::ifstream ifs(item, std::ifstream::binary);

                    std::unique_ptr<lodestone::minecraft::common::region::Region> r =
                        io->read(common::conversion::io::options::OptionPresets::CommonChunkReadOptions {
                            common::conversion::io::options::ChunkOptions {
                                coords
                            },
                            common::conversion::io::options::OptionPresets::CommonReadOptions {
                                lodestone::conversion::io::options::fs::file::FileReaderOptions {
                                    ifs
                                },
                                lodestone::conversion::io::options::versioned::VersionedOptions {
                                    options.version
                                }
                            }
                        }); // todo return value?

                    LOG_DEBUG(r->toString());

                    dim->merge(std::move(r));
                    ifs.close();
                THREADED_LOOP_END();

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
            t++;


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
        };

        return world;
    }

    void JungleAnvilWorldIo::write(level::world::World *w, const common::conversion::io::options::OptionPresets::CommonFilesystemOptions &options)
        const {
                if (!std::filesystem::exists(options.path))
            std::filesystem::create_directories(options.path);
        if (!std::filesystem::is_directory(options.path))
            throw std::runtime_error(
                "Cannot write a world to a path that is not a directory");

        {
            // Leveldat
            // TODO incomplete
            std::ofstream dat(options.path / "level.dat", std::ios::binary);
            zlib::ozlibstream strm(dat, Z_DEFAULT_COMPRESSION, true);

            nbt::io::stream_writer nbt(strm);
            nbt::tag_compound root{};

            nbt::tag_compound data{};

            data["LevelName"] = w->getName();

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

            root.emplace<nbt::tag_compound>("Data", data);
            nbt.write_tag("", root);
        }
        // Regions
        auto io = this->getAsByRelation<const region::JungleAnvilRegionIO, &lodestone::minecraft::common::identifiers::io::REGION_IO>();

        std::filesystem::path p = options.path;

        // todo this is trash code, throw it in the bin and remake it later
        // we need to register custom dims in Level, and then make an internal conversion in this lib.
        int i = 2; // for writing other dims
        for (auto &[id, lvl] : w->getLevels()) {
            const int dim = mcregion::player::McRegionPlayer::identifierToDimensionId(id);

            if (dim == 0) {
                p = options.path;
            } else {
                p = options.path /
                    ("DIM" + std::to_string(dim == 0x7FFFFFFF ? i : dim));
            }
            i++;

            if (!std::filesystem::exists(p))
                std::filesystem::create_directory(p);

            std::filesystem::path r = p / "region";
            if (!std::filesystem::exists(r))
                std::filesystem::create_directory(r);

            level::types::Bounds3i bounds = lvl->getChunkBounds();

            for (int rx = bounds.min.x >> 5; rx <= bounds.max.x >> 5; rx++) {
                for (int rz = bounds.min.z >> 5; rz <= bounds.max.z >> 5; rz++) {
                    std::ofstream o(r / std::format("r.{}.{}.mca", rx, rz));

                    io->write(lvl.get(), common::conversion::io::options::OptionPresets::CommonChunkWriteOptions {
                                  common::conversion::io::options::ChunkOptions {
                                          {rx, rz}
                                  },
                                  common::conversion::io::options::OptionPresets::CommonWriteOptions {
                                      lodestone::conversion::io::options::fs::file::FileWriterOptions {
                                          o
                                      },
                                      lodestone::conversion::io::options::versioned::VersionedOptions {
                                      options.version
                                      }
                                  }
                    });

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
} // namespace lodestone::minecraft::java::anvil::jungle::world