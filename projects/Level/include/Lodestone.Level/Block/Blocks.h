//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKS_H
#define LODESTONE_BLOCKS_H
#include <unordered_map>

#include <Lodestone.Common/Defines.h>

#include "Lodestone.Level/Block/Block.h"

namespace lodestone::level::block {
    class LODESTONE_API Blocks {
    protected:
        Blocks();
    public:
#define REGISTER(n, m) {n, new Block(n, material::Material({0, 0, 0, 0}))}

        static const Block *sDefaultBlock;
        static Blocks *sInstance;

        void registerBlock(const std::string &id, const Block* block);
        const Block *getBlock(const std::string &id) const;

    private:
        std::unordered_map<std::string, const Block*> mBlocks = {
            REGISTER("lodestone:air", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:stone", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:grass_block", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:dirt", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:cobblestone", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:oak_planks", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:oak_sapling", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:bedrock", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:flowing_water", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:water", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:flowing_lava", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:lava", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:sand", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:gravel", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:gold_ore", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:iron_ore", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:coal_ore", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:oak_log", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:oak_leaves", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:sponge", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:glass", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:red_wool", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:orange_wool", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:yellow_wool", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:chartreuse_wool", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:green_wool", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:spring_green_wool", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:cyan_wool", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:capri_wool", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:ultramarine_wool", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:purple_wool", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:violet_wool", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:magenta_wool", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:pink_wool", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:gray_wool", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:light_gray_wool", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:white_wool", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:dandelion", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:poppy", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:brown_mushroom", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:red_mushroom", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:gold_block", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:iron_block", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:double_smooth_stone_slab", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:smooth_stone_slab", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:bricks", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:tnt", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:dandelion", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:bookshelf", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:mossy_cobblestone", material::Material({0, 0, 0, 0})),
            REGISTER("lodestone:obsidian", material::Material({0, 0, 0, 0})),
        };
    };
}

#endif //LODESTONE_BLOCKS_H