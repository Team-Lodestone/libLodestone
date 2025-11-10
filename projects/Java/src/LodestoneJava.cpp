//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//

#include <Lodestone.Level/conversion/level/LevelIORegistry.h>

#include "Lodestone.Java/classic/minev1/MineV1LevelIO.h"
#include "Lodestone.Java/classic/minev2/MineV2LevelIO.h"
#include "Lodestone.Java/indev/McLevelLevelIO.h"
#include "Lodestone.Java/LodestoneJava.h"

#include "Lodestone.Java/Identifiers.h"
#include "Lodestone.Java/Version.h"
#include "Lodestone.Java/classic/minev2/MineV2WorldIo.h"
#include <Lodestone.Level/conversion/block/BlockIO.h>
#include <Lodestone.Level/conversion/block/VersionedBlockIO.h>
#include <Lodestone.Level/conversion/block/data/ClassicBlockData.h>
#include <Lodestone.Level/conversion/block/data/NumericBlockData.h>
#include <Lodestone.Level/conversion/chunk/ChunkIORegistry.h>
#include <Lodestone.Level/conversion/region/RegionIORegistry.h>
#include <Lodestone.Level/conversion/world/WorldIORegistry.h>
#include "Lodestone.Java/mcr/chunk/McRegionChunkIo.h"
#include "Lodestone.Java/mcr/region/McRegionRegionIo.h"

namespace lodestone::java {
    LodestoneJava *LodestoneJava::sInstance = nullptr;

    LodestoneJava::LodestoneJava() {
        this->io = level::conversion::block::version::VersionedBlockIO();
        initBlocks();

        // mine v1
        level::conversion::level::LevelIORegistry::sInstance.registerLevelIO(
            identifiers::MINEV1,
            std::make_unique<classic::minev1::MineV1LevelIO>()
        );

        // minev2
        level::conversion::level::LevelIORegistry::sInstance.registerLevelIO(
            identifiers::MINEV2,
            std::make_unique<classic::minev2::MineV2LevelIO>()
        );

        level::conversion::world::WorldIORegistry::sInstance.registerWorldIO(
            identifiers::MINEV2,
            std::make_unique<classic::minev2::MineV2WorldIO>()
        );

        // indev
        level::conversion::level::LevelIORegistry::sInstance.registerLevelIO(
            identifiers::MCLEVEL,
            std::make_unique<indev::McLevelLevelIO>()
        );

        // mcr
        level::conversion::chunk::ChunkIORegistry::sInstance.registerChunkIO(
            identifiers::MCREGION,
            std::make_unique<mcr::chunk::McRegionChunkIO>()
        );

        level::conversion::region::RegionIORegistry::sInstance.registerRegionIO(
            identifiers::MCREGION,
            std::make_unique<mcr::region::McRegionRegionIO>()
        );
    }

    LodestoneJava *LodestoneJava::getInstance() {
        return sInstance;
    }

    void LodestoneJava::init() {
        if (sInstance != nullptr) return;

        sInstance = new LodestoneJava();
    }

    void LodestoneJava::initBlocks() {
        io.registerBlock(Version::caveGame, &level::block::Blocks::AIR,
                         new level::conversion::block::data::ClassicBlockData(0));
        io.registerBlock(Version::caveGame, &level::block::Blocks::STONE,
                         new level::conversion::block::data::ClassicBlockData(1));
        io.registerBlock(Version::caveGame, &level::block::Blocks::GRASS_BLOCK,
                         new level::conversion::block::data::ClassicBlockData(2));
        io.registerBlock(Version::rd20090515, &level::block::Blocks::DIRT,
                         new level::conversion::block::data::ClassicBlockData(3));
        io.registerBlock(Version::rd20090515, &level::block::Blocks::COBBLESTONE,
                         new level::conversion::block::data::ClassicBlockData(4));
        io.registerBlock(Version::rd20090515, &level::block::Blocks::OAK_PLANKS,
                         new level::conversion::block::data::ClassicBlockData(5));
        io.registerBlock(Version::rd161348, &level::block::Blocks::OAK_SAPLING,
                         new level::conversion::block::data::ClassicBlockData(6));
        io.registerBlock(Version::c0_0_12a, &level::block::Blocks::BEDROCK,
                         new level::conversion::block::data::ClassicBlockData(7));

        io.registerBlock(Version::b1_3, &level::block::Blocks::AIR,
                         new level::conversion::block::data::NumericBlockData(0, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::STONE,
                         new level::conversion::block::data::NumericBlockData(1, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::GRASS_BLOCK,
                         new level::conversion::block::data::NumericBlockData(2, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::DIRT,
                         new level::conversion::block::data::NumericBlockData(3, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::COBBLESTONE,
                         new level::conversion::block::data::NumericBlockData(4, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::OAK_PLANKS,
                         new level::conversion::block::data::NumericBlockData(5, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::OAK_SAPLING,
                         new level::conversion::block::data::NumericBlockData(6, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::BEDROCK,
                         new level::conversion::block::data::NumericBlockData(7, 0));
    }
}
