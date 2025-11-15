//
// Created by DexrnZacAttack on 10/17/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKS_H
#define LODESTONE_BLOCKS_H

#include <Lodestone.Common/registry/Identifier.h>

namespace lodestone::level::block {
    struct Blocks {
#define ADD_BLOCK(name, id) static constexpr const lodestone::common::registry::Identifier name = lodestone::common::registry::Identifier{"lodestone", id}

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
        ADD_BLOCK(FLOWING_LAVA, "flowing_lava");
        ADD_BLOCK(LAVA, "lava");
        //endregion
        ADD_BLOCK(SAND, "sand");
        ADD_BLOCK(GRAVEL, "gravel");
        //region ORE
        ADD_BLOCK(GOLD_ORE, "gold_ore");
        ADD_BLOCK(IRON_ORE, "iron_ore");
        ADD_BLOCK(COAL_ORE, "coal_ore");
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
    };
}

#endif //LODESTONE_BLOCKS_H