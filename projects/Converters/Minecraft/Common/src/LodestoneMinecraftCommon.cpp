//
// Created by DexrnZacAttack on 11/21/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Common/LodestoneMinecraftCommon.h"

#include "Lodestone.Minecraft.Common/block/Blocks.h"
#include "Lodestone.Minecraft.Common/material/Materials.h"

#include <Lodestone.Level/block/BlockRegistry.h>

namespace lodestone::minecraft::common {
#define MC_REGISTER_BLOCK_FUNC(n, m, d)                                           \
    r.registerBlockIfNonExistent(n, new level::block::Block(n, m, d))

    void LodestoneMinecraftCommon::initBlocks() {
        static bool blocksInitialized = false;
        if (blocksInitialized)
            return;

        blocksInitialized = true;

        level::block::BlockRegistry &r =
            level::block::BlockRegistry::getInstance();

        MC_REGISTER_BLOCK_FUNC(&block::Blocks::STONE, materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GRASS_BLOCK, materials::GRASS, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::DIRT, materials::DIRT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::COBBLESTONE,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_PLANKS,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_SAPLING,
                               materials::PLANT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BEDROCK,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::FLOWING_WATER,
                               materials::WATER, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::WATER,
                               materials::WATER, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::FLOWING_LAVA,
                               materials::FIRE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LAVA, materials::FIRE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SAND,
                               materials::SAND, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GRAVEL,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GOLD_ORE,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::IRON_ORE,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::COAL_ORE,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_LOG,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_LEAVES,
                               materials::PLANT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SPONGE,
                               materials::COLOR_YELLOW, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GLASS,
                               materials::NONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::RED_WOOL,
                               materials::COLOR_RED, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::ORANGE_WOOL,
                               materials::COLOR_ORANGE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::YELLOW_WOOL,
                               materials::COLOR_YELLOW, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CHARTREUSE_WOOL,
                               materials::COLOR_LIGHT_GREEN, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LIME_WOOL,
                               materials::COLOR_LIGHT_GREEN, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SPRING_GREEN_WOOL,
                               materials::COLOR_CYAN, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CYAN_WOOL,
                               materials::COLOR_CYAN, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CAPRI_WOOL,
                               materials::COLOR_CYAN, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LIGHT_BLUE_WOOL,
                               materials::COLOR_LIGHT_BLUE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::ULTRAMARINE_WOOL,
                               materials::COLOR_BLUE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::PURPLE_WOOL,
                               materials::COLOR_PURPLE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::VIOLET_WOOL,
                               materials::COLOR_PURPLE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MAGENTA_WOOL,
                               materials::COLOR_PINK, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::PINK_WOOL,
                               materials::COLOR_PINK, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GRAY_WOOL,
                               materials::COLOR_GRAY, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LIGHT_GRAY_WOOL,
                               materials::COLOR_LIGHT_GRAY, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::WHITE_WOOL,
                               materials::WOOL, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::DANDELION,
                               materials::COLOR_YELLOW, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::POPPY,
                               materials::COLOR_RED, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BROWN_MUSHROOM,
                               materials::COLOR_BROWN, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::RED_MUSHROOM,
                               materials::COLOR_RED, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GOLD_BLOCK,
                               materials::GOLD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::IRON_BLOCK,
                               materials::METAL, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::DOUBLE_SMOOTH_STONE_SLAB,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SMOOTH_STONE_SLAB,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BRICKS,
                               materials::COLOR_RED, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::TNT,
                               materials::FIRE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BOOKSHELF,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MOSSY_COBBLESTONE,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OBSIDIAN,
                               materials::COLOR_BLACK, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::ROPE,
                               materials::NONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SANDSTONE,
                               materials::SAND, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SNOW_LAYER,
                               materials::SNOW, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::FIRE,
                               materials::FIRE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::ICE,
                               materials::ICE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CERAMIC_TILE,
                               materials::QUARTZ, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MAGMA_BLOCK,
                               materials::NETHER, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::QUARTZ_PILLAR,
                               materials::QUARTZ, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CRATE,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::STONE_BRICKS,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::TORCH,
                               materials::NONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CHEST,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GEAR,
                               materials::METAL, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::DIAMOND_BLOCK,
                               materials::DIAMOND, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CRAFTING_TABLE,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::FARMLAND,
                               materials::DIRT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::WHEAT,
                               materials::PLANT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::FURNACE,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LIT_FURNACE,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_DOOR,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LADDER,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_SIGN,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::RAIL,
                               materials::NONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MOB_SPAWNER,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::COBBLESTONE_STAIRS,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_STAIRS,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::IRON_DOOR,
                               materials::METAL, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LEVER,
                               materials::NONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::REDSTONE_DUST,
                               materials::NONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::REDSTONE_TORCH,
                               materials::NONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::STONE_BUTTON,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::STONE_PRESSURE_PLATE,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_PRESSURE_PLATE,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SNOW_BLOCK,
                               materials::SNOW, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CACTUS,
                               materials::PLANT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CLAY,
                               materials::CLAY, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SUGAR_CANE,
                               materials::PLANT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::JUKEBOX,
                               materials::DIRT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_FENCE,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::NETHERRACK,
                               materials::NETHER, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SOUL_SAND,
                               materials::COLOR_BROWN, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GLOWSTONE,
                               materials::SAND, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::PUMPKIN,
                               materials::COLOR_ORANGE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GLOWING_PUMPKIN,
                               materials::COLOR_ORANGE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::NETHER_PORTAL,
                               materials::NONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BIRCH_LEAVES,
                               materials::PLANT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BIRCH_LOG,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CAKE,
                               materials::NONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::DISPENSER,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LAPIS_BLOCK,
                               materials::LAPIS, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::NOTE_BLOCK,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CORAL,
                               materials::COLOR_YELLOW, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BED,
                               materials::WOOL, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::REDSTONE_REPEATER,
                               materials::NONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::PETRIFIED_OAK_SLAB,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SANDSTONE_SLAB,
                               materials::SAND, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SEAMLESS_STONE_SLAB,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::APRIL_FOOLS_CHEST,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BIRCH_SAPLING,
                               materials::PLANT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::COBWEB,
                               materials::WOOL, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::DETECTOR_RAIL,
                               materials::NONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::POWERED_RAIL,
                               materials::NONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SPRUCE_SAPLING,
                               materials::PLANT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::DEAD_BUSH,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GRASS,
                               materials::GRASS, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::FERN,
                               materials::PLANT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_TRAPDOOR,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::PISTON,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::STICKY_PISTON,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::PISTON_HEAD,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BRICK_SLAB,
                               materials::COLOR_RED, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BRICK_STAIRS,
                               materials::COLOR_RED, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::STONE_BRICK_SLAB,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::STONE_BRICK_STAIRS,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CRACKED_STONE_BRICKS,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MOSSY_STONE_BRICKS,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::INFESTED_STONE,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::INFESTED_COBBLESTONE,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::INFESTED_STONE_BRICKS,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GLASS_PANE,
                               materials::NONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_FENCE_GATE,
                               materials::WOOD, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::IRON_BARS,
                               materials::NONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MELON,
                               materials::COLOR_LIGHT_GREEN, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MELON_STEM,
                               materials::PLANT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::PUMPKIN_STEM,
                               materials::PLANT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MUSHROOM_BLOCK,
                               materials::DIRT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MUSHROOM_STEM,
                               materials::WOOL, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::RED_MUSHROOM_BLOCK,
                               materials::COLOR_RED, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BROWN_MUSHROOM_BLOCK,
                               materials::DIRT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::VINE,
                               materials::PLANT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BREWING_STAND,
                               materials::METAL, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CAULDRON,
                               materials::STONE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::DRAGON_EGG,
                               materials::COLOR_BLACK, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::ENCHANTMENT_TABLE,
                               materials::COLOR_RED, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::END_PORTAL,
                               materials::COLOR_BLACK, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::END_PORTAL_FRAME,
                               materials::COLOR_GREEN, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::END_STONE,
                               materials::SAND, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LILY_PAD,
                               materials::PLANT, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MYCELIUM,
                               materials::COLOR_PURPLE, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::NETHER_BRICKS,
                               materials::NETHER, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::NETHER_BRICK_FENCE,
                               materials::NETHER, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::NETHER_BRICK_STAIRS,
                               materials::NETHER, nullptr);
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::NETHER_WART,
                               materials::COLOR_RED, nullptr);
    }
} // namespace lodestone::minecraft::common