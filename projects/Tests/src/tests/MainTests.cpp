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
#include <Lodestone.Level/Level.h>
#include <Lodestone.Level/conversion/chunk/ChunkIORegistry.h>
#include <Lodestone.Level/conversion/region/RegionIORegistry.h>
#include <Lodestone.Level/conversion/world/FileWorldIo.h>
#include <Lodestone.Level/conversion/world/WorldIORegistry.h>

namespace lodestone::tests::test {
    void MainTests::run() {
        ADD_TEST(READ_MCR_CHUNK, readMcrChunk, util::types::MAIN, "Read McRegion Chunk");
        ADD_TEST(READ_MCR_FILE, readMcrFile, util::types::MAIN, "Read McRegion File");
    }

    void MainTests::readMcrChunk() {
        OPEN_FILE("mcregion_chunk.dat", c);

        java::mcr::chunk::McRegionChunkIO *io = (java::mcr::chunk::McRegionChunkIO *)
                level::conversion::chunk::ChunkIORegistry::sInstance.getChunkIO({"lodestone", "mcregion"});
        level::chunk::Chunk *ch = io->read(c.data(), c.size(), java::Version::b1_3);

        level::Level *level = new level::Level();
        level->addChunk(std::unique_ptr<level::chunk::Chunk>(ch));

        const lodestone::level::conversion::world::FileWorldIO *l2 = dynamic_cast<const
            lodestone::level::conversion::world::FileWorldIO *>(
            lodestone::level::conversion::world::WorldIORegistry::sInstance.getWorldIO({"lodestone", "minev2"}));
        lodestone::java::classic::minev2::MineV2World *w = new lodestone::java::classic::minev2::MineV2World(
            std::unique_ptr<lodestone::level::Level>(level), "New World", "h");
        WRITE_FILE("minev2.mine.out", reinterpret_cast<const char*>(l2->write(w, lodestone::java::c0_0_12a)),
                   l2->getSize(w, lodestone::java::c0_0_12a));
    }

    void MainTests::readMcrFile() {
        OPEN_FILE("r.0.0.mcr", c);

        java::mcr::region::McRegionRegionIO *io = (java::mcr::region::McRegionRegionIO *)
                level::conversion::region::RegionIORegistry::sInstance.getRegionIO(java::identifiers::MCREGION);
        level::region::Region *r = io->read(c.data(), c.size(), java::Version::b1_3, {0, 0});

        const lodestone::level::conversion::world::FileWorldIO *l2 = dynamic_cast<const
            lodestone::level::conversion::world::FileWorldIO *>(
            lodestone::level::conversion::world::WorldIORegistry::sInstance.getWorldIO({"lodestone", "minev2"}));
        lodestone::java::classic::minev2::MineV2World *w = new lodestone::java::classic::minev2::MineV2World(
            std::unique_ptr<lodestone::level::Level>(r), "New World", "h");
        WRITE_FILE("minev2.mine.out", reinterpret_cast<const char*>(l2->write(w, lodestone::java::c0_0_12a)),
                   l2->getSize(w, lodestone::java::c0_0_12a));
    }
}
