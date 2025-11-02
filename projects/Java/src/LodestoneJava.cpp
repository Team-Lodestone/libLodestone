//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//

#include <Lodestone.Level/Conversion/Level/LevelIORegistry.h>

#include "Classic/MineV1/MineV1LevelIO.h"
#include "Classic/MineV2/MineV2LevelIO.h"
#include "Indev/McLevelLevelIO.h"
#include "LodestoneJava.h"

#include "Version.h"
#include "Lodestone.Level/Conversion/Block/BlockIO.h"
#include "Lodestone.Level/Conversion/Block/VersionedBlockIO.h"
#include "Lodestone.Level/Conversion/Block/data/ClassicBlockData.h"

namespace lodestone::java {
    LodestoneJava *LodestoneJava::sInstance = nullptr;

    LodestoneJava::LodestoneJava() {
        this->io = lodestone::level::conversion::block::version::VersionedBlockIO();
        initBlocks();

        level::conversion::level::LevelIORegistry::sInstance.registerLevelIO(
            classic::minev1::MineV1LevelIO::NAME,
            std::make_unique<classic::minev1::MineV1LevelIO>()
        );

        level::conversion::level::LevelIORegistry::sInstance.registerLevelIO(
            classic::minev2::MineV2LevelIO::NAME,
            std::make_unique<classic::minev2::MineV2LevelIO>()
        );

        level::conversion::level::LevelIORegistry::sInstance.registerLevelIO(
            indev::McLevelLevelIO::NAME,
            std::make_unique<indev::McLevelLevelIO>()
        );
    }

    LodestoneJava * LodestoneJava::getInstance() {
        return sInstance;
    }

    void LodestoneJava::init() {
        if (sInstance != nullptr) return;

        sInstance = new LodestoneJava();
    }

    void LodestoneJava::initBlocks() {
        io.registerBlock(Version::caveGame,{"lodestone", "air"}, new level::conversion::block::data::ClassicBlockData(0));
        io.registerBlock(Version::caveGame,{"lodestone", "stone"}, new level::conversion::block::data::ClassicBlockData(1));
        io.registerBlock(Version::caveGame,{"lodestone", "grass_block"}, new level::conversion::block::data::ClassicBlockData(2));
        io.registerBlock(Version::rd20090515,{"lodestone", "dirt"}, new level::conversion::block::data::ClassicBlockData(3));
        io.registerBlock(Version::rd20090515,{"lodestone", "cobblestone"}, new level::conversion::block::data::ClassicBlockData(4));
        io.registerBlock(Version::rd20090515,{"lodestone", "oak_planks"}, new level::conversion::block::data::ClassicBlockData(5));
        io.registerBlock(Version::rd161348,{"lodestone", "oak_sapling"}, new level::conversion::block::data::ClassicBlockData(6));
        io.registerBlock(Version::c0_0_12a,{"lodestone", "bedrock"}, new level::conversion::block::data::ClassicBlockData(7));
    }
}
