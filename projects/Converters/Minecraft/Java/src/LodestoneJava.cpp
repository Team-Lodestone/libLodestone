//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//

#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/LodestoneJava.h"

#include "Lodestone.Minecraft.Java/conversion/classic/minev2/MineV2LevelIO.h"
#include <Lodestone.Conversion/block/data/ExtendedNumericBlockData.h>

#include <Lodestone.Core/Lodestone.h>

#include <Lodestone.Minecraft.Common/LodestoneMinecraftCommon.h>

#include <Lodestone.Minecraft.Common/block/Blocks.h>

#include "Lodestone.Minecraft.Java/Version.h"
#include "Lodestone.Minecraft.Java/conversion/alpha/AlphaPlayerIo.h"
#include "Lodestone.Minecraft.Java/conversion/alpha/AlphaWorldIo.h"
#include "Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilChunkIo.h"
#include "Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilRegionIo.h"
#include "Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilWorldIo.h"
#include "Lodestone.Minecraft.Java/conversion/classic/minev1/MineV1LevelIO.h"
#include "Lodestone.Minecraft.Java/conversion/classic/minev2/MineV2WorldIo.h"
#include "Lodestone.Minecraft.Java/conversion/indev/McLevelLevelIO.h"
#include "Lodestone.Minecraft.Java/conversion/mcregion/McRegionChunkIo.h"
#include "Lodestone.Minecraft.Java/conversion/mcregion/McRegionPlayerIo.h"
#include "Lodestone.Minecraft.Java/conversion/mcregion/McRegionRegionIo.h"
#include "Lodestone.Minecraft.Java/conversion/mcregion/McRegionWorldIo.h"
#include <Lodestone.Conversion/block/data/ClassicBlockData.h>
#include <Lodestone.Conversion/block/data/NumericBlockData.h>

#include <Lodestone.Conversion/registry/Registries.h>
#include <Lodestone.Minecraft.Common/conversion/registry/Registries.h>
#include <Lodestone.Minecraft.Common/conversion/io/ObjectIOs.h>
#include <Lodestone.Conversion/io/ObjectIOs.h>

#include "Lodestone.Minecraft.Java/conversion/infdev/InfdevWorldIo.h"

namespace lodestone::minecraft::java {
#define REG_PUT(r, n) lodestone::conversion::registry::r::getInstance().put(*n::getIdentifier(), std::make_unique<n>())

    LodestoneJava::LodestoneJava() {
        this->m_blockIo = lodestone::conversion::block::version::VersionedBlockIO();
        initBlocks();
        initItems();

        // classic
        // minev1
        REG_PUT(LevelIORegistry, classic::minev1::MineV1LevelIO);

        // minev2
        REG_PUT(LevelIORegistry, classic::minev2::MineV2LevelIO);
        REG_PUT(WorldIORegistry, classic::minev2::MineV2WorldIO);

        // indev
        REG_PUT(LevelIORegistry, indev::McLevelLevelIO);
        REG_PUT(LevelIORegistry, indev::McLevelNbtLevelIO);

        // infdev 20100624
        REG_PUT(ChunkIORegistry, infdev::chunk::InfdevChunkIO);
        REG_PUT(LevelIORegistry, infdev::zone::InfdevZoneIo);
        REG_PUT(WorldIORegistry, infdev::world::InfdevWorldIo);

        // alpha
        REG_PUT(WorldIORegistry, alpha::world::AlphaWorldIo);
        REG_PUT(PlayerIORegistry, alpha::player::AlphaPlayerIO);
        REG_PUT(PlayerIORegistry, alpha::player::AlphaNbtPlayerIO);

        // mcr
        REG_PUT(PlayerIORegistry, mcregion::player::McRegionNbtPlayerIO);
        REG_PUT(PlayerIORegistry, mcregion::player::McRegionPlayerIO);
        REG_PUT(ChunkIORegistry, mcregion::chunk::McRegionChunkIO);
        REG_PUT(ChunkIORegistry, mcregion::chunk::McRegionNbtChunkIO);
        REG_PUT(RegionIORegistry, mcregion::region::McRegionRegionIO);
        REG_PUT(WorldIORegistry, mcregion::world::McRegionWorldIo);

        // anvil
        // jungle (1.2.1-1.12.2)
        REG_PUT(ChunkIORegistry, anvil::jungle::chunk::JungleAnvilChunkIO);
        REG_PUT(ChunkIORegistry, anvil::jungle::chunk::JungleAnvilNbtChunkIO);
        REG_PUT(RegionIORegistry, anvil::jungle::region::JungleAnvilRegionIO);
        REG_PUT(WorldIORegistry, anvil::jungle::world::JungleAnvilWorldIo);
    }

    LodestoneJava *LodestoneJava::getInstance() {
        static LodestoneJava s_instance;
        return &s_instance;
    }

    void LodestoneJava::initBlocks() {
        common::LodestoneMinecraftCommon::initBlocks();
        m_blockIo.registerBlock(
            Version::rd131655, &level::block::Blocks::NONE,
            new lodestone::conversion::block::data::ClassicBlockData(0));
        m_blockIo.registerBlock(
            Version::rd131655, &minecraft::common::block::Blocks::STONE,
            new lodestone::conversion::block::data::ClassicBlockData(1));
        m_blockIo.registerBlock(
            Version::rd131655, &minecraft::common::block::Blocks::GRASS_BLOCK,
            new lodestone::conversion::block::data::ClassicBlockData(2));
        m_blockIo.registerBlock(
            Version::rd20090515, &minecraft::common::block::Blocks::DIRT,
            new lodestone::conversion::block::data::ClassicBlockData(3));
        m_blockIo.registerBlock(
            Version::rd20090515, &minecraft::common::block::Blocks::COBBLESTONE,
            new lodestone::conversion::block::data::ClassicBlockData(4));
        m_blockIo.registerBlock(
            Version::rd20090515, &minecraft::common::block::Blocks::OAK_PLANKS,
            new lodestone::conversion::block::data::ClassicBlockData(5));
        m_blockIo.registerBlock(
            Version::rd161348, &minecraft::common::block::Blocks::OAK_SAPLING,
            new lodestone::conversion::block::data::ClassicBlockData(6));
        m_blockIo.registerBlock(
            Version::c0_0_12a, &minecraft::common::block::Blocks::BEDROCK,
            new lodestone::conversion::block::data::ClassicBlockData(7));
        m_blockIo.registerBlock(
            Version::c0_0_12a, &minecraft::common::block::Blocks::FLOWING_WATER,
            new lodestone::conversion::block::data::ClassicBlockData(8));
        m_blockIo.registerBlock(
            Version::c0_0_12a, &minecraft::common::block::Blocks::WATER,
            new lodestone::conversion::block::data::ClassicBlockData(9));
        m_blockIo.registerBlock(
            Version::c0_0_12a, &minecraft::common::block::Blocks::FLOWING_LAVA,
            new lodestone::conversion::block::data::ClassicBlockData(10));
        m_blockIo.registerBlock(
            Version::c0_0_12a, &minecraft::common::block::Blocks::LAVA,
            new lodestone::conversion::block::data::ClassicBlockData(11));
        m_blockIo.registerBlock(
            Version::c0_0_14a, &minecraft::common::block::Blocks::SAND,
            new lodestone::conversion::block::data::ClassicBlockData(12));
        m_blockIo.registerBlock(
            Version::c0_0_14a, &minecraft::common::block::Blocks::GRAVEL,
            new lodestone::conversion::block::data::ClassicBlockData(13));
        m_blockIo.registerBlock(
            Version::c0_0_14a, &minecraft::common::block::Blocks::GOLD_ORE,
            new lodestone::conversion::block::data::ClassicBlockData(14));
        m_blockIo.registerBlock(
            Version::c0_0_14a, &minecraft::common::block::Blocks::IRON_ORE,
            new lodestone::conversion::block::data::ClassicBlockData(15));
        m_blockIo.registerBlock(
            Version::c0_0_14a, &minecraft::common::block::Blocks::COAL_ORE,
            new lodestone::conversion::block::data::ClassicBlockData(16));
        m_blockIo.registerBlock(
            Version::c0_0_14a, &minecraft::common::block::Blocks::OAK_LOG,
            new lodestone::conversion::block::data::ClassicBlockData(17));
        m_blockIo.registerBlock(
            Version::c0_0_14a, &minecraft::common::block::Blocks::OAK_LEAVES,
            new lodestone::conversion::block::data::ClassicBlockData(18));
        m_blockIo.registerBlock(
            Version::c0_0_19a, &minecraft::common::block::Blocks::SPONGE,
            new lodestone::conversion::block::data::ClassicBlockData(19));
        m_blockIo.registerBlock(
            Version::c0_0_19a, &minecraft::common::block::Blocks::GLASS,
            new lodestone::conversion::block::data::ClassicBlockData(20));
        m_blockIo.registerBlock(
            Version::c0_0_20a, &minecraft::common::block::Blocks::RED_WOOL,
            new lodestone::conversion::block::data::ClassicBlockData(21));
        m_blockIo.registerBlock(
            Version::c0_0_20a, &minecraft::common::block::Blocks::ORANGE_WOOL,
            new lodestone::conversion::block::data::ClassicBlockData(22));
        m_blockIo.registerBlock(
            Version::c0_0_20a, &minecraft::common::block::Blocks::YELLOW_WOOL,
            new lodestone::conversion::block::data::ClassicBlockData(23));
        m_blockIo.registerBlock(
            Version::c0_0_20a,
            &minecraft::common::block::Blocks::CHARTREUSE_WOOL,
            new lodestone::conversion::block::data::ClassicBlockData(24));
        m_blockIo.registerBlock(
            Version::c0_0_20a, &minecraft::common::block::Blocks::LIME_WOOL,
            new lodestone::conversion::block::data::ClassicBlockData(25));
        m_blockIo.registerBlock(
            Version::c0_0_20a,
            &minecraft::common::block::Blocks::SPRING_GREEN_WOOL,
            new lodestone::conversion::block::data::ClassicBlockData(26));
        m_blockIo.registerBlock(
            Version::c0_0_20a, &minecraft::common::block::Blocks::CYAN_WOOL,
            new lodestone::conversion::block::data::ClassicBlockData(27));
        m_blockIo.registerBlock(
            Version::c0_0_20a,
            &minecraft::common::block::Blocks::LIGHT_BLUE_WOOL,
            new lodestone::conversion::block::data::ClassicBlockData(28));
        m_blockIo.registerBlock(
            Version::c0_0_20a,
            &minecraft::common::block::Blocks::ULTRAMARINE_WOOL,
            new lodestone::conversion::block::data::ClassicBlockData(29));
        m_blockIo.registerBlock(
            Version::c0_0_20a, &minecraft::common::block::Blocks::PURPLE_WOOL,
            new lodestone::conversion::block::data::ClassicBlockData(30));
        m_blockIo.registerBlock(
            Version::c0_0_20a, &minecraft::common::block::Blocks::VIOLET_WOOL,
            new lodestone::conversion::block::data::ClassicBlockData(31));
        m_blockIo.registerBlock(
            Version::c0_0_20a, &minecraft::common::block::Blocks::MAGENTA_WOOL,
            new lodestone::conversion::block::data::ClassicBlockData(32));
        m_blockIo.registerBlock(
            Version::c0_0_20a, &minecraft::common::block::Blocks::PINK_WOOL,
            new lodestone::conversion::block::data::ClassicBlockData(33));
        m_blockIo.registerBlock(
            Version::c0_0_20a, &minecraft::common::block::Blocks::GRAY_WOOL,
            new lodestone::conversion::block::data::ClassicBlockData(34));
        m_blockIo.registerBlock(
            Version::c0_0_20a,
            &minecraft::common::block::Blocks::LIGHT_GRAY_WOOL,
            new lodestone::conversion::block::data::ClassicBlockData(35));
        m_blockIo.registerBlock(
            Version::c0_0_20a, &minecraft::common::block::Blocks::WHITE_WOOL,
            new lodestone::conversion::block::data::ClassicBlockData(36));
        m_blockIo.registerBlock(
            Version::c0_0_20a, &minecraft::common::block::Blocks::DANDELION,
            new lodestone::conversion::block::data::ClassicBlockData(37));
        m_blockIo.registerBlock(
            Version::c0_0_20a, &minecraft::common::block::Blocks::POPPY,
            new lodestone::conversion::block::data::ClassicBlockData(38));
        m_blockIo.registerBlock(
            Version::c0_0_20a,
            &minecraft::common::block::Blocks::BROWN_MUSHROOM,
            new lodestone::conversion::block::data::ClassicBlockData(39));
        m_blockIo.registerBlock(
            Version::c0_0_20a, &minecraft::common::block::Blocks::RED_MUSHROOM,
            new lodestone::conversion::block::data::ClassicBlockData(40));
        m_blockIo.registerBlock(
            Version::c0_0_20a, &minecraft::common::block::Blocks::GOLD_BLOCK,
            new lodestone::conversion::block::data::ClassicBlockData(41));
        m_blockIo.registerBlock(
            Version::c0_26st, &minecraft::common::block::Blocks::IRON_BLOCK,
            new lodestone::conversion::block::data::ClassicBlockData(42));
        m_blockIo.registerBlock(
            Version::c0_26st,
            &minecraft::common::block::Blocks::DOUBLE_SMOOTH_STONE_SLAB,
            new lodestone::conversion::block::data::ClassicBlockData(43));
        m_blockIo.registerBlock(
            Version::c0_26st,
            &minecraft::common::block::Blocks::SMOOTH_STONE_SLAB,
            new lodestone::conversion::block::data::ClassicBlockData(44));
        m_blockIo.registerBlock(
            Version::c0_26st, &minecraft::common::block::Blocks::BRICKS,
            new lodestone::conversion::block::data::ClassicBlockData(45));
        m_blockIo.registerBlock(
            Version::c0_26st, &minecraft::common::block::Blocks::TNT,
            new lodestone::conversion::block::data::ClassicBlockData(46));
        m_blockIo.registerBlock(
            Version::c0_26st, &minecraft::common::block::Blocks::BOOKSHELF,
            new lodestone::conversion::block::data::ClassicBlockData(47));
        m_blockIo.registerBlock(
            Version::c0_26st,
            &minecraft::common::block::Blocks::MOSSY_COBBLESTONE,
            new lodestone::conversion::block::data::ClassicBlockData(48));
        m_blockIo.registerBlock(
            Version::c0_28, &minecraft::common::block::Blocks::OBSIDIAN,
            new lodestone::conversion::block::data::ClassicBlockData(49));

        // CPE specific
        m_blockIo.registerBlock(
            Version::c0_30_CPE,
            &minecraft::common::block::Blocks::COBBLESTONE_SLAB,
            new lodestone::conversion::block::data::ClassicBlockData(50));
        m_blockIo.registerBlock(
            Version::c0_30_CPE, &minecraft::common::block::Blocks::ROPE,
            new lodestone::conversion::block::data::ClassicBlockData(51));
        m_blockIo.registerBlock(
            Version::c0_30_CPE, &minecraft::common::block::Blocks::SANDSTONE,
            new lodestone::conversion::block::data::ClassicBlockData(52));
        m_blockIo.registerBlock(
            Version::c0_30_CPE, &minecraft::common::block::Blocks::SNOW_LAYER,
            new lodestone::conversion::block::data::ClassicBlockData(53));
        m_blockIo.registerBlock(
            Version::c0_30_CPE, &minecraft::common::block::Blocks::FIRE,
            new lodestone::conversion::block::data::ClassicBlockData(54));
        m_blockIo.registerBlock(
            Version::c0_30_CPE, &minecraft::common::block::Blocks::ICE,
            new lodestone::conversion::block::data::ClassicBlockData(60));
        m_blockIo.registerBlock(
            Version::c0_30_CPE, &minecraft::common::block::Blocks::CERAMIC_TILE,
            new lodestone::conversion::block::data::ClassicBlockData(61));
        m_blockIo.registerBlock(
            Version::c0_30_CPE, &minecraft::common::block::Blocks::MAGMA_BLOCK,
            new lodestone::conversion::block::data::ClassicBlockData(62));
        m_blockIo.registerBlock(
            Version::c0_30_CPE,
            &minecraft::common::block::Blocks::QUARTZ_PILLAR,
            new lodestone::conversion::block::data::ClassicBlockData(63));
        m_blockIo.registerBlock(
            Version::c0_30_CPE, &minecraft::common::block::Blocks::CRATE,
            new lodestone::conversion::block::data::ClassicBlockData(64));
        m_blockIo.registerBlock(
            Version::c0_30_CPE, &minecraft::common::block::Blocks::STONE_BRICKS,
            new lodestone::conversion::block::data::ClassicBlockData(65));

        // Remove the cpe specific blocks because they didn't exist here
        m_blockIo.removeBlock(Version::in20091223_1457,
                       &minecraft::common::block::Blocks::COBBLESTONE_SLAB);
        m_blockIo.removeBlock(Version::in20091223_1457,
                       &minecraft::common::block::Blocks::ROPE);
        m_blockIo.removeBlock(Version::in20091223_1457,
                       &minecraft::common::block::Blocks::SANDSTONE);
        m_blockIo.removeBlock(Version::in20091223_1457,
                       &minecraft::common::block::Blocks::SNOW_LAYER);
        m_blockIo.removeBlock(Version::in20091223_1457,
                       &minecraft::common::block::Blocks::FIRE);
        m_blockIo.removeBlock(Version::in20091223_1457,
                       &minecraft::common::block::Blocks::ICE);
        m_blockIo.removeBlock(Version::in20091223_1457,
                       &minecraft::common::block::Blocks::CERAMIC_TILE);
        m_blockIo.removeBlock(Version::in20091223_1457,
                       &minecraft::common::block::Blocks::MAGMA_BLOCK);
        m_blockIo.removeBlock(Version::in20091223_1457,
                       &minecraft::common::block::Blocks::QUARTZ_PILLAR);
        m_blockIo.removeBlock(Version::in20091223_1457,
                       &minecraft::common::block::Blocks::CRATE);
        m_blockIo.removeBlock(Version::in20091223_1457,
                       &minecraft::common::block::Blocks::STONE_BRICKS);

        m_blockIo.registerBlock(
            Version::in20091223_1457, &minecraft::common::block::Blocks::TORCH,
            new lodestone::conversion::block::data::ClassicBlockData(50));
        m_blockIo.registerBlock(
            Version::in20100109_1939, &minecraft::common::block::Blocks::FIRE,
            new lodestone::conversion::block::data::ClassicBlockData(51));
        m_blockIo.registerBlock(
            Version::in20100114,
            &minecraft::common::block::Blocks::WATER_SPAWNER,
            new lodestone::conversion::block::data::ClassicBlockData(52));
        m_blockIo.registerBlock(
            Version::in20100122_2251,
            &minecraft::common::block::Blocks::LAVA_SPAWNER,
            new lodestone::conversion::block::data::ClassicBlockData(53));
        m_blockIo.registerBlock(
            Version::in20100124_2119, &minecraft::common::block::Blocks::CHEST,
            new lodestone::conversion::block::data::ClassicBlockData(54));
        m_blockIo.registerBlock(
            Version::in20100128_2200, &minecraft::common::block::Blocks::GEAR,
            new lodestone::conversion::block::data::ClassicBlockData(55));
        m_blockIo.registerBlock(
            Version::in20100128_2200,
            &minecraft::common::block::Blocks::DIAMOND_ORE,
            new lodestone::conversion::block::data::ClassicBlockData(56));
        m_blockIo.registerBlock(
            Version::in20100128_2200,
            &minecraft::common::block::Blocks::DIAMOND_BLOCK,
            new lodestone::conversion::block::data::ClassicBlockData(57));
        m_blockIo.registerBlock(
            Version::in20100129_2332,
            &minecraft::common::block::Blocks::CRAFTING_TABLE,
            new lodestone::conversion::block::data::ClassicBlockData(58));
        m_blockIo.registerBlock(
            Version::in20100206_2034, &minecraft::common::block::Blocks::WHEAT,
            new lodestone::conversion::block::data::ClassicBlockData(59));
        m_blockIo.registerBlock(
            Version::in20100206_2034,
            &minecraft::common::block::Blocks::FARMLAND,
            new lodestone::conversion::block::data::ClassicBlockData(60));
        m_blockIo.registerBlock(
            Version::in20100219, &minecraft::common::block::Blocks::FURNACE,
            new lodestone::conversion::block::data::ClassicBlockData(61));
        m_blockIo.registerBlock(
            Version::in20100219, &minecraft::common::block::Blocks::LIT_FURNACE,
            new lodestone::conversion::block::data::ClassicBlockData(62));

        // TODO sometime we need to implement item conversion too

        // ID FORMAT CHANGE
        m_blockIo.registerBlock(
            Version::b1_3, &level::block::Blocks::NONE,
            new lodestone::conversion::block::data::NumericBlockData(0, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::STONE,
            new lodestone::conversion::block::data::NumericBlockData(1, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::GRASS_BLOCK,
            new lodestone::conversion::block::data::NumericBlockData(2, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::DIRT,
            new lodestone::conversion::block::data::NumericBlockData(3, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::COBBLESTONE,
            new lodestone::conversion::block::data::NumericBlockData(4, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::OAK_PLANKS,
            new lodestone::conversion::block::data::NumericBlockData(5, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::OAK_SAPLING,
            new lodestone::conversion::block::data::NumericBlockData(6, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::BEDROCK,
            new lodestone::conversion::block::data::NumericBlockData(7, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::FLOWING_WATER,
            new lodestone::conversion::block::data::NumericBlockData(8, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::WATER,
            new lodestone::conversion::block::data::NumericBlockData(9, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::FLOWING_LAVA,
            new lodestone::conversion::block::data::NumericBlockData(10, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::LAVA,
            new lodestone::conversion::block::data::NumericBlockData(11, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::SAND,
            new lodestone::conversion::block::data::NumericBlockData(12, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::GRAVEL,
            new lodestone::conversion::block::data::NumericBlockData(13, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::GOLD_ORE,
            new lodestone::conversion::block::data::NumericBlockData(14, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::IRON_ORE,
            new lodestone::conversion::block::data::NumericBlockData(15, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::COAL_ORE,
            new lodestone::conversion::block::data::NumericBlockData(16, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::OAK_LOG,
            new lodestone::conversion::block::data::NumericBlockData(17, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::OAK_LEAVES,
            new lodestone::conversion::block::data::NumericBlockData(18, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::SPONGE,
            new lodestone::conversion::block::data::NumericBlockData(19, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::GLASS,
            new lodestone::conversion::block::data::NumericBlockData(20, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::DANDELION,
            new lodestone::conversion::block::data::NumericBlockData(37, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::POPPY,
            new lodestone::conversion::block::data::NumericBlockData(38, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::BROWN_MUSHROOM,
            new lodestone::conversion::block::data::NumericBlockData(39, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::RED_MUSHROOM,
            new lodestone::conversion::block::data::NumericBlockData(40, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::GOLD_BLOCK,
            new lodestone::conversion::block::data::NumericBlockData(41, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::IRON_BLOCK,
            new lodestone::conversion::block::data::NumericBlockData(42, 0));
        m_blockIo.registerBlock(
            Version::b1_3,
            &minecraft::common::block::Blocks::DOUBLE_SMOOTH_STONE_SLAB,
            new lodestone::conversion::block::data::NumericBlockData(43, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::SMOOTH_STONE_SLAB,
            new lodestone::conversion::block::data::NumericBlockData(44, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::BRICKS,
            new lodestone::conversion::block::data::NumericBlockData(45, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::TNT,
            new lodestone::conversion::block::data::NumericBlockData(46, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::BOOKSHELF,
            new lodestone::conversion::block::data::NumericBlockData(47, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::MOSSY_COBBLESTONE,
            new lodestone::conversion::block::data::NumericBlockData(48, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::OBSIDIAN,
            new lodestone::conversion::block::data::NumericBlockData(49, 0));
        m_blockIo.registerBlock(
            Version::b1_3, &minecraft::common::block::Blocks::TORCH,
            new lodestone::conversion::block::data::NumericBlockData(50, 0));
        // ID FORMAT CHANGE #2

        m_blockIo.registerBlock(
            Version::r1_2_1, &level::block::Blocks::NONE,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                0, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::STONE,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                1, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::GRASS_BLOCK,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                2, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::DIRT,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                3, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::COBBLESTONE,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                4, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::OAK_PLANKS,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                5, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::OAK_SAPLING,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                6, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::BEDROCK,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                7, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::FLOWING_WATER,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                8, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::WATER,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                9, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::FLOWING_LAVA,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                10, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::LAVA,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                11, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::SAND,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                12, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::GRAVEL,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                13, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::GOLD_ORE,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                14, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::IRON_ORE,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                15, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::COAL_ORE,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                16, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::OAK_LOG,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                17, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::OAK_LEAVES,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                18, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::SPONGE,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                19, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::GLASS,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                20, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::DANDELION,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                37, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::POPPY,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                38, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::BROWN_MUSHROOM,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                39, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::RED_MUSHROOM,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                40, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::GOLD_BLOCK,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                41, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::IRON_BLOCK,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                42, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1,
            &minecraft::common::block::Blocks::DOUBLE_SMOOTH_STONE_SLAB,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                43, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1,
            &minecraft::common::block::Blocks::SMOOTH_STONE_SLAB,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                44, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::BRICKS,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                45, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::TNT,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                46, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::BOOKSHELF,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                47, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1,
            &minecraft::common::block::Blocks::MOSSY_COBBLESTONE,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                48, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::OBSIDIAN,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(
                49, 0));
        m_blockIo.registerBlock(
            Version::r1_2_1, &minecraft::common::block::Blocks::TORCH,
            new lodestone::conversion::block::data::ExtendedNumericBlockData(50, 0));
    }

    void LodestoneJava::initItems() {
        common::LodestoneMinecraftCommon::initItems();
    }

    lodestone::common::registry::Identifier LodestoneJava::getIdentifier() const {
        return *Identifiable::getIdentifier();
    }

    lodestone::common::util::Semver LodestoneJava::getVersion() const { return VERSION; }

    core::LodestoneExtension *lodestoneInit() {
        return LodestoneJava::getInstance();
    }
} // namespace lodestone::minecraft::java
