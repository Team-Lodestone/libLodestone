//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#include "Lodestone.Tests/tests/MainTests.h"

#include <Lodestone.Minecraft.Java/classic/minev2/options/MineV2WorldWriteOptions.h>

#include <fstream>

#include "Lodestone.Tests/util.h"
#include <Lodestone.Conversion/chunk/ChunkIORegistry.h>
#include <Lodestone.Conversion/region/RegionIORegistry.h>
#include <Lodestone.Conversion/world/FileWorldIo.h>
#include <Lodestone.Conversion/world/WorldIORegistry.h>
#include <Lodestone.Minecraft.Java/Identifiers.h>
#include <Lodestone.Minecraft.Java/Version.h>
#include <Lodestone.Minecraft.Java/classic/minev2/MineV2World.h>
#include <Lodestone.Minecraft.Java/mcr/chunk/McRegionChunkIo.h>
#include <Lodestone.Minecraft.Java/mcr/region/McRegionRegionIo.h>
#include <Lodestone.Minecraft.Java/mcr/world/McRegionWorld.h>
#include <Lodestone.Minecraft.Java/mcr/world/McRegionWorldIo.h>
#include <Lodestone.Level/Level.h>

#include <Lodestone.Minecraft.Java/mcr/chunk/McRegionChunk.h>
#include <Lodestone.Minecraft.Java/mcr/region/McRegionRegion.h>

#include <Lodestone.Minecraft.Java/classic/minev2/MineV2WorldIo.h>

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
    }

    void MainTests::readMcrChunk() {
        OPEN_FILE_STREAM("mcregion_chunk.dat", c);

        minecraft::java::mcr::chunk::McRegionChunkIO *io =
            (minecraft::java::mcr::chunk::McRegionChunkIO *)
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
        // lodestone::minecraft::minecraft::java::classic::minev2::MineV2World *w = new
        // lodestone::minecraft::minecraft::java::classic::minev2::MineV2World(
        //     std::unique_ptr<lodestone::level::Level>(level), "New World",
        //     "h");
        // WRITE_FILE("minev2.mine.out", reinterpret_cast<const
        // char*>(l2->write(w, lodestone::minecraft::minecraft::java::c0_0_12a)),
        //            l2->getSize(w, lodestone::minecraft::minecraft::java::c0_0_12a));
    }

    void MainTests::readMcrFile() {
        std::string name("r.0.0.omnibeta");
        OPEN_FILE_STREAM(std::format("{}.mcr", name), c);

        minecraft::java::mcr::region::McRegionRegionIO *io =
            (minecraft::java::mcr::region::McRegionRegionIO *)
                lodestone::conversion::region::RegionIORegistry::getInstance()
                    .getRegionIO(minecraft::java::identifiers::MCREGION);
        std::unique_ptr<level::region::Region> r = io->read(
            in, minecraft::java::Version::b1_3,
            minecraft::java::mcr::region::McRegionRegion::getCoordsFromFilename(name));

        // const lodestone::conversion::world::FileWorldIO *l2 =
        // dynamic_cast<const
        //     lodestone::conversion::world::FileWorldIO *>(
        //     lodestone::conversion::world::WorldIORegistry::sInstance.getWorldIO({"lodestone",
        //     "minev2"}));
        // lodestone::minecraft::minecraft::java::classic::minev2::MineV2World *w = new
        // lodestone::minecraft::minecraft::java::classic::minev2::MineV2World(
        //     std::move(r), "New World", "h");
        //
        // OPEN_WRITE_FILE_STREAM(std::format("{}.dat", name))
        // l2->write(w, lodestone::minecraft::minecraft::java::c0_28, out);
        // out.close();
    }

    void MainTests::readMcrWorld() {
        std::string name("omnibeta");
        std::filesystem::path dir(util::INPUT_FOLDER / name);

        const minecraft::java::mcr::world::McRegionWorldIo *io =
            (minecraft::java::mcr::world::McRegionWorldIo *)
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
        // l2->write(w.get(), lodestone::minecraft::minecraft::java::c0_28, out);
        // out.close();
        const minecraft::java::mcr::region::McRegionRegionIO *r =
            dynamic_cast<const minecraft::java::mcr::region::McRegionRegionIO *>(
                lodestone::conversion::region::RegionIORegistry::getInstance()
                    .getRegionIO({"lodestone", "mcregion"}));

        OPEN_WRITE_FILE_STREAM(std::format("{}.mcr", name))
        r->write(w.get()->getDefaultLevel(), lodestone::minecraft::java::b1_3, {0, 0},
                 out);
        out.close();
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

        const minecraft::java::mcr::world::McRegionWorldIo *mcrio =
            (minecraft::java::mcr::world::McRegionWorldIo *)
                lodestone::conversion::world::WorldIORegistry::getInstance()
                    .getWorldIO(minecraft::java::identifiers::MCREGION);

        mcrio->write(util::OUTPUT_FOLDER / name, wld.get(), minecraft::java::b1_3,
                     minecraft::java::classic::minev2::options::MineV2WorldWriteOptions{});
    }

} // namespace lodestone::tests::test
