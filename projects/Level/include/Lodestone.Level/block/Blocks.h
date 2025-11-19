//
// Created by DexrnZacAttack on 10/17/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKS_H
#define LODESTONE_BLOCKS_H

#include <Lodestone.Common/registry/Identifier.h>

namespace lodestone::level::block {
    struct Blocks {
#define ADD_BLOCK(name, id) static constexpr const lodestone::common::registry::Identifier name = lodestone::common::registry::Identifier{"lodestone", id}

        // TODO once all blocks are added we should sort them
        ADD_BLOCK(AIR, "air");
        ADD_BLOCK(STONE, "stone");
        ADD_BLOCK(GRASS_BLOCK, "grass_block");
        ADD_BLOCK(DIRT, "dirt");
        ADD_BLOCK(COBBLESTONE, "cobblestone");
        ADD_BLOCK(OAK_PLANKS, "oak_planks");
        ADD_BLOCK(OAK_SAPLING, "oak_sapling");
        ADD_BLOCK(BEDROCK, "bedrock");
        //region LIQUID
        ADD_BLOCK(FLOWING_WATER, "flowing_water");
        ADD_BLOCK(WATER, "water");
        ADD_BLOCK(WATER_SPAWNER, "water_spawner");
        ADD_BLOCK(FLOWING_LAVA, "flowing_lava");
        ADD_BLOCK(LAVA, "lava");
        ADD_BLOCK(LAVA_SPAWNER, "lava_spawner");
        //endregion
        ADD_BLOCK(SAND, "sand");
        ADD_BLOCK(GRAVEL, "gravel");
        //region ORE
        ADD_BLOCK(COAL_ORE, "coal_ore");
        ADD_BLOCK(IRON_ORE, "iron_ore");
        ADD_BLOCK(GOLD_ORE, "gold_ore");
        ADD_BLOCK(LAPIS_ORE, "lapis_ore");
        ADD_BLOCK(REDSTONE_ORE, "redstone_ore");
        ADD_BLOCK(DIAMOND_ORE, "diamond_ore");
        //endregion
        ADD_BLOCK(OAK_LOG, "oak_log");
        ADD_BLOCK(OAK_LEAVES, "oak_leaves");
        ADD_BLOCK(SPONGE, "sponge");
        ADD_BLOCK(GLASS, "glass");
        //region WOOL
        ADD_BLOCK(RED_WOOL, "red_wool");
        ADD_BLOCK(ORANGE_WOOL, "orange_wool");
        ADD_BLOCK(YELLOW_WOOL, "yellow_wool");
        ADD_BLOCK(CHARTREUSE_WOOL, "chartreuse_wool");
        ADD_BLOCK(LIME_WOOL, "lime_wool");
        ADD_BLOCK(SPRING_GREEN_WOOL, "spring_green_wool");
        ADD_BLOCK(CYAN_WOOL, "cyan_wool");
        ADD_BLOCK(CAPRI_WOOL, "capri_wool");
        ADD_BLOCK(LIGHT_BLUE_WOOL, "light_blue_wool");
        ADD_BLOCK(ULTRAMARINE_WOOL, "ultramarine_wool");
        ADD_BLOCK(PURPLE_WOOL, "purple_wool");
        ADD_BLOCK(VIOLET_WOOL, "violet_wool");
        ADD_BLOCK(MAGENTA_WOOL, "magenta_wool");
        ADD_BLOCK(PINK_WOOL, "pink_wool");
        ADD_BLOCK(GRAY_WOOL, "gray_wool");
        ADD_BLOCK(LIGHT_GRAY_WOOL, "light_gray_wool");
        ADD_BLOCK(WHITE_WOOL, "white_wool");
        //endregion
        //region PLANTS
        ADD_BLOCK(DANDELION, "dandelion");
        ADD_BLOCK(POPPY, "poppy");
        ADD_BLOCK(BROWN_MUSHROOM, "brown_mushroom");
        ADD_BLOCK(RED_MUSHROOM, "red_mushroom");
        //endregion
        ADD_BLOCK(GOLD_BLOCK, "gold_block");
        ADD_BLOCK(IRON_BLOCK, "iron_block");
        ADD_BLOCK(DOUBLE_SMOOTH_STONE_SLAB, "double_smooth_stone_slab");
        ADD_BLOCK(SMOOTH_STONE_SLAB, "smooth_stone_slab");
        ADD_BLOCK(BRICKS, "bricks");
        ADD_BLOCK(TNT, "tnt");
        ADD_BLOCK(BOOKSHELF, "bookshelf");
        ADD_BLOCK(MOSSY_COBBLESTONE, "mossy_cobblestone");
        ADD_BLOCK(OBSIDIAN, "obsidian");
        ADD_BLOCK(COBBLESTONE_SLAB, "cobblestone_slab");
        ADD_BLOCK(ROPE, "rope"); // CPE exclusive, later we can convert to chain
        ADD_BLOCK(SANDSTONE, "sandstone");
        ADD_BLOCK(SNOW_LAYER, "snow_layer");
        ADD_BLOCK(FIRE, "fire");
        ADD_BLOCK(ICE, "ice");
        // todo do we want to add every single wool type? we would have to give unique names to some of them
        ADD_BLOCK(CERAMIC_TILE, "ceramic_tile"); // cpe exclusive
        ADD_BLOCK(MAGMA_BLOCK, "magma_block");
        ADD_BLOCK(QUARTZ_PILLAR, "quartz_pillar");
        ADD_BLOCK(CRATE, "crate"); // cpe exclusive
        ADD_BLOCK(STONE_BRICKS, "stone_bricks");
        ADD_BLOCK(TORCH, "torch");
        ADD_BLOCK(CHEST, "chest"); // mmm tile entity, how do we want to do this?
        ADD_BLOCK(GEAR, "gear");
        ADD_BLOCK(DIAMOND_BLOCK, "diamond_block");
        ADD_BLOCK(CRAFTING_TABLE, "crafting_table");
        ADD_BLOCK(FARMLAND, "farmland");
        ADD_BLOCK(WHEAT, "wheat");
        ADD_BLOCK(FURNACE, "furnace");
        ADD_BLOCK(LIT_FURNACE, "lit_furnace");
        ADD_BLOCK(OAK_DOOR, "oak_door");
        ADD_BLOCK(LADDER, "ladder");
        ADD_BLOCK(OAK_SIGN, "oak_sign");
        ADD_BLOCK(RAIL, "rail");
        ADD_BLOCK(MOB_SPAWNER, "mob_spawner");
        ADD_BLOCK(COBBLESTONE_STAIRS, "cobblestone_stairs");
        ADD_BLOCK(OAK_STAIRS, "oak_stairs");
        ADD_BLOCK(IRON_DOOR, "iron_door");
        ADD_BLOCK(LEVER, "lever");
        ADD_BLOCK(REDSTONE_DUST, "redstone_dust");
        ADD_BLOCK(REDSTONE_TORCH, "redstone_torch");
        ADD_BLOCK(STONE_BUTTON, "stone_button");
        ADD_BLOCK(STONE_PRESSURE_PLATE, "stone_pressure_plate");
        ADD_BLOCK(OAK_PRESSURE_PLATE, "oak_pressure_plate");
        ADD_BLOCK(SNOW_BLOCK, "snow_block");
        ADD_BLOCK(CACTUS, "cactus");
        ADD_BLOCK(CLAY, "clay");
        ADD_BLOCK(SUGAR_CANE, "sugar_cane");
        ADD_BLOCK(JUKEBOX, "jukebox");
        ADD_BLOCK(OAK_FENCE, "oak_fence");
        ADD_BLOCK(NETHERRACK, "netherrack");
        ADD_BLOCK(SOUL_SAND, "soul_sand");
        ADD_BLOCK(GLOWSTONE, "glowstone");
        ADD_BLOCK(PUMPKIN, "pumpkin");
        ADD_BLOCK(GLOWING_PUMPKIN, "glowing_pumpkin"); // yes I know it's jack o lantern, but this is simpler to find
        ADD_BLOCK(NETHER_PORTAL, "nether_portal");
        ADD_BLOCK(BIRCH_LEAVES, "birch_leaves");
        ADD_BLOCK(BIRCH_LOG, "birch_log");
        ADD_BLOCK(CAKE, "cake");
        ADD_BLOCK(DISPENSER, "dispenser");
        ADD_BLOCK(LAPIS_BLOCK, "lapis_block");
        ADD_BLOCK(NOTE_BLOCK, "note_block");
        ADD_BLOCK(CORAL, "coral"); // was this ever saved?
        ADD_BLOCK(BED, "bed");
        ADD_BLOCK(REDSTONE_REPEATER, "redstone_repeater");
        ADD_BLOCK(PETRIFIED_OAK_SLAB, "petrified_oak_slab");
        ADD_BLOCK(SANDSTONE_SLAB, "sandstone_slab");
        ADD_BLOCK(SEAMLESS_STONE_SLAB, "seamless_stone_slab"); // apparently took like 50 metadata values, fun!
        ADD_BLOCK(APRIL_FOOLS_CHEST, "april_fools_chest"); // locked chest
        ADD_BLOCK(BIRCH_SAPLING, "birch_sapling");
        ADD_BLOCK(COBWEB, "cobweb");
        ADD_BLOCK(DETECTOR_RAIL, "detector_rail");
        ADD_BLOCK(POWERED_RAIL, "powered_rail");
        ADD_BLOCK(SPRUCE_SAPLING, "spruce_sapling");
        ADD_BLOCK(DEAD_BUSH, "dead_bush");
        ADD_BLOCK(GRASS, "grass"); // different from grass block
        ADD_BLOCK(FERN, "fern");
        ADD_BLOCK(OAK_TRAPDOOR, "oak_trapdoor");
        ADD_BLOCK(PISTON, "piston");
        ADD_BLOCK(STICKY_PISTON, "sticky_piston");
        ADD_BLOCK(PISTON_HEAD, "piston_head");
        ADD_BLOCK(BRICK_SLAB, "brick_slab");
        ADD_BLOCK(BRICK_STAIRS, "brick_stairs");
        ADD_BLOCK(STONE_BRICK_SLAB, "stone_brick_slab");
        ADD_BLOCK(STONE_BRICK_STAIRS, "stone_brick_stairs");
        ADD_BLOCK(CRACKED_STONE_BRICKS, "cracked_stone_bricks");
        ADD_BLOCK(MOSSY_STONE_BRICKS, "mossy_stone_bricks");
        ADD_BLOCK(INFESTED_STONE, "infested_stone");
        ADD_BLOCK(INFESTED_COBBLESTONE, "infested_cobblestone");
        ADD_BLOCK(INFESTED_STONE_BRICKS, "infested_stone_bricks");
        ADD_BLOCK(GLASS_PANE, "glass_pane");
        ADD_BLOCK(OAK_FENCE_GATE, "oak_fence_gate");
        ADD_BLOCK(IRON_BARS, "iron_bars");
        ADD_BLOCK(MELON, "melon");
        ADD_BLOCK(MELON_STEM, "melon_stem");
        ADD_BLOCK(PUMPKIN_STEM, "pumpkin_stem");
        ADD_BLOCK(MUSHROOM_BLOCK, "mushroom_block");
        ADD_BLOCK(MUSHROOM_STEM, "mushroom_stem");
        ADD_BLOCK(RED_MUSHROOM_BLOCK, "red_mushroom_block");
        ADD_BLOCK(BROWN_MUSHROOM_BLOCK, "brown_mushroom_block");
        ADD_BLOCK(VINE, "vine");
        ADD_BLOCK(BREWING_STAND, "brewing_stand");
        ADD_BLOCK(CAULDRON, "cauldron");
        ADD_BLOCK(DRAGON_EGG, "dragon_egg");
        ADD_BLOCK(ENCHANTMENT_TABLE, "enchantment_table");
        ADD_BLOCK(END_PORTAL, "end_portal");
        ADD_BLOCK(END_PORTAL_FRAME, "end_portal_frame");
        ADD_BLOCK(END_STONE, "end_stone");
        ADD_BLOCK(LILY_PAD, "lily_pad");
        ADD_BLOCK(MYCELIUM, "mycelium");
        ADD_BLOCK(NETHER_BRICKS, "nether_bricks");
        ADD_BLOCK(NETHER_BRICK_FENCE, "nether_brick_fence");
        ADD_BLOCK(NETHER_BRICK_STAIRS, "nether_brick_stairs");
        ADD_BLOCK(NETHER_WART, "nether_wart");
    };
}

#endif //LODESTONE_BLOCKS_H