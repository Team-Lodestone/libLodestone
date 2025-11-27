//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#include "Lodestone.Tests/tests/MainTests.h"

#include <Lodestone.Minecraft.Java/anvil/jungle/world/JungleAnvilWorldIo.h>

#include <Lodestone.Minecraft.Java/anvil/jungle/region/JungleAnvilRegion.h>
#include <Lodestone.Minecraft.Java/anvil/jungle/region/JungleAnvilRegionIo.h>

#include <Lodestone.Minecraft.Java/classic/minev2/options/MineV2WorldWriteOptions.h>

#include <fstream>

#include "Lodestone.Tests/util.h"
#include <Lodestone.Conversion/chunk/ChunkIORegistry.h>
#include <Lodestone.Conversion/region/RegionIORegistry.h>
#include <Lodestone.Conversion/world/FileWorldIo.h>
#include <Lodestone.Conversion/world/WorldIORegistry.h>
#include <Lodestone.Level/Level.h>
#include <Lodestone.Minecraft.Java/Identifiers.h>
#include <Lodestone.Minecraft.Java/Version.h>
#include <Lodestone.Minecraft.Java/classic/minev2/MineV2World.h>
#include <Lodestone.Minecraft.Java/mcregion/chunk/McRegionChunkIo.h>
#include <Lodestone.Minecraft.Java/mcregion/region/McRegionRegionIo.h>
#include <Lodestone.Minecraft.Java/mcregion/world/McRegionWorld.h>
#include <Lodestone.Minecraft.Java/mcregion/world/McRegionWorldIo.h>

#include <Lodestone.Minecraft.Java/mcregion/chunk/McRegionChunk.h>
#include <Lodestone.Minecraft.Java/mcregion/region/McRegionRegion.h>

#include <Lodestone.Minecraft.Java/classic/minev2/MineV2WorldIo.h>

#include <Lodestone.Minecraft.Java/alpha/world/AlphaWorldIo.h>

namespace lodestone::tests::test {
    void MainTests::run() {
        ADD_TEST(READ_ANVIL_WORLD, readAnvilWorld, util::types::MAIN,
                 "Read Anvil World");
        ADD_TEST(READ_MCR_CHUNK, readMcrChunk, util::types::MAIN,
                 "Read McRegion Chunk");
        ADD_TEST(READ_MCR_FILE, readMcrFile, util::types::MAIN,
                 "Read McRegion File");
        ADD_TEST(READ_MCR_WORLD, readMcrWorld, util::types::MAIN,
                 "Read McRegion World");
        ADD_TEST(READ_MINEV2_WORLD, readMinev2World, util::types::MAIN,
                 "Read Classic .mine v2 World");
        ADD_TEST(READ_ALPHA_WORLD, readAlphaWorld, util::types::MAIN,
                 "Read Alpha World");
        ADD_TEST(WRITE_ALPHA_WORLD, writeAlphaWorld, util::types::MAIN,
                 "Write Alpha World");
    }
    void MainTests::readAnvilWorld() {
        const std::string name("AnvilWorld");
        const std::filesystem::path dir(util::INPUT_FOLDER / name);

        const auto *io = static_cast<
            const minecraft::java::anvil::jungle::world::JungleAnvilWorldIo *>(
            conversion::world::WorldIORegistry::getInstance().getWorldIO(
                minecraft::java::identifiers::ANVIL_JUNGLE));
        const auto w = io->read(dir, minecraft::java::Version::r1_2_1, {});

        const auto converter = static_cast<
            const minecraft::java::mcregion::world::McRegionWorldIo *>(
            conversion::world::WorldIORegistry::getInstance().getWorldIO(
                minecraft::java::identifiers::MCREGION));

        converter->write(util::OUTPUT_FOLDER / name, w.get(),
                         minecraft::java::b1_3, {});
    }

    void MainTests::readMcrChunk() {
        OPEN_FILE_STREAM("mcregion_chunk.dat", c);

        minecraft::java::mcregion::chunk::McRegionChunkIO *io =
            (minecraft::java::mcregion::chunk::McRegionChunkIO *)
                lodestone::conversion::chunk::ChunkIORegistry::getInstance()
                    .getChunkIO({"lodestone", "mcregion"});
        std::unique_ptr<level::chunk::Chunk> ch =
            io->read(in, minecraft::java::Version::b1_3);

        level::Level *level = new level::Level();
        level->addChunk(std::move(ch));

        // const lodestone::conversion::world::FileWorldIO *l2 =
        // dynamic_cast<const
        //     lodestone::conversion::world::FileWorldIO *>(
        //     lodestone::conversion::world::WorldIORegistry::sInstance.getWorldIO({"lodestone",
        //     "minev2"}));
        // lodestone::minecraft::minecraft::java::classic::minev2::MineV2World
        // *w = new
        // lodestone::minecraft::minecraft::java::classic::minev2::MineV2World(
        //     std::unique_ptr<lodestone::level::Level>(level), "New World",
        //     "h");
        // WRITE_FILE("minev2.mine.out", reinterpret_cast<const
        // char*>(l2->write(w,
        // lodestone::minecraft::minecraft::java::c0_0_12a)),
        //            l2->getSize(w,
        //            lodestone::minecraft::minecraft::java::c0_0_12a));
    }

    void MainTests::readMcrFile() {
        std::string name("r.0.0.omnibeta");
        OPEN_FILE_STREAM(std::format("{}.mcr", name), c);

        minecraft::java::mcregion::region::McRegionRegionIO *io =
            (minecraft::java::mcregion::region::McRegionRegionIO *)
                lodestone::conversion::region::RegionIORegistry::getInstance()
                    .getRegionIO(minecraft::java::identifiers::MCREGION);
        std::unique_ptr<level::region::Region> r =
            io->read(in, minecraft::java::Version::b1_3,
                     minecraft::java::mcregion::region::McRegionRegion::
                         getCoordsFromFilename(name));

        // const lodestone::conversion::world::FileWorldIO *l2 =
        // dynamic_cast<const
        //     lodestone::conversion::world::FileWorldIO *>(
        //     lodestone::conversion::world::WorldIORegistry::sInstance.getWorldIO({"lodestone",
        //     "minev2"}));
        // lodestone::minecraft::minecraft::java::classic::minev2::MineV2World
        // *w = new
        // lodestone::minecraft::minecraft::java::classic::minev2::MineV2World(
        //     std::move(r), "New World", "h");
        //
        // OPEN_WRITE_FILE_STREAM(std::format("{}.dat", name))
        // l2->write(w, lodestone::minecraft::minecraft::java::c0_28, out);
        // out.close();
    }

    void MainTests::readMcrWorld() {
        std::string name("McRegionWorld");
        std::filesystem::path dir(util::INPUT_FOLDER / name);

        const minecraft::java::mcregion::world::McRegionWorldIo *io =
            (minecraft::java::mcregion::world::McRegionWorldIo *)
                lodestone::conversion::world::WorldIORegistry::getInstance()
                    .getWorldIO(minecraft::java::identifiers::MCREGION);
        std::shared_ptr<level::world::World> w =
            io->read(dir, minecraft::java::Version::b1_3, {});

        std::cout << "done now writing" << std::endl;

        // const lodestone::conversion::world::FileWorldIO *l2 =
        // dynamic_cast<const lodestone::conversion::world::FileWorldIO
        // *>(lodestone::conversion::world::WorldIORegistry::sInstance.getWorldIO({"lodestone",
        // "minev2"}));
        //
        // OPEN_WRITE_FILE_STREAM(std::format("{}.dat", name))
        // l2->write(w.get(), lodestone::minecraft::minecraft::java::c0_28,
        // out); out.close();
        // const minecraft::java::mcregion::region::McRegionRegionIO *r =
        // dynamic_cast<
        //     const minecraft::java::mcregion::region::McRegionRegionIO *>(
        //     lodestone::conversion::region::RegionIORegistry::getInstance()
        //         .getRegionIO({"lodestone", "mcregion"}));
        //
        // OPEN_WRITE_FILE_STREAM(std::format("{}.mcr", name))
        // r->write(w.get()->getDefaultLevel(),
        // lodestone::minecraft::java::b1_3,
        //          {0, 0}, out);
        // out.close();

        const minecraft::java::alpha::world::AlphaWorldIo *converter =
            (minecraft::java::alpha::world::AlphaWorldIo *)
                conversion::world::WorldIORegistry::getInstance()
                    .getWorldIO(minecraft::java::identifiers::ALPHA);

        converter->write(util::OUTPUT_FOLDER / name, w.get(),
                         minecraft::java::b1_3, {});
    }

    void MainTests::readMinev2World() {
        std::string name("ProjectLodestoneTestWorld");
        OPEN_FILE_STREAM(std::format("{}.mine", name), c);

        const minecraft::java::classic::minev2::MineV2WorldIO *mv2io =
            (minecraft::java::classic::minev2::MineV2WorldIO *)
                lodestone::conversion::world::WorldIORegistry::getInstance()
                    .getWorldIO(minecraft::java::identifiers::MINEV2);

        std::unique_ptr<level::world::World> wld =
            mv2io->read(in, lodestone::minecraft::java::c0_28, {});

        const minecraft::java::mcregion::world::McRegionWorldIo *mcrio =
            (minecraft::java::mcregion::world::McRegionWorldIo *)
                lodestone::conversion::world::WorldIORegistry::getInstance()
                    .getWorldIO(minecraft::java::identifiers::MCREGION);

        mcrio->write(
            util::OUTPUT_FOLDER / name, wld.get(), minecraft::java::b1_3,
            minecraft::java::classic::minev2::options::MineV2WorldWriteOptions{
                level::world::World::Dimension::OVERWORLD});
    }

    void MainTests::readAlphaWorld() {
        std::string name("alphaworld");
        std::filesystem::path dir(util::INPUT_FOLDER / name);

        const minecraft::java::alpha::world::AlphaWorldIo *io =
            static_cast<const minecraft::java::alpha::world::AlphaWorldIo *>(
                lodestone::conversion::world::WorldIORegistry::getInstance()
                    .getWorldIO(minecraft::java::identifiers::ALPHA));

        std::shared_ptr<level::world::World> w =
            io->read(dir, minecraft::java::Version::b1_3, {});

        std::cout << "done now writing" << std::endl;

        const lodestone::conversion::world::FileWorldIO *l2 =
            dynamic_cast<const lodestone::conversion::world::FileWorldIO *>(
                lodestone::conversion::world::WorldIORegistry::getInstance()
                    .getWorldIO({"lodestone", "minev2"}));
        {
            OPEN_WRITE_FILE_STREAM(std::format("{}_overworld.dat", name))
            l2->write(w.get(), lodestone::minecraft::java::c0_28, out,
                      minecraft::java::classic::minev2::options::
                          MineV2WorldWriteOptions{
                              level::world::World::Dimension::OVERWORLD});
            out.close();
        }

        {
            OPEN_WRITE_FILE_STREAM(std::format("{}_nether.dat", name))
            l2->write(w.get(), lodestone::minecraft::java::c0_28, out,
                      minecraft::java::classic::minev2::options::
                          MineV2WorldWriteOptions{
                              level::world::World::Dimension::NETHER});
            out.close();
        }
    }

    void MainTests::writeAlphaWorld() {
        std::string name("13a_03-level_greffen");
        OPEN_FILE_STREAM(std::format("{}.mine", name), c);

        const minecraft::java::classic::minev2::MineV2WorldIO *mv2io =
            (minecraft::java::classic::minev2::MineV2WorldIO *)
                conversion::world::WorldIORegistry::getInstance()
                    .getWorldIO(minecraft::java::identifiers::MINEV2);

        std::unique_ptr<level::world::World> wld =
            mv2io->read(in, minecraft::java::c0_30_CPE, {});

        const minecraft::java::alpha::world::AlphaWorldIo *converter =
            (minecraft::java::alpha::world::AlphaWorldIo *)
                conversion::world::WorldIORegistry::getInstance()
                    .getWorldIO(minecraft::java::identifiers::ALPHA);

        converter->write(util::OUTPUT_FOLDER / name, wld.get(),
                         minecraft::java::b1_3, {});
    }

} // namespace lodestone::tests::test
