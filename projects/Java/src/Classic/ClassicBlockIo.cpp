//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Classic/ClassicBlockIo.h"

namespace lodestone::java::classic {
    ClassicBlockIO *ClassicBlockIO::sInstance = new ClassicBlockIO();

    ClassicBlockIO::ClassicBlockIO() {
            registerBlock("lodestone:air", {0, std::monostate{}}, true);
            registerBlock("lodestone:stone", {1, std::monostate{}}, true);
            registerBlock("lodestone:grass_block", {2, std::monostate{}}, true);
            registerBlock("lodestone:dirt", {3, std::monostate{}}, true);
            registerBlock("lodestone:cobblestone", {4, std::monostate{}}, true);
            registerBlock("lodestone:oak_planks", {5, std::monostate{}}, true);
            registerBlock("lodestone:oak_sapling", {6, std::monostate{}}, true);
            registerBlock("lodestone:bedrock", {7, std::monostate{}}, true);
            registerBlock("lodestone:flowing_water", {8, std::monostate{}}, true);
            registerBlock("lodestone:water", {9, std::monostate{}}, true);
            registerBlock("lodestone:flowing_lava", {10, std::monostate{}}, true);
            registerBlock("lodestone:lava", {11, std::monostate{}}, true);
            registerBlock("lodestone:sand", {12, std::monostate{}}, true);
            registerBlock("lodestone:gravel", {13, std::monostate{}}, true);
            registerBlock("lodestone:gold_ore", {14, std::monostate{}}, true);
            registerBlock("lodestone:iron_ore", {15, std::monostate{}}, true);
            registerBlock("lodestone:coal_ore", {16, std::monostate{}}, true);
            registerBlock("lodestone:oak_log", {17, std::monostate{}}, true);
            registerBlock("lodestone:oak_leaves", {18, std::monostate{}}, true);
            registerBlock("lodestone:sponge", {19, std::monostate{}}, true);
            registerBlock("lodestone:glass", {20, std::monostate{}}, true);
            registerBlock("lodestone:red_wool", {21, std::monostate{}}, true);
            registerBlock("lodestone:orange_wool", {22, std::monostate{}}, true);
            registerBlock("lodestone:yellow_wool", {23, std::monostate{}}, true);
            registerBlock("lodestone:chartreuse_wool", {24, std::monostate{}}, true);
            registerBlock("lodestone:green_wool", {25, std::monostate{}}, true);
            registerBlock("lodestone:spring_green_wool", {26, std::monostate{}}, true);
            registerBlock("lodestone:cyan_wool", {27, std::monostate{}}, true);
            registerBlock("lodestone:capri_wool", {28, std::monostate{}}, true);
            registerBlock("lodestone:ultramarine_wool", {29, std::monostate{}}, true);
            registerBlock("lodestone:purple_wool", {30, std::monostate{}}, true);
            registerBlock("lodestone:violet_wool", {31, std::monostate{}}, true);
            registerBlock("lodestone:magenta_wool", {32, std::monostate{}}, true);
            registerBlock("lodestone:pink_wool", {33, std::monostate{}}, true);
            registerBlock("lodestone:gray_wool", {34, std::monostate{}}, true);
            registerBlock("lodestone:light_gray_wool", {35, std::monostate{}}, true);
            registerBlock("lodestone:white_wool", {36, std::monostate{}}, true);
            registerBlock("lodestone:dandelion", {37, std::monostate{}}, true);
            registerBlock("lodestone:poppy", {38, std::monostate{}}, true);
            registerBlock("lodestone:brown_mushroom", {39, std::monostate{}}, true);
            registerBlock("lodestone:red_mushroom", {40, std::monostate{}}, true);
            registerBlock("lodestone:gold_block", {41, std::monostate{}}, true);
            registerBlock("lodestone:iron_block", {42, std::monostate{}}, true);
            registerBlock("lodestone:double_smooth_stone_slab", {43, std::monostate{}}, true);
            registerBlock("lodestone:smooth_stone_slab", {44, std::monostate{}}, true);
            registerBlock("lodestone:bricks", {45, std::monostate{}}, true);
            registerBlock("lodestone:tnt", {46, std::monostate{}}, true);
            registerBlock("lodestone:bookshelf", {47, std::monostate{}}, true);
            registerBlock("lodestone:mossy_cobblestone", {48, std::monostate{}}, true);
            registerBlock("lodestone:obsidian", {49, std::monostate{}}, true);
    }

    std::unordered_map<unsigned char, std::monostate> &ClassicBlockIO::getDefaultDataMap() {
        return mDefaultDataMap;
    }

    void ClassicBlockIO::writeBlock(level::block::state::BlockState *b, uint8_t *arr) {
        *arr = convertBlockFromInternal(b).first;
    }

    std::unordered_map<std::string, level::conversion::block::BlockIO<unsigned char>::Blk> & ClassicBlockIO::
    getFromInternalConversionMap() {
        return this->mFromInternalConversionMap;
    }

    std::unordered_map<std::pair<unsigned char, std::monostate>, std::string, PairHash> & ClassicBlockIO::
    getToInternalConversionMap() {
        return this->mToInternalConversionMap;
    }
}
