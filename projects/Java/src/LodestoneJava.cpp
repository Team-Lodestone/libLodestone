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
        io.registerBlock(Version::rd131655, &level::block::Blocks::AIR, new level::conversion::block::data::ClassicBlockData(0));
        io.registerBlock(Version::rd131655, &level::block::Blocks::STONE, new level::conversion::block::data::ClassicBlockData(1));
        io.registerBlock(Version::rd131655, &level::block::Blocks::GRASS_BLOCK, new level::conversion::block::data::ClassicBlockData(2));
        io.registerBlock(Version::rd20090515, &level::block::Blocks::DIRT, new level::conversion::block::data::ClassicBlockData(3));
        io.registerBlock(Version::rd20090515, &level::block::Blocks::COBBLESTONE, new level::conversion::block::data::ClassicBlockData(4));
        io.registerBlock(Version::rd20090515, &level::block::Blocks::OAK_PLANKS, new level::conversion::block::data::ClassicBlockData(5));
        io.registerBlock(Version::rd161348, &level::block::Blocks::OAK_SAPLING, new level::conversion::block::data::ClassicBlockData(6));
        io.registerBlock(Version::c0_0_12a, &level::block::Blocks::BEDROCK, new level::conversion::block::data::ClassicBlockData(7));
        io.registerBlock(Version::c0_0_12a, &level::block::Blocks::FLOWING_WATER, new level::conversion::block::data::ClassicBlockData(8));
        io.registerBlock(Version::c0_0_12a, &level::block::Blocks::WATER, new level::conversion::block::data::ClassicBlockData(9));
        io.registerBlock(Version::c0_0_12a, &level::block::Blocks::FLOWING_LAVA, new level::conversion::block::data::ClassicBlockData(10));
        io.registerBlock(Version::c0_0_12a, &level::block::Blocks::LAVA, new level::conversion::block::data::ClassicBlockData(11));
        io.registerBlock(Version::c0_0_14a, &level::block::Blocks::SAND, new level::conversion::block::data::ClassicBlockData(12));
        io.registerBlock(Version::c0_0_14a, &level::block::Blocks::GRAVEL, new level::conversion::block::data::ClassicBlockData(13));
        io.registerBlock(Version::c0_0_14a, &level::block::Blocks::GOLD_ORE, new level::conversion::block::data::ClassicBlockData(14));
        io.registerBlock(Version::c0_0_14a, &level::block::Blocks::IRON_ORE, new level::conversion::block::data::ClassicBlockData(15));
        io.registerBlock(Version::c0_0_14a, &level::block::Blocks::COAL_ORE, new level::conversion::block::data::ClassicBlockData(16));
        io.registerBlock(Version::c0_0_14a, &level::block::Blocks::OAK_LOG, new level::conversion::block::data::ClassicBlockData(17));
        io.registerBlock(Version::c0_0_14a, &level::block::Blocks::OAK_LEAVES, new level::conversion::block::data::ClassicBlockData(18));
        io.registerBlock(Version::c0_0_19a, &level::block::Blocks::SPONGE, new level::conversion::block::data::ClassicBlockData(19));
        io.registerBlock(Version::c0_0_19a, &level::block::Blocks::GLASS, new level::conversion::block::data::ClassicBlockData(20));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::RED_WOOL, new level::conversion::block::data::ClassicBlockData(21));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::ORANGE_WOOL, new level::conversion::block::data::ClassicBlockData(22));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::YELLOW_WOOL, new level::conversion::block::data::ClassicBlockData(23));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::CHARTREUSE_WOOL, new level::conversion::block::data::ClassicBlockData(24));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::LIME_WOOL, new level::conversion::block::data::ClassicBlockData(25));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::SPRING_GREEN_WOOL, new level::conversion::block::data::ClassicBlockData(26));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::CYAN_WOOL, new level::conversion::block::data::ClassicBlockData(27));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::LIGHT_BLUE_WOOL, new level::conversion::block::data::ClassicBlockData(28));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::ULTRAMARINE_WOOL, new level::conversion::block::data::ClassicBlockData(29));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::PURPLE_WOOL, new level::conversion::block::data::ClassicBlockData(30));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::VIOLET_WOOL, new level::conversion::block::data::ClassicBlockData(31));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::MAGENTA_WOOL, new level::conversion::block::data::ClassicBlockData(32));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::PINK_WOOL, new level::conversion::block::data::ClassicBlockData(33));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::GRAY_WOOL, new level::conversion::block::data::ClassicBlockData(34));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::LIGHT_GRAY_WOOL, new level::conversion::block::data::ClassicBlockData(35));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::WHITE_WOOL, new level::conversion::block::data::ClassicBlockData(36));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::DANDELION, new level::conversion::block::data::ClassicBlockData(37));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::POPPY, new level::conversion::block::data::ClassicBlockData(38));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::BROWN_MUSHROOM, new level::conversion::block::data::ClassicBlockData(39));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::RED_MUSHROOM, new level::conversion::block::data::ClassicBlockData(40));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::GOLD_BLOCK, new level::conversion::block::data::ClassicBlockData(41));
        io.registerBlock(Version::c0_26st, &level::block::Blocks::IRON_BLOCK, new level::conversion::block::data::ClassicBlockData(42));
        io.registerBlock(Version::c0_26st, &level::block::Blocks::DOUBLE_SMOOTH_STONE_SLAB, new level::conversion::block::data::ClassicBlockData(43));
        io.registerBlock(Version::c0_26st, &level::block::Blocks::SMOOTH_STONE_SLAB, new level::conversion::block::data::ClassicBlockData(44));
        io.registerBlock(Version::c0_26st, &level::block::Blocks::BRICKS, new level::conversion::block::data::ClassicBlockData(45));
        io.registerBlock(Version::c0_26st, &level::block::Blocks::TNT, new level::conversion::block::data::ClassicBlockData(46));
        io.registerBlock(Version::c0_26st, &level::block::Blocks::BOOKSHELF, new level::conversion::block::data::ClassicBlockData(47));
        io.registerBlock(Version::c0_26st, &level::block::Blocks::MOSSY_COBBLESTONE, new level::conversion::block::data::ClassicBlockData(48));
        io.registerBlock(Version::c0_28, &level::block::Blocks::OBSIDIAN, new level::conversion::block::data::ClassicBlockData(49));

        // TODO sometime we need to implement item conversion too

        // ID FORMAT CHANGE
        io.registerBlock(Version::b1_3, &level::block::Blocks::AIR, new level::conversion::block::data::NumericBlockData(0, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::STONE, new level::conversion::block::data::NumericBlockData(1, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::GRASS_BLOCK, new level::conversion::block::data::NumericBlockData(2, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::DIRT, new level::conversion::block::data::NumericBlockData(3, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::COBBLESTONE, new level::conversion::block::data::NumericBlockData(4, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::OAK_PLANKS, new level::conversion::block::data::NumericBlockData(5, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::OAK_SAPLING, new level::conversion::block::data::NumericBlockData(6, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::BEDROCK, new level::conversion::block::data::NumericBlockData(7, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::FLOWING_WATER, new level::conversion::block::data::NumericBlockData(8, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::WATER, new level::conversion::block::data::NumericBlockData(9, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::FLOWING_LAVA, new level::conversion::block::data::NumericBlockData(10, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::LAVA, new level::conversion::block::data::NumericBlockData(11, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::SAND, new level::conversion::block::data::NumericBlockData(12, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::GRAVEL, new level::conversion::block::data::NumericBlockData(13, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::GOLD_ORE, new level::conversion::block::data::NumericBlockData(14, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::IRON_ORE, new level::conversion::block::data::NumericBlockData(15, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::COAL_ORE, new level::conversion::block::data::NumericBlockData(16, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::OAK_LOG, new level::conversion::block::data::NumericBlockData(17, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::OAK_LEAVES, new level::conversion::block::data::NumericBlockData(18, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::SPONGE, new level::conversion::block::data::NumericBlockData(19, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::GLASS, new level::conversion::block::data::NumericBlockData(20, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::DANDELION, new level::conversion::block::data::NumericBlockData(37, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::POPPY, new level::conversion::block::data::NumericBlockData(38, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::BROWN_MUSHROOM, new level::conversion::block::data::NumericBlockData(39, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::RED_MUSHROOM, new level::conversion::block::data::NumericBlockData(40, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::GOLD_BLOCK, new level::conversion::block::data::NumericBlockData(41, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::IRON_BLOCK, new level::conversion::block::data::NumericBlockData(42, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::DOUBLE_SMOOTH_STONE_SLAB, new level::conversion::block::data::NumericBlockData(43, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::SMOOTH_STONE_SLAB, new level::conversion::block::data::NumericBlockData(44, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::BRICKS, new level::conversion::block::data::NumericBlockData(45, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::TNT, new level::conversion::block::data::NumericBlockData(46, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::BOOKSHELF, new level::conversion::block::data::NumericBlockData(47, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::MOSSY_COBBLESTONE, new level::conversion::block::data::NumericBlockData(48, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::OBSIDIAN, new level::conversion::block::data::NumericBlockData(49, 0));

    }
}
