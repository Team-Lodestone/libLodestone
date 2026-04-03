//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#include "Lodestone.Tests/tests/MainTests.h"

#include <Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilWorldIo.h>

#include <Lodestone.Minecraft.Java/anvil/jungle/JungleAnvilRegion.h>
#include <Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilRegionIo.h>

#include <fstream>

#include "Lodestone.Tests/util.h"

#include <Lodestone.Level/Level.h>
#include <Lodestone.Minecraft.Java/Identifiers.h>
#include <Lodestone.Minecraft.Java/Version.h>
#include <Lodestone.Minecraft.Java/classic/minev2/MineV2World.h>
#include <Lodestone.Minecraft.Java/conversion/mcregion/McRegionChunkIo.h>
#include <Lodestone.Minecraft.Java/conversion/mcregion/McRegionRegionIo.h>
#include <Lodestone.Minecraft.Java/mcregion/McRegionWorld.h>
#include <Lodestone.Minecraft.Java/conversion/mcregion/McRegionWorldIo.h>

#include <Lodestone.Minecraft.Java/mcregion/McRegionChunk.h>
#include <Lodestone.Minecraft.Java/mcregion/McRegionRegion.h>

#include <Lodestone.Minecraft.Java/conversion/classic/minev2/MineV2WorldIo.h>

#include <Lodestone.Minecraft.Java/conversion/alpha/AlphaWorldIo.h>

#include <Lodestone.Minecraft.Common/block/Blocks.h>

namespace lodestone::tests::test {
    void MainTests::add() {
        auto &mgr = tfw::TestFramework::getInstance()->testManager();

        mgr.addTest(GENERATE_WATER_CHUNK, "Generate LCE Water Chunk", generateWaterChunk);
        mgr.addTest(READ_ANVIL_WORLD, "Read Anvil World", readAnvilWorld);
        mgr.addTest(WRITE_ANVIL_WORLD, "Write Anvil World", writeAnvilWorld);
        // ADD_TEST(READ_MCR_CHUNK, readMcrChunk, util::types::MAIN,
        //          "Read McRegion Chunk");
        // ADD_TEST(READ_MCR_FILE, readMcrFile, util::types::MAIN,
        //          "Read McRegion File");
        // ADD_TEST(READ_MCR_WORLD, readMcrWorld, util::types::MAIN,
        //          "Read McRegion World");
        // ADD_TEST(READ_MINEV2_WORLD, readMinev2World, util::types::MAIN,
        //          "Read Classic .mine v2 World");
        // ADD_TEST(READ_ALPHA_WORLD, readAlphaWorld, util::types::MAIN,
        //          "Read Alpha World");
        // ADD_TEST(WRITE_ALPHA_WORLD, writeAlphaWorld, util::types::MAIN,
        //          "Write Alpha World");
    }

    tfw::test::result::TestResult MainTests::generateWaterChunk(tfw::test::logging::loggers::ITestLogger &logger) {
        const std::string name = "LCEWaterChunk";

        std::unique_ptr<level::FiniteLevel> lvl = std::make_unique<level::FiniteLevel>(level::types::Bounds2i{0, 0, 16, 16});

        constexpr bool USE_MODERN = false;

        if constexpr (USE_MODERN) {
            constexpr int SEA_LEVEL = 62 + 64;
            for (int y = 0; y < 128 + 64; y++ ) {
                for (int z = 0; z < 16; z++ ) {
                    for (int x = 0; x < 16; x++ ) {
                        if (SEA_LEVEL < y) {
                            lvl->setBlockCreate(level::block::BlockRegistry::getInstance().getBlock(&level::block::Blocks::AIR), x, y, z);
                        } else if (y > SEA_LEVEL - 10) {
                            lvl->setBlockCreate(level::block::BlockRegistry::getInstance().getBlock(&minecraft::common::block::Blocks::WATER), x, y, z);
                        } else if (y > 0 && y <= 64) {
                            lvl->setBlockCreate(level::block::BlockRegistry::getInstance().getBlock(&minecraft::common::block::Blocks::OAK_LOG), x, y, z); // deepslate
                        } else if (y == 0) {
                            lvl->setBlockCreate(level::block::BlockRegistry::getInstance().getBlock(&minecraft::common::block::Blocks::BEDROCK), x, y, z);
                        } else {
                            lvl->setBlockCreate(level::block::BlockRegistry::getInstance().getBlock(&minecraft::common::block::Blocks::STONE), x, y, z);
                        }
                    }
                }
            }
        } else {
            constexpr int SEA_LEVEL = 62;
            for (int y = 0; y < 128; y++ ) {
                for (int z = 0; z < 16; z++ ) {
                    for (int x = 0; x < 16; x++ ) {
                        if (SEA_LEVEL < y) {
                            lvl->setBlockCreate(level::block::BlockRegistry::getInstance().getBlock(&level::block::Blocks::AIR), x, y, z);
                        } else if (y > SEA_LEVEL - 10) {
                            lvl->setBlockCreate(level::block::BlockRegistry::getInstance().getBlock(&minecraft::common::block::Blocks::WATER), x, y, z);
                        } else if (y == 0) {
                            lvl->setBlockCreate(level::block::BlockRegistry::getInstance().getBlock(&minecraft::common::block::Blocks::BEDROCK), x, y, z);
                        } else {
                            lvl->setBlockCreate(level::block::BlockRegistry::getInstance().getBlock(&minecraft::common::block::Blocks::STONE), x, y, z);
                        }
                    }
                }
            }
        }

        level::world::World *wld = new level::world::World();
        wld->addLevel(level::world::World::Dimension::OVERWORLD, std::move(lvl));

        const conversion::registry::WorldIORegistry &r = conversion::registry::WorldIORegistry::getInstance();

        const auto io = r.getAs<const minecraft::java::mcregion::world::McRegionWorldIo>(
                minecraft::java::identifiers::MCREGION_WORLD_IO);

        io->write(wld, lodestone::minecraft::common::conversion::io::options::OptionPresets::CommonFilesystemOptions {
                lodestone::conversion::io::options::fs::FilesystemPathOptions {
                    util::OUTPUT_FOLDER / name
                },
                conversion::io::options::versioned::VersionedOptions {
                    minecraft::java::b1_3
                }
        });

        return tfw::test::result::TestResult(true, wld->toString());
    }

    tfw::test::result::TestResult MainTests::readAnvilWorld(tfw::test::logging::loggers::ITestLogger &logger) {
        const std::string name("AnvilWorld");
        const std::filesystem::path dir(util::INPUT_FOLDER / name);
        logger << "Reading from " << dir << std::endl;

        const minecraft::java::anvil::jungle::world::JungleAnvilWorldIo *inputIo = conversion::registry::WorldIORegistry::getInstance().getAs<const minecraft::java::anvil::jungle::world::JungleAnvilWorldIo>(minecraft::java::identifiers::ANVIL_JUNGLE_WORLD_IO);

        const auto w = inputIo->read(lodestone::minecraft::common::conversion::io::options::OptionPresets::CommonFilesystemOptions {
                                    conversion::io::options::fs::FilesystemPathOptions {
                                        dir
                                    },
                                    conversion::io::options::versioned::VersionedOptions {
                                        minecraft::java::Version::r1_2_1
            }});

        logger << "Writing to " << util::OUTPUT_FOLDER / name << std::endl;

        const minecraft::java::mcregion::world::McRegionWorldIo *outputIo = conversion::registry::WorldIORegistry::getInstance().getAs<const minecraft::java::mcregion::world::McRegionWorldIo>(minecraft::java::identifiers::MCREGION_WORLD_IO);
        outputIo->write(w.get(), lodestone::minecraft::common::conversion::io::options::OptionPresets::CommonFilesystemOptions {
            conversion::io::options::fs::FilesystemPathOptions {
            util::OUTPUT_FOLDER / name
            },
            conversion::io::options::versioned::VersionedOptions {
                minecraft::java::b1_3
            }
        });

        return tfw::test::result::TestResult(true, w->toString());
    }

    tfw::test::result::TestResult MainTests::writeAnvilWorld(tfw::test::logging::loggers::ITestLogger &logger) {
        const std::string name("WriteAnvilWorld");
        const std::filesystem::path inputDir(util::INPUT_FOLDER / name);
        const std::filesystem::path outputDir(util::OUTPUT_FOLDER / name);

        logger << "Input: " << inputDir << std::endl;

        const minecraft::java::mcregion::world::McRegionWorldIo *inputIo = conversion::registry::WorldIORegistry::getInstance().getAs<const minecraft::java::mcregion::world::McRegionWorldIo>(minecraft::java::identifiers::MCREGION_WORLD_IO);
        const auto w = inputIo->read(lodestone::minecraft::common::conversion::io::options::OptionPresets::CommonFilesystemOptions {
            conversion::io::options::fs::FilesystemPathOptions {
                inputDir
            },
            conversion::io::options::versioned::VersionedOptions {
                minecraft::java::Version::b1_3
            }
        });

        logger << "Bounds: " << w->getDefaultLevel()->getChunkBounds() << std::endl;

        logger << "Output: " << outputDir << std::endl;

        const minecraft::java::anvil::jungle::world::JungleAnvilWorldIo *outputIo = conversion::registry::WorldIORegistry::getInstance().getAs<const minecraft::java::anvil::jungle::world::JungleAnvilWorldIo>(minecraft::java::identifiers::ANVIL_JUNGLE_WORLD_IO);
        outputIo->write(w.get(), lodestone::minecraft::common::conversion::io::options::OptionPresets::CommonFilesystemOptions {
            conversion::io::options::fs::FilesystemPathOptions {
                outputDir
            },
            conversion::io::options::versioned::VersionedOptions {
                minecraft::java::r1_2_1
            }
        });

        return tfw::test::result::TestResult(true, w->toString());
    }

    // void MainTests::readMcrChunk(tfw::test::logging::loggers::ITestLogger &logger) {
    //     OPEN_FILE_STREAM("mcregion_chunk.dat", c);
    //
    //     minecraft::java::mcregion::chunk::McRegionChunkIO *io =
    //         static_cast<minecraft::java::mcregion::chunk::McRegionChunkIO *>(lodestone::conversion::registry::registries::ChunkIORegistry::getInstance().getChunkIO({"lodestone", "mcregion"}));
    //     std::unique_ptr<level::chunk::Chunk> ch =
    //         io->read(in, minecraft::java::Version::b1_3);
    //
    //     level::Level *level = new level::Level();
    //     level->addChunk(std::move(ch));
    //
    //     // const lodestone::conversion::registry::registries::FileWorldIO *l2 =
    //     // dynamic_cast<const
    //     //     lodestone::conversion::registry::registries::FileWorldIO *>(
    //     //     lodestone::conversion::registry::registries::WorldIORegistry::s_instance.getWorldIO({"lodestone",
    //     //     "minev2"}));
    //     // lodestone::minecraft::minecraft::java::classic::minev2::MineV2World
    //     // *w = new
    //     // lodestone::minecraft::minecraft::java::classic::minev2::MineV2World(
    //     //     std::unique_ptr<lodestone::level::Level>(level), "New World",
    //     //     "h");
    //     // WRITE_FILE("minev2.mine.out", reinterpret_cast<const
    //     // char*>(l2->write(w,
    //     // lodestone::minecraft::minecraft::java::c0_0_12a)),
    //     //            l2->getSize(w,
    //     //            lodestone::minecraft::minecraft::java::c0_0_12a));
    // }
    //
    // void MainTests::readMcrFile(tfw::test::logging::loggers::ITestLogger &logger) {
    //     std::string name("r.0.0.omnibeta");
    //     OPEN_FILE_STREAM(std::format("{}.mcr", name), c);
    //
    //     minecraft::java::mcregion::region::McRegionRegionIO *io =
    //         (minecraft::java::mcregion::region::McRegionRegionIO *)
    //             lodestone::conversion::registry::registries::RegionIORegistry::getInstance()
    //                 .getRegionIO(minecraft::java::identifiers::MCREGION_CHUNK_IO);
    //     std::unique_ptr<level::region::Region> r =
    //         io->read(in, minecraft::java::Version::b1_3,
    //                  minecraft::java::mcregion::region::McRegionRegion::
    //                      getCoordsFromFilename(name));
    //
    //     // const lodestone::conversion::registry::registries::FileWorldIO *l2 =
    //     // dynamic_cast<const
    //     //     lodestone::conversion::registry::registries::FileWorldIO *>(
    //     //     lodestone::conversion::registry::registries::WorldIORegistry::s_instance.getWorldIO({"lodestone",
    //     //     "minev2"}));
    //     // lodestone::minecraft::minecraft::java::classic::minev2::MineV2World
    //     // *w = new
    //     // lodestone::minecraft::minecraft::java::classic::minev2::MineV2World(
    //     //     std::move(r), "New World", "h");
    //     //
    //     // OPEN_WRITE_FILE_STREAM(std::format("{}.dat", name))
    //     // l2->write(w, lodestone::minecraft::minecraft::java::c0_28, out);
    //     // out.close();
    // }
    //
    // void MainTests::readMcrWorld(tfw::test::logging::loggers::ITestLogger &logger) {
    //     std::string name("McRegionWorld");
    //     std::filesystem::path dir(util::INPUT_FOLDER / name);
    //
    //     const minecraft::java::mcregion::world::McRegionWorldIo *io =
    //         (minecraft::java::mcregion::world::McRegionWorldIo *)
    //             lodestone::conversion::registry::registries::WorldIORegistry::getInstance()
    //                 .getWorldIO(minecraft::java::identifiers::MCREGION_CHUNK_IO);
    //     std::shared_ptr<level::world::World> w =
    //         io->read(dir, minecraft::java::Version::b1_3, {});
    //
    //     std::cout << "done now writing" << std::endl;
    //
    //     // const lodestone::conversion::registry::registries::FileWorldIO *l2 =
    //     // dynamic_cast<const lodestone::conversion::registry::registries::FileWorldIO
    //     // *>(lodestone::conversion::registry::registries::WorldIORegistry::s_instance.getWorldIO({"lodestone",
    //     // "minev2"}));
    //     //
    //     // OPEN_WRITE_FILE_STREAM(std::format("{}.dat", name))
    //     // l2->write(w.get(), lodestone::minecraft::minecraft::java::c0_28,
    //     // out); out.close();
    //     // const minecraft::java::mcregion::region::McRegionRegionIO *r =
    //     // dynamic_cast<
    //     //     const minecraft::java::mcregion::region::McRegionRegionIO *>(
    //     //     lodestone::conversion::registry::registries::RegionIORegistry::getInstance()
    //     //         .getRegionIO({"lodestone", "mcregion"}));
    //     //
    //     // OPEN_WRITE_FILE_STREAM(std::format("{}.mcr", name))
    //     // r->write(w.get()->getDefaultLevel(),
    //     // lodestone::minecraft::java::b1_3,
    //     //          {0, 0}, out);
    //     // out.close();
    //
    //     const minecraft::java::alpha::world::AlphaWorldIo *converter =
    //         (minecraft::java::alpha::world::AlphaWorldIo *)
    //             lodestone::conversion::registry::registries::WorldIORegistry::getInstance()
    //                 .getWorldIO(minecraft::java::identifiers::ALPHA_WORLD_IO);
    //
    //     converter->write(util::OUTPUT_FOLDER / name, w.get(),
    //                      minecraft::java::b1_3, {});
    // }
    //
    // void MainTests::readMinev2World(tfw::test::logging::loggers::ITestLogger &logger) {
    //     std::string name("ProjectLodestoneTestWorld");
    //     OPEN_FILE_STREAM(std::format("{}.mine", name), c);
    //
    //     const minecraft::java::classic::minev2::MineV2WorldIO *mv2io =
    //         (minecraft::java::classic::minev2::MineV2WorldIO *)
    //             lodestone::conversion::registry::registries::WorldIORegistry::getInstance()
    //                 .getWorldIO(minecraft::java::identifiers::MINEV2_LEVEL_IO);
    //
    //     std::unique_ptr<level::world::World> wld =
    //         mv2io->read(in, lodestone::minecraft::java::c0_28, {});
    //
    //     const minecraft::java::mcregion::world::McRegionWorldIo *mcrio =
    //         (minecraft::java::mcregion::world::McRegionWorldIo *)
    //             lodestone::conversion::registry::registries::WorldIORegistry::getInstance()
    //                 .getWorldIO(minecraft::java::identifiers::MCREGION_CHUNK_IO);
    //
    //     mcrio->write(
    //         util::OUTPUT_FOLDER / name, wld.get(), minecraft::java::b1_3,
    //         minecraft::java::classic::minev2::options::MineV2WorldWriteOptions{
    //             level::world::World::Dimension::OVERWORLD});
    // }
    //
    // void MainTests::readAlphaWorld(tfw::test::logging::loggers::ITestLogger &logger) {
    //     std::string name("alphaworld");
    //     std::filesystem::path dir(util::INPUT_FOLDER / name);
    //
    //     const minecraft::java::alpha::world::AlphaWorldIo *io =
    //         static_cast<const minecraft::java::alpha::world::AlphaWorldIo *>(
    //             lodestone::conversion::registry::registries::WorldIORegistry::getInstance()
    //                 .getWorldIO(minecraft::java::identifiers::ALPHA_WORLD_IO));
    //
    //     std::shared_ptr<level::world::World> w =
    //         io->read(dir, minecraft::java::Version::b1_3, {});
    //
    //     std::cout << "done now writing" << std::endl;
    //
    //     const lodestone::conversion::registry::registries::FileWorldIO *l2 =
    //         dynamic_cast<const lodestone::conversion::registry::registries::FileWorldIO *>(
    //             lodestone::conversion::registry::registries::WorldIORegistry::getInstance()
    //                 .getWorldIO({"lodestone", "minev2"}));
    //     {
    //         OPEN_WRITE_FILE_STREAM(std::format("{}_overworld.dat", name))
    //         l2->write(w.get(), lodestone::minecraft::java::c0_28, out,
    //                   minecraft::java::classic::minev2::options::
    //                       MineV2WorldWriteOptions{
    //                           level::world::World::Dimension::OVERWORLD});
    //         out.close();
    //     }
    //
    //     {
    //         OPEN_WRITE_FILE_STREAM(std::format("{}_nether.dat", name))
    //         l2->write(w.get(), lodestone::minecraft::java::c0_28, out,
    //                   minecraft::java::classic::minev2::options::
    //                       MineV2WorldWriteOptions{
    //                           level::world::World::Dimension::NETHER});
    //         out.close();
    //     }
    // }
    //
    // void MainTests::writeAlphaWorld(tfw::test::logging::loggers::ITestLogger &logger) {
    //     std::string name("13a_03-level_greffen");
    //     OPEN_FILE_STREAM(std::format("{}.mine", name), c);
    //
    //     const minecraft::java::classic::minev2::MineV2WorldIO *mv2io =
    //         (minecraft::java::classic::minev2::MineV2WorldIO *)
    //             lodestone::conversion::registry::registries::WorldIORegistry::getInstance()
    //                 .getWorldIO(minecraft::java::identifiers::MINEV2_LEVEL_IO);
    //
    //     std::unique_ptr<level::world::World> wld =
    //         mv2io->read(in, minecraft::java::c0_30_CPE, {});
    //
    //     const minecraft::java::alpha::world::AlphaWorldIo *converter =
    //         (minecraft::java::alpha::world::AlphaWorldIo *)
    //             lodestone::conversion::registry::registries::WorldIORegistry::getInstance()
    //                 .getWorldIO(minecraft::java::identifiers::ALPHA_WORLD_IO);
    //
    //     converter->write(util::OUTPUT_FOLDER / name, wld.get(),
    //                      minecraft::java::b1_3, {});
    // }

} // namespace lodestone::tests::test
