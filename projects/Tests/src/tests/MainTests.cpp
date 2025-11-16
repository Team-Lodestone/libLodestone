//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#include "Lodestone.Tests/tests/MainTests.h"

#include <fstream>

#include "Lodestone.Tests/util.h"
#include <Lodestone.Java/Identifiers.h>
#include <Lodestone.Java/Version.h>
#include <Lodestone.Java/mcr/region/McRegionRegionIo.h>
#include <Lodestone.Java/classic/minev2/MineV2World.h>
#include <Lodestone.Java/mcr/chunk/McRegionChunkIo.h>
#include <Lodestone.Java/mcr/world/McRegionWorld.h>
#include <Lodestone.Java/mcr/world/McRegionWorldIo.h>
#include <Lodestone.Level/Level.h>
#include <Lodestone.Conversion/chunk/ChunkIORegistry.h>
#include <Lodestone.Conversion/region/RegionIORegistry.h>
#include <Lodestone.Conversion/world/FileWorldIo.h>
#include <Lodestone.Conversion/world/WorldIORegistry.h>

#include <Lodestone.Java/mcr/chunk/McRegionChunk.h>
#include <Lodestone.Java/mcr/region/McRegionRegion.h>

namespace lodestone::tests::test {
    void MainTests::run() {
        ADD_TEST(READ_MCR_CHUNK, readMcrChunk, util::types::MAIN, "Read McRegion Chunk");
        ADD_TEST(READ_MCR_FILE, readMcrFile, util::types::MAIN, "Read McRegion File");
        ADD_TEST(READ_MCR_WORLD, readMcrWorld, util::types::MAIN, "Read McRegion World");
    }

    void MainTests::readMcrChunk() {
        OPEN_FILE_STREAM("mcregion_chunk.dat", c);

        java::mcr::chunk::McRegionChunkIO *io = (java::mcr::chunk::McRegionChunkIO *)
                lodestone::conversion::chunk::ChunkIORegistry::sInstance.getChunkIO({"lodestone", "mcregion"});
        std::unique_ptr<level::chunk::Chunk> ch = io->read(in, java::Version::b1_3);

        level::Level *level = new level::Level();
        level->addChunk(std::move(ch));

        // const lodestone::conversion::world::FileWorldIO *l2 = dynamic_cast<const
        //     lodestone::conversion::world::FileWorldIO *>(
        //     lodestone::conversion::world::WorldIORegistry::sInstance.getWorldIO({"lodestone", "minev2"}));
        // lodestone::java::classic::minev2::MineV2World *w = new lodestone::java::classic::minev2::MineV2World(
        //     std::unique_ptr<lodestone::level::Level>(level), "New World", "h");
        // WRITE_FILE("minev2.mine.out", reinterpret_cast<const char*>(l2->write(w, lodestone::java::c0_0_12a)),
        //            l2->getSize(w, lodestone::java::c0_0_12a));
    }

    void MainTests::readMcrFile() {
        std::string name("r.0.0.omnibeta");
        OPEN_FILE_STREAM(std::format("{}.mcr", name), c);

        java::mcr::region::McRegionRegionIO *io = (java::mcr::region::McRegionRegionIO *)
                lodestone::conversion::region::RegionIORegistry::sInstance.getRegionIO(java::identifiers::MCREGION);
        std::unique_ptr<level::region::Region> r = io->read(in, java::Version::b1_3, java::mcr::region::McRegionRegion::getCoordsFromFilename(name));

        const lodestone::conversion::world::FileWorldIO *l2 = dynamic_cast<const
            lodestone::conversion::world::FileWorldIO *>(
            lodestone::conversion::world::WorldIORegistry::sInstance.getWorldIO({"lodestone", "minev2"}));
        lodestone::java::classic::minev2::MineV2World *w = new lodestone::java::classic::minev2::MineV2World(
            std::move(r), "New World", "h");

        OPEN_WRITE_FILE_STREAM(std::format("{}.dat", name))
        l2->write(w, lodestone::java::c0_28, out);
        out.close();
    }

    void MainTests::readMcrWorld() {
        std::string name("ShadowWorld");
        std::filesystem::path dir(util::INPUT_FOLDER / name);

        const java::mcr::world::McRegionWorldIo *io = (java::mcr::world::McRegionWorldIo *)
        lodestone::conversion::world::WorldIORegistry::sInstance.getWorldIO(java::identifiers::MCREGION);
        std::shared_ptr<level::world::World> w = io->read(dir, java::Version::b1_3);

        std::cout << "done now writing" << std::endl;

        const lodestone::conversion::world::FileWorldIO *l2 = dynamic_cast<const lodestone::conversion::world::FileWorldIO *>(lodestone::conversion::world::WorldIORegistry::sInstance.getWorldIO({"lodestone", "minev2"}));

        OPEN_WRITE_FILE_STREAM(std::format("{}.dat", name))
        l2->write(w.get(), lodestone::java::c0_28, out);
        out.close();
    }
}
