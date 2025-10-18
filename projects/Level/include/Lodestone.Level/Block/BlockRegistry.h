//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKREGISTRY_H
#define LODESTONE_BLOCKREGISTRY_H
#include <unordered_map>

#include <Lodestone.Common/Defines.h>

#include "Lodestone.Level/Block/Block.h"
#include "Lodestone.Level/Block/Blocks.h"

namespace lodestone::level::block {
    class LODESTONE_API BlockRegistry {
    protected:
        BlockRegistry() = default;
    public:
#define REGISTER(n, m) {n, new Block(n, m)}

        static const Block *sDefaultBlock;
        static BlockRegistry sInstance;

        void registerBlock(const std::string &id, const Block* block);
        const Block *getBlock(const std::string &id) const;

        const Block *operator[](const std::string &) const;

        std::unordered_map<std::string, const Block*>::iterator begin() {
            return mBlocks.begin();
        }

        std::unordered_map<std::string, const Block*>::iterator end() {
            return mBlocks.end();
        }

    private:
        std::unordered_map<std::string, const Block*> mBlocks = {
            REGISTER(Blocks::AIR, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::STONE, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::GRASS_BLOCK, material::Material({127, 178, 56, 255})),
            REGISTER(Blocks::DIRT, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::COBBLESTONE, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::OAK_PLANKS, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::OAK_SAPLING, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::BEDROCK, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::FLOWING_WATER, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::WATER, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::FLOWING_LAVA, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::LAVA, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::SAND, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::GRAVEL, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::GOLD_ORE, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::IRON_ORE, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::COAL_ORE, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::OAK_LOG, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::OAK_LEAVES, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::SPONGE, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::GLASS, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::RED_WOOL, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::ORANGE_WOOL, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::YELLOW_WOOL, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::CHARTREUSE_WOOL, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::GREEN_WOOL, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::SPRING_GREEN_WOOL, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::CYAN_WOOL, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::CAPRI_WOOL, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::ULTRAMARINE_WOOL, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::PURPLE_WOOL, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::VIOLET_WOOL, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::MAGENTA_WOOL, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::PINK_WOOL, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::GRAY_WOOL, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::LIGHT_GRAY_WOOL, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::WHITE_WOOL, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::DANDELION, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::POPPY, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::BROWN_MUSHROOM, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::RED_MUSHROOM, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::GOLD_BLOCK, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::IRON_BLOCK, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::DOUBLE_SMOOTH_STONE_SLAB, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::SMOOTH_STONE_SLAB, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::BRICKS, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::TNT, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::BOOKSHELF, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::MOSSY_COBBLESTONE, material::Material({0, 0, 0, 0})),
            REGISTER(Blocks::OBSIDIAN, material::Material({0, 0, 0, 0})),
        };
    };
}

#endif //LODESTONE_BLOCKREGISTRY_H