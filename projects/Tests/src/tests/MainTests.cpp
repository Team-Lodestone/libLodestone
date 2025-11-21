//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#include "Lodestone.Tests/tests/MainTests.h"

#include <Lodestone.Java/classic/minev2/options/MineV2WorldWriteOptions.h>

#include <Lodestone.Java/alpha/world/AlphaWorldIo.h>

#include <fstream>

#include "Lodestone.Tests/util.h"
#include <Lodestone.Conversion/chunk/ChunkIORegistry.h>
#include <Lodestone.Conversion/region/RegionIORegistry.h>
#include <Lodestone.Conversion/world/FileWorldIo.h>
#include <Lodestone.Conversion/world/WorldIORegistry.h>
#include <Lodestone.Java/Identifiers.h>
#include <Lodestone.Java/Version.h>
#include <Lodestone.Java/classic/minev2/MineV2World.h>
#include <Lodestone.Java/mcr/chunk/McRegionChunkIo.h>
#include <Lodestone.Java/mcr/region/McRegionRegionIo.h>
#include <Lodestone.Java/mcr/world/McRegionWorld.h>
#include <Lodestone.Java/mcr/world/McRegionWorldIo.h>
#include <Lodestone.Level/Level.h>

#include <Lodestone.Java/mcr/chunk/McRegionChunk.h>
#include <Lodestone.Java/mcr/region/McRegionRegion.h>

#include <Lodestone.Java/classic/minev2/MineV2WorldIo.h>

namespace lodestone::tests::test {
    void MainTests::run() {
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
    }

    void MainTests::readMcrChunk() {
        OPEN_FILE_STREAM("mcregion_chunk.dat", c);

        java::mcr::chunk::McRegionChunkIO *io =
            (java::mcr::chunk::McRegionChunkIO *)
                lodestone::conversion::chunk::ChunkIORegistry::getInstance()
                    .getChunkIO({"lodestone", "mcregion"});
        std::unique_ptr<level::chunk::Chunk> ch =
            io->read(in, java::Version::b1_3);

        level::Level *level = new level::Level();
        level->addChunk(std::move(ch));

        // const lodestone::conversion::world::FileWorldIO *l2 =
        // dynamic_cast<const
        //     lodestone::conversion::world::FileWorldIO *>(
        //     lodestone::conversion::world::WorldIORegistry::sInstance.getWorldIO({"lodestone",
        //     "minev2"}));
        // lodestone::java::classic::minev2::MineV2World *w = new
        // lodestone::java::classic::minev2::MineV2World(
        //     std::unique_ptr<lodestone::level::Level>(level), "New World",
        //     "h");
        // WRITE_FILE("minev2.mine.out", reinterpret_cast<const
        // char*>(l2->write(w, lodestone::java::c0_0_12a)),
        //            l2->getSize(w, lodestone::java::c0_0_12a));
    }

    void MainTests::readMcrFile() {
        std::string name("r.0.0.omnibeta");
        OPEN_FILE_STREAM(std::format("{}.mcr", name), c);

        java::mcr::region::McRegionRegionIO *io =
            (java::mcr::region::McRegionRegionIO *)
                lodestone::conversion::region::RegionIORegistry::getInstance()
                    .getRegionIO(java::identifiers::MCREGION);
        std::unique_ptr<level::region::Region> r = io->read(
            in, java::Version::b1_3,
            java::mcr::region::McRegionRegion::getCoordsFromFilename(name));

        // const lodestone::conversion::world::FileWorldIO *l2 =
        // dynamic_cast<const
        //     lodestone::conversion::world::FileWorldIO *>(
        //     lodestone::conversion::world::WorldIORegistry::sInstance.getWorldIO({"lodestone",
        //     "minev2"}));
        // lodestone::java::classic::minev2::MineV2World *w = new
        // lodestone::java::classic::minev2::MineV2World(
        //     std::move(r), "New World", "h");
        //
        // OPEN_WRITE_FILE_STREAM(std::format("{}.dat", name))
        // l2->write(w, lodestone::java::c0_28, out);
        // out.close();
    }

    void MainTests::readMcrWorld() {
        std::string name("omnibeta");
        std::filesystem::path dir(util::INPUT_FOLDER / name);

        const java::mcr::world::McRegionWorldIo *io =
            (java::mcr::world::McRegionWorldIo *)
                lodestone::conversion::world::WorldIORegistry::getInstance()
                    .getWorldIO(java::identifiers::MCREGION);
        std::shared_ptr<level::world::World> w =
            io->read(dir, java::Version::b1_3, {});

        std::cout << "done now writing" << std::endl;

        // const lodestone::conversion::world::FileWorldIO *l2 =
        // dynamic_cast<const lodestone::conversion::world::FileWorldIO
        // *>(lodestone::conversion::world::WorldIORegistry::sInstance.getWorldIO({"lodestone",
        // "minev2"}));
        //
        // OPEN_WRITE_FILE_STREAM(std::format("{}.dat", name))
        // l2->write(w.get(), lodestone::java::c0_28, out);
        // out.close();
        const java::mcr::region::McRegionRegionIO *r =
            dynamic_cast<const java::mcr::region::McRegionRegionIO *>(
                lodestone::conversion::region::RegionIORegistry::getInstance()
                    .getRegionIO({"lodestone", "mcregion"}));

        OPEN_WRITE_FILE_STREAM(std::format("{}.mcr", name))
        r->write(w.get()->getDefaultLevel(), lodestone::java::b1_3, {0, 0},
                 out);
        out.close();
    }

    void MainTests::readMinev2World() {
        std::string name("ProjectLodestoneTestWorld");
        OPEN_FILE_STREAM(std::format("{}.mine", name), c);

        const java::classic::minev2::MineV2WorldIO *mv2io =
            (java::classic::minev2::MineV2WorldIO *)
                lodestone::conversion::world::WorldIORegistry::getInstance()
                    .getWorldIO(java::identifiers::MINEV2);

        std::unique_ptr<level::world::World> wld =
            mv2io->read(in, lodestone::java::c0_28, {});

        const java::mcr::world::McRegionWorldIo *mcrio =
            (java::mcr::world::McRegionWorldIo *)
                lodestone::conversion::world::WorldIORegistry::getInstance()
                    .getWorldIO(java::identifiers::MCREGION);

        mcrio->write(util::OUTPUT_FOLDER / name, wld.get(), java::b1_3,
                     java::classic::minev2::options::MineV2WorldWriteOptions{
                         level::world::World::Dimension::OVERWORLD});
    }

    void MainTests::readAlphaWorld() {
        std::string name("alphaworld");
        std::filesystem::path dir(util::INPUT_FOLDER / name);

        const java::alpha::world::AlphaWorldIo *io =
            static_cast<const java::alpha::world::AlphaWorldIo *>(
                lodestone::conversion::world::WorldIORegistry::getInstance()
                    .getWorldIO(java::identifiers::ALPHA));

        std::shared_ptr<level::world::World> w =
            io->read(dir, java::Version::b1_3, {});

        std::cout << "done now writing" << std::endl;

        const lodestone::conversion::world::FileWorldIO *l2 =
            dynamic_cast<const lodestone::conversion::world::FileWorldIO *>(
                lodestone::conversion::world::WorldIORegistry::getInstance()
                    .getWorldIO({"lodestone", "minev2"}));
        {
            OPEN_WRITE_FILE_STREAM(std::format("{}_overworld.dat", name))
            l2->write(w.get(), lodestone::java::c0_28, out,
                      java::classic::minev2::options::MineV2WorldWriteOptions{
                          level::world::World::Dimension::OVERWORLD});
            out.close();
        }

        {
            OPEN_WRITE_FILE_STREAM(std::format("{}_nether.dat", name))
            l2->write(w.get(), lodestone::java::c0_28, out,
                      java::classic::minev2::options::MineV2WorldWriteOptions{
                          level::world::World::Dimension::NETHER});
            out.close();
        }
    }
} // namespace lodestone::tests::test
