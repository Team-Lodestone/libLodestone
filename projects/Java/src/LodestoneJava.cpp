//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//

#include <Lodestone.Conversion/level/LevelIORegistry.h>

#include "Lodestone.Java/LodestoneJava.h"
#include "Lodestone.Java/classic/minev1/MineV1LevelIO.h"
#include "Lodestone.Java/classic/minev2/MineV2LevelIO.h"
#include "Lodestone.Java/indev/McLevelLevelIO.h"

#include "Lodestone.Java/Identifiers.h"
#include "Lodestone.Java/Version.h"
#include "Lodestone.Java/classic/minev2/MineV2WorldIo.h"
#include <Lodestone.Conversion/block/BlockIO.h>
#include <Lodestone.Conversion/block/VersionedBlockIO.h>
#include <Lodestone.Conversion/block/data/ClassicBlockData.h>
#include <Lodestone.Conversion/block/data/NumericBlockData.h>
#include <Lodestone.Conversion/chunk/ChunkIORegistry.h>
#include <Lodestone.Conversion/region/RegionIORegistry.h>
#include <Lodestone.Conversion/world/WorldIORegistry.h>

#include <Lodestone.Conversion/player/PlayerIORegistry.h>

#include <Lodestone.Core/Lodestone.h>
#include "Lodestone.Java/mcr/chunk/McRegionChunkIo.h"
#include "Lodestone.Java/mcr/player/McRegionPlayerIo.h"
#include "Lodestone.Java/mcr/region/McRegionRegionIo.h"
#include "Lodestone.Java/mcr/world/McRegionWorldIo.h"

namespace lodestone::java {
    LodestoneJava::LodestoneJava() {
        this->io = lodestone::conversion::block::version::VersionedBlockIO();
        initBlocks();

        // mine v1
        lodestone::conversion::level::LevelIoRegistry::getInstance().registerLevelIO(
            identifiers::MINEV1,
            std::make_unique<classic::minev1::MineV1LevelIO>()
        );

        // minev2
        lodestone::conversion::level::LevelIoRegistry::getInstance().registerLevelIO(
            identifiers::MINEV2,
            std::make_unique<classic::minev2::MineV2LevelIO>()
        );

        lodestone::conversion::world::WorldIORegistry::getInstance()
            .registerWorldIO(
                identifiers::MINEV2,
                std::make_unique<classic::minev2::MineV2WorldIO>());

        // indev
        lodestone::conversion::level::LevelIoRegistry::getInstance().registerLevelIO(
            identifiers::MCLEVEL,
            std::make_unique<indev::McLevelLevelIO>()
        );

        // mcr
        lodestone::conversion::chunk::ChunkIORegistry::getInstance()
            .registerChunkIO(identifiers::MCREGION,
                             std::make_unique<mcr::chunk::McRegionChunkIO>());

        lodestone::conversion::region::RegionIORegistry::getInstance()
            .registerRegionIO(
                identifiers::MCREGION,
                std::make_unique<mcr::region::McRegionRegionIO>());

        lodestone::conversion::world::WorldIORegistry::getInstance()
            .registerWorldIO(identifiers::MCREGION,
                             std::make_unique<mcr::world::McRegionWorldIo>());

        lodestone::conversion::player::PlayerIORegistry::getInstance()
            .registerPlayerIO(
                identifiers::MCREGION,
                std::make_unique<mcr::player::McRegionPlayerIO>());
    }

    LodestoneJava *LodestoneJava::getInstance() {
        static LodestoneJava sInstance;
        return &sInstance;
    }

    void LodestoneJava::init() {
        core::Lodestone::getInstance()->registerExtension(getInstance());
    }

    void LodestoneJava::initBlocks() {
        io.registerBlock(Version::rd131655, &level::block::Blocks::AIR, new lodestone::conversion::block::data::ClassicBlockData(0));
        io.registerBlock(Version::rd131655, &level::block::Blocks::STONE, new lodestone::conversion::block::data::ClassicBlockData(1));
        io.registerBlock(Version::rd131655, &level::block::Blocks::GRASS_BLOCK, new lodestone::conversion::block::data::ClassicBlockData(2));
        io.registerBlock(Version::rd20090515, &level::block::Blocks::DIRT, new lodestone::conversion::block::data::ClassicBlockData(3));
        io.registerBlock(Version::rd20090515, &level::block::Blocks::COBBLESTONE, new lodestone::conversion::block::data::ClassicBlockData(4));
        io.registerBlock(Version::rd20090515, &level::block::Blocks::OAK_PLANKS, new lodestone::conversion::block::data::ClassicBlockData(5));
        io.registerBlock(Version::rd161348, &level::block::Blocks::OAK_SAPLING, new lodestone::conversion::block::data::ClassicBlockData(6));
        io.registerBlock(Version::c0_0_12a, &level::block::Blocks::BEDROCK, new lodestone::conversion::block::data::ClassicBlockData(7));
        io.registerBlock(Version::c0_0_12a, &level::block::Blocks::FLOWING_WATER, new lodestone::conversion::block::data::ClassicBlockData(8));
        io.registerBlock(Version::c0_0_12a, &level::block::Blocks::WATER, new lodestone::conversion::block::data::ClassicBlockData(9));
        io.registerBlock(Version::c0_0_12a, &level::block::Blocks::FLOWING_LAVA, new lodestone::conversion::block::data::ClassicBlockData(10));
        io.registerBlock(Version::c0_0_12a, &level::block::Blocks::LAVA, new lodestone::conversion::block::data::ClassicBlockData(11));
        io.registerBlock(Version::c0_0_14a, &level::block::Blocks::SAND, new lodestone::conversion::block::data::ClassicBlockData(12));
        io.registerBlock(Version::c0_0_14a, &level::block::Blocks::GRAVEL, new lodestone::conversion::block::data::ClassicBlockData(13));
        io.registerBlock(Version::c0_0_14a, &level::block::Blocks::GOLD_ORE, new lodestone::conversion::block::data::ClassicBlockData(14));
        io.registerBlock(Version::c0_0_14a, &level::block::Blocks::IRON_ORE, new lodestone::conversion::block::data::ClassicBlockData(15));
        io.registerBlock(Version::c0_0_14a, &level::block::Blocks::COAL_ORE, new lodestone::conversion::block::data::ClassicBlockData(16));
        io.registerBlock(Version::c0_0_14a, &level::block::Blocks::OAK_LOG, new lodestone::conversion::block::data::ClassicBlockData(17));
        io.registerBlock(Version::c0_0_14a, &level::block::Blocks::OAK_LEAVES, new lodestone::conversion::block::data::ClassicBlockData(18));
        io.registerBlock(Version::c0_0_19a, &level::block::Blocks::SPONGE, new lodestone::conversion::block::data::ClassicBlockData(19));
        io.registerBlock(Version::c0_0_19a, &level::block::Blocks::GLASS, new lodestone::conversion::block::data::ClassicBlockData(20));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::RED_WOOL, new lodestone::conversion::block::data::ClassicBlockData(21));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::ORANGE_WOOL, new lodestone::conversion::block::data::ClassicBlockData(22));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::YELLOW_WOOL, new lodestone::conversion::block::data::ClassicBlockData(23));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::CHARTREUSE_WOOL, new lodestone::conversion::block::data::ClassicBlockData(24));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::LIME_WOOL, new lodestone::conversion::block::data::ClassicBlockData(25));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::SPRING_GREEN_WOOL, new lodestone::conversion::block::data::ClassicBlockData(26));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::CYAN_WOOL, new lodestone::conversion::block::data::ClassicBlockData(27));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::LIGHT_BLUE_WOOL, new lodestone::conversion::block::data::ClassicBlockData(28));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::ULTRAMARINE_WOOL, new lodestone::conversion::block::data::ClassicBlockData(29));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::PURPLE_WOOL, new lodestone::conversion::block::data::ClassicBlockData(30));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::VIOLET_WOOL, new lodestone::conversion::block::data::ClassicBlockData(31));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::MAGENTA_WOOL, new lodestone::conversion::block::data::ClassicBlockData(32));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::PINK_WOOL, new lodestone::conversion::block::data::ClassicBlockData(33));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::GRAY_WOOL, new lodestone::conversion::block::data::ClassicBlockData(34));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::LIGHT_GRAY_WOOL, new lodestone::conversion::block::data::ClassicBlockData(35));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::WHITE_WOOL, new lodestone::conversion::block::data::ClassicBlockData(36));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::DANDELION, new lodestone::conversion::block::data::ClassicBlockData(37));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::POPPY, new lodestone::conversion::block::data::ClassicBlockData(38));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::BROWN_MUSHROOM, new lodestone::conversion::block::data::ClassicBlockData(39));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::RED_MUSHROOM, new lodestone::conversion::block::data::ClassicBlockData(40));
        io.registerBlock(Version::c0_0_20a, &level::block::Blocks::GOLD_BLOCK, new lodestone::conversion::block::data::ClassicBlockData(41));
        io.registerBlock(Version::c0_26st, &level::block::Blocks::IRON_BLOCK, new lodestone::conversion::block::data::ClassicBlockData(42));
        io.registerBlock(Version::c0_26st, &level::block::Blocks::DOUBLE_SMOOTH_STONE_SLAB, new lodestone::conversion::block::data::ClassicBlockData(43));
        io.registerBlock(Version::c0_26st, &level::block::Blocks::SMOOTH_STONE_SLAB, new lodestone::conversion::block::data::ClassicBlockData(44));
        io.registerBlock(Version::c0_26st, &level::block::Blocks::BRICKS, new lodestone::conversion::block::data::ClassicBlockData(45));
        io.registerBlock(Version::c0_26st, &level::block::Blocks::TNT, new lodestone::conversion::block::data::ClassicBlockData(46));
        io.registerBlock(Version::c0_26st, &level::block::Blocks::BOOKSHELF, new lodestone::conversion::block::data::ClassicBlockData(47));
        io.registerBlock(Version::c0_26st, &level::block::Blocks::MOSSY_COBBLESTONE, new lodestone::conversion::block::data::ClassicBlockData(48));
        io.registerBlock(Version::c0_28, &level::block::Blocks::OBSIDIAN, new lodestone::conversion::block::data::ClassicBlockData(49));
        // CPE specific
        io.registerBlock(Version::c0_30_CPE, &level::block::Blocks::COBBLESTONE_SLAB, new lodestone::conversion::block::data::ClassicBlockData(50));
        io.registerBlock(Version::c0_30_CPE, &level::block::Blocks::ROPE, new lodestone::conversion::block::data::ClassicBlockData(51));
        io.registerBlock(Version::c0_30_CPE, &level::block::Blocks::SANDSTONE, new lodestone::conversion::block::data::ClassicBlockData(52));
        io.registerBlock(Version::c0_30_CPE, &level::block::Blocks::SNOW_LAYER, new lodestone::conversion::block::data::ClassicBlockData(53));
        io.registerBlock(Version::c0_30_CPE, &level::block::Blocks::FIRE, new lodestone::conversion::block::data::ClassicBlockData(54));
        io.registerBlock(Version::c0_30_CPE, &level::block::Blocks::ICE, new lodestone::conversion::block::data::ClassicBlockData(60));
        io.registerBlock(Version::c0_30_CPE, &level::block::Blocks::CERAMIC_TILE, new lodestone::conversion::block::data::ClassicBlockData(61));
        io.registerBlock(Version::c0_30_CPE, &level::block::Blocks::MAGMA_BLOCK, new lodestone::conversion::block::data::ClassicBlockData(62));
        io.registerBlock(Version::c0_30_CPE, &level::block::Blocks::QUARTZ_PILLAR, new lodestone::conversion::block::data::ClassicBlockData(63));
        io.registerBlock(Version::c0_30_CPE, &level::block::Blocks::CRATE, new lodestone::conversion::block::data::ClassicBlockData(64));
        io.registerBlock(Version::c0_30_CPE, &level::block::Blocks::STONE_BRICKS, new lodestone::conversion::block::data::ClassicBlockData(65));

        // Remove the cpe specific blocks because they didn't exist here
        io.removeBlock(Version::in20091223_1457, &level::block::Blocks::COBBLESTONE_SLAB);
        io.removeBlock(Version::in20091223_1457, &level::block::Blocks::ROPE);
        io.removeBlock(Version::in20091223_1457, &level::block::Blocks::SANDSTONE);
        io.removeBlock(Version::in20091223_1457, &level::block::Blocks::SNOW_LAYER);
        io.removeBlock(Version::in20091223_1457, &level::block::Blocks::FIRE);
        io.removeBlock(Version::in20091223_1457, &level::block::Blocks::ICE);
        io.removeBlock(Version::in20091223_1457, &level::block::Blocks::CERAMIC_TILE);
        io.removeBlock(Version::in20091223_1457, &level::block::Blocks::MAGMA_BLOCK);
        io.removeBlock(Version::in20091223_1457, &level::block::Blocks::QUARTZ_PILLAR);
        io.removeBlock(Version::in20091223_1457, &level::block::Blocks::CRATE);
        io.removeBlock(Version::in20091223_1457, &level::block::Blocks::STONE_BRICKS);

        io.registerBlock(Version::in20091223_1457, &level::block::Blocks::TORCH, new lodestone::conversion::block::data::ClassicBlockData(50));
        io.registerBlock(Version::in20100109_1939, &level::block::Blocks::FIRE, new lodestone::conversion::block::data::ClassicBlockData(51));
        io.registerBlock(Version::in20100114, &level::block::Blocks::WATER_SPAWNER, new lodestone::conversion::block::data::ClassicBlockData(52));
        io.registerBlock(Version::in20100122_2251, &level::block::Blocks::LAVA_SPAWNER, new lodestone::conversion::block::data::ClassicBlockData(53));
        io.registerBlock(Version::in20100124_2119, &level::block::Blocks::CHEST, new lodestone::conversion::block::data::ClassicBlockData(54));
        io.registerBlock(Version::in20100128_2200, &level::block::Blocks::GEAR, new lodestone::conversion::block::data::ClassicBlockData(55));
        io.registerBlock(Version::in20100128_2200, &level::block::Blocks::DIAMOND_ORE, new lodestone::conversion::block::data::ClassicBlockData(56));
        io.registerBlock(Version::in20100128_2200, &level::block::Blocks::DIAMOND_BLOCK, new lodestone::conversion::block::data::ClassicBlockData(57));
        io.registerBlock(Version::in20100129_2332, &level::block::Blocks::CRAFTING_TABLE, new lodestone::conversion::block::data::ClassicBlockData(58));
        io.registerBlock(Version::in20100206_2034, &level::block::Blocks::WHEAT, new lodestone::conversion::block::data::ClassicBlockData(59));
        io.registerBlock(Version::in20100206_2034, &level::block::Blocks::FARMLAND, new lodestone::conversion::block::data::ClassicBlockData(60));
        io.registerBlock(Version::in20100219, &level::block::Blocks::FURNACE, new lodestone::conversion::block::data::ClassicBlockData(61));
        io.registerBlock(Version::in20100219, &level::block::Blocks::LIT_FURNACE, new lodestone::conversion::block::data::ClassicBlockData(62));

        // TODO sometime we need to implement item conversion too

        // ID FORMAT CHANGE
        io.registerBlock(Version::b1_3, &level::block::Blocks::AIR, new lodestone::conversion::block::data::NumericBlockData(0, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::STONE, new lodestone::conversion::block::data::NumericBlockData(1, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::GRASS_BLOCK, new lodestone::conversion::block::data::NumericBlockData(2, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::DIRT, new lodestone::conversion::block::data::NumericBlockData(3, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::COBBLESTONE, new lodestone::conversion::block::data::NumericBlockData(4, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::OAK_PLANKS, new lodestone::conversion::block::data::NumericBlockData(5, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::OAK_SAPLING, new lodestone::conversion::block::data::NumericBlockData(6, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::BEDROCK, new lodestone::conversion::block::data::NumericBlockData(7, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::FLOWING_WATER, new lodestone::conversion::block::data::NumericBlockData(8, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::WATER, new lodestone::conversion::block::data::NumericBlockData(9, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::FLOWING_LAVA, new lodestone::conversion::block::data::NumericBlockData(10, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::LAVA, new lodestone::conversion::block::data::NumericBlockData(11, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::SAND, new lodestone::conversion::block::data::NumericBlockData(12, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::GRAVEL, new lodestone::conversion::block::data::NumericBlockData(13, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::GOLD_ORE, new lodestone::conversion::block::data::NumericBlockData(14, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::IRON_ORE, new lodestone::conversion::block::data::NumericBlockData(15, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::COAL_ORE, new lodestone::conversion::block::data::NumericBlockData(16, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::OAK_LOG, new lodestone::conversion::block::data::NumericBlockData(17, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::OAK_LEAVES, new lodestone::conversion::block::data::NumericBlockData(18, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::SPONGE, new lodestone::conversion::block::data::NumericBlockData(19, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::GLASS, new lodestone::conversion::block::data::NumericBlockData(20, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::DANDELION, new lodestone::conversion::block::data::NumericBlockData(37, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::POPPY, new lodestone::conversion::block::data::NumericBlockData(38, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::BROWN_MUSHROOM, new lodestone::conversion::block::data::NumericBlockData(39, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::RED_MUSHROOM, new lodestone::conversion::block::data::NumericBlockData(40, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::GOLD_BLOCK, new lodestone::conversion::block::data::NumericBlockData(41, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::IRON_BLOCK, new lodestone::conversion::block::data::NumericBlockData(42, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::DOUBLE_SMOOTH_STONE_SLAB, new lodestone::conversion::block::data::NumericBlockData(43, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::SMOOTH_STONE_SLAB, new lodestone::conversion::block::data::NumericBlockData(44, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::BRICKS, new lodestone::conversion::block::data::NumericBlockData(45, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::TNT, new lodestone::conversion::block::data::NumericBlockData(46, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::BOOKSHELF, new lodestone::conversion::block::data::NumericBlockData(47, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::MOSSY_COBBLESTONE, new lodestone::conversion::block::data::NumericBlockData(48, 0));
        io.registerBlock(Version::b1_3, &level::block::Blocks::OBSIDIAN, new lodestone::conversion::block::data::NumericBlockData(49, 0));
    }

    common::registry::Identifier LodestoneJava::getIdentifier() {
        return {"lodestone", "java"};
    }
} // namespace lodestone::java
