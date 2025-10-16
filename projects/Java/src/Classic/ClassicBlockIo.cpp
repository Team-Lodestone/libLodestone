//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Classic/ClassicBlockIo.h"

namespace lodestone::java::classic {
    ClassicBlockIO *ClassicBlockIO::sInstance = new ClassicBlockIO();

    ClassicBlockIO::ClassicBlockIO() {
        registerBlock("lodestone:air", {0, std::monostate{}});
            registerBlock("lodestone:stone", {1, std::monostate{}});
            registerBlock("lodestone:grass_block", {2, std::monostate{}});
            registerBlock("lodestone:dirt", {3, std::monostate{}});
            registerBlock("lodestone:cobblestone", {4, std::monostate{}});
            registerBlock("lodestone:oak_planks", {5, std::monostate{}});
            registerBlock("lodestone:oak_sapling", {6, std::monostate{}});
            registerBlock("lodestone:bedrock", {7, std::monostate{}});
            registerBlock("lodestone:flowing_water", {8, std::monostate{}});
            registerBlock("lodestone:water", {9, std::monostate{}});
            registerBlock("lodestone:flowing_lava", {10, std::monostate{}});
            registerBlock("lodestone:lava", {11, std::monostate{}});
            registerBlock("lodestone:sand", {12, std::monostate{}});
            registerBlock("lodestone:gravel", {13, std::monostate{}});
            registerBlock("lodestone:gold_ore", {14, std::monostate{}});
            registerBlock("lodestone:iron_ore", {15, std::monostate{}});
            registerBlock("lodestone:coal_ore", {16, std::monostate{}});
            registerBlock("lodestone:oak_log", {17, std::monostate{}});
            registerBlock("lodestone:oak_leaves", {18, std::monostate{}});
            registerBlock("lodestone:sponge", {19, std::monostate{}});
            registerBlock("lodestone:glass", {20, std::monostate{}});
            registerBlock("lodestone:red_wool", {21, std::monostate{}});
            registerBlock("lodestone:orange_wool", {22, std::monostate{}});
            registerBlock("lodestone:yellow_wool", {23, std::monostate{}});
            registerBlock("lodestone:chartreuse_wool", {24, std::monostate{}});
            registerBlock("lodestone:green_wool", {25, std::monostate{}});
            registerBlock("lodestone:spring_green_wool", {26, std::monostate{}});
            registerBlock("lodestone:cyan_wool", {27, std::monostate{}});
            registerBlock("lodestone:capri_wool", {28, std::monostate{}});
            registerBlock("lodestone:ultramarine_wool", {29, std::monostate{}});
            registerBlock("lodestone:purple_wool", {30, std::monostate{}});
            registerBlock("lodestone:violet_wool", {31, std::monostate{}});
            registerBlock("lodestone:magenta_wool", {32, std::monostate{}});
            registerBlock("lodestone:pink_wool", {33, std::monostate{}});
            registerBlock("lodestone:gray_wool", {34, std::monostate{}});
            registerBlock("lodestone:light_gray_wool", {35, std::monostate{}});
            registerBlock("lodestone:white_wool", {36, std::monostate{}});
            registerBlock("lodestone:dandelion", {37, std::monostate{}});
            registerBlock("lodestone:poppy", {38, std::monostate{}});
            registerBlock("lodestone:brown_mushroom", {39, std::monostate{}});
            registerBlock("lodestone:red_mushroom", {40, std::monostate{}});
            registerBlock("lodestone:gold_block", {41, std::monostate{}});
            registerBlock("lodestone:iron_block", {42, std::monostate{}});
            registerBlock("lodestone:double_smooth_stone_slab", {43, std::monostate{}});
            registerBlock("lodestone:smooth_stone_slab", {44, std::monostate{}});
            registerBlock("lodestone:bricks", {45, std::monostate{}});
            registerBlock("lodestone:tnt", {46, std::monostate{}});
            registerBlock("lodestone:bookshelf", {47, std::monostate{}});
            registerBlock("lodestone:mossy_cobblestone", {48, std::monostate{}});
            registerBlock("lodestone:obsidian", {49, std::monostate{}});
    }

    std::unordered_map<std::string, level::conversion::block::BlockIO<unsigned char>::Blk> &ClassicBlockIO::
    getConversionMap() {
        return mConversionMap;
    }

    std::unordered_map<unsigned char, std::monostate> &ClassicBlockIO::getDefaultDataMap() {
        return mDefaultDataMap;
    }

    void ClassicBlockIO::writeBlock(level::block::state::BlockState *b, uint8_t *arr) {
        *arr = convertBlockFromInternal(b).first;
    }
}
