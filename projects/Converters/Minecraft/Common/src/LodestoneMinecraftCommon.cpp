//
// Created by DexrnZacAttack on 11/21/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Common/LodestoneMinecraftCommon.h"

#include "Lodestone.Minecraft.Common/block/Blocks.h"
#include <Lodestone.Level/block/BlockRegistry.h>

namespace lodestone::minecraft::common {
#define MC_REGISTER_BLOCK_FUNC(n, m)                                           \
    r.registerBlockIfNonExistent(n, new level::block::Block(n, m))

    void LodestoneMinecraftCommon::initBlocks() {
        level::block::BlockRegistry &r =
            level::block::BlockRegistry::getInstance();

        MC_REGISTER_BLOCK_FUNC(&block::Blocks::STONE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GRASS_BLOCK,
                               level::material::Material({127, 178, 56, 255}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::DIRT,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::COBBLESTONE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_PLANKS,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_SAPLING,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BEDROCK,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::FLOWING_WATER,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::WATER,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::FLOWING_LAVA,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LAVA,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SAND,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GRAVEL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GOLD_ORE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::IRON_ORE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::COAL_ORE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_LOG,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_LEAVES,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SPONGE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GLASS,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::RED_WOOL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::ORANGE_WOOL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::YELLOW_WOOL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CHARTREUSE_WOOL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LIME_WOOL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SPRING_GREEN_WOOL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CYAN_WOOL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CAPRI_WOOL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LIGHT_BLUE_WOOL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::ULTRAMARINE_WOOL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::PURPLE_WOOL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::VIOLET_WOOL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MAGENTA_WOOL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::PINK_WOOL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GRAY_WOOL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LIGHT_GRAY_WOOL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::WHITE_WOOL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::DANDELION,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::POPPY,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BROWN_MUSHROOM,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::RED_MUSHROOM,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GOLD_BLOCK,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::IRON_BLOCK,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::DOUBLE_SMOOTH_STONE_SLAB,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SMOOTH_STONE_SLAB,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BRICKS,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::TNT,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BOOKSHELF,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MOSSY_COBBLESTONE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OBSIDIAN,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::ROPE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SANDSTONE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SNOW_LAYER,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::FIRE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::ICE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CERAMIC_TILE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MAGMA_BLOCK,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::QUARTZ_PILLAR,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CRATE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::STONE_BRICKS,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::TORCH,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CHEST,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GEAR,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::DIAMOND_BLOCK,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CRAFTING_TABLE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::FARMLAND,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::WHEAT,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::FURNACE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LIT_FURNACE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_DOOR,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LADDER,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_SIGN,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::RAIL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MOB_SPAWNER,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::COBBLESTONE_STAIRS,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_STAIRS,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::IRON_DOOR,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LEVER,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::REDSTONE_DUST,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::REDSTONE_TORCH,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::STONE_BUTTON,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::STONE_PRESSURE_PLATE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_PRESSURE_PLATE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SNOW_BLOCK,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CACTUS,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CLAY,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SUGAR_CANE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::JUKEBOX,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_FENCE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::NETHERRACK,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SOUL_SAND,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GLOWSTONE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::PUMPKIN,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GLOWING_PUMPKIN,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::NETHER_PORTAL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BIRCH_LEAVES,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BIRCH_LOG,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CAKE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::DISPENSER,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LAPIS_BLOCK,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::NOTE_BLOCK,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CORAL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BED,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::REDSTONE_REPEATER,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::PETRIFIED_OAK_SLAB,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SANDSTONE_SLAB,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SEAMLESS_STONE_SLAB,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::APRIL_FOOLS_CHEST,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BIRCH_SAPLING,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::COBWEB,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::DETECTOR_RAIL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::POWERED_RAIL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::SPRUCE_SAPLING,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::DEAD_BUSH,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GRASS,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::FERN,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_TRAPDOOR,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::PISTON,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::STICKY_PISTON,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::PISTON_HEAD,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BRICK_SLAB,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BRICK_STAIRS,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::STONE_BRICK_SLAB,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::STONE_BRICK_STAIRS,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CRACKED_STONE_BRICKS,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MOSSY_STONE_BRICKS,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::INFESTED_STONE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::INFESTED_COBBLESTONE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::INFESTED_STONE_BRICKS,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::GLASS_PANE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::OAK_FENCE_GATE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::IRON_BARS,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MELON,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MELON_STEM,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::PUMPKIN_STEM,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MUSHROOM_BLOCK,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MUSHROOM_STEM,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::RED_MUSHROOM_BLOCK,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BROWN_MUSHROOM_BLOCK,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::VINE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::BREWING_STAND,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::CAULDRON,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::DRAGON_EGG,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::ENCHANTMENT_TABLE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::END_PORTAL,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::END_PORTAL_FRAME,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::END_STONE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::LILY_PAD,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::MYCELIUM,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::NETHER_BRICKS,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::NETHER_BRICK_FENCE,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::NETHER_BRICK_STAIRS,
                               level::material::Material({0, 0, 0, 0}));
        MC_REGISTER_BLOCK_FUNC(&block::Blocks::NETHER_WART,
                               level::material::Material({0, 0, 0, 0}));
    }
} // namespace lodestone::minecraft::common
