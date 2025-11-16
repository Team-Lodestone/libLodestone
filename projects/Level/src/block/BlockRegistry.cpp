#include "Lodestone.Level/block/BlockRegistry.h"

#include "Lodestone.Level/item/ItemRegistry.h"

#if CMAKE_BUILD_DEBUG
#include <iostream>
#endif
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
namespace lodestone::level::block {
    const Block *BlockRegistry::sDefaultBlock = getInstance().getBlock(&Blocks::AIR);

    BlockRegistry::BlockRegistry() {
        REGISTER_BLOCK_FUNC(&Blocks::AIR, material::Material({0, 0, 0, 0}));
            // TODO make Minecraft project which just initializes minecraft blocks & items
        REGISTER_BLOCK_FUNC(&Blocks::STONE, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::GRASS_BLOCK, material::Material({127, 178, 56, 255}));
        REGISTER_BLOCK_FUNC(&Blocks::DIRT, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::COBBLESTONE, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::OAK_PLANKS, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::OAK_SAPLING, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::BEDROCK, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::FLOWING_WATER, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::WATER, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::FLOWING_LAVA, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::LAVA, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::SAND, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::GRAVEL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::GOLD_ORE, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::IRON_ORE, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::COAL_ORE, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::OAK_LOG, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::OAK_LEAVES, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::SPONGE, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::GLASS, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::RED_WOOL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::ORANGE_WOOL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::YELLOW_WOOL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::CHARTREUSE_WOOL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::LIME_WOOL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::SPRING_GREEN_WOOL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::CYAN_WOOL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::CAPRI_WOOL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::LIGHT_BLUE_WOOL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::ULTRAMARINE_WOOL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::PURPLE_WOOL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::VIOLET_WOOL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::MAGENTA_WOOL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::PINK_WOOL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::GRAY_WOOL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::LIGHT_GRAY_WOOL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::WHITE_WOOL, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::DANDELION, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::POPPY, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::BROWN_MUSHROOM, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::RED_MUSHROOM, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::GOLD_BLOCK, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::IRON_BLOCK, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::DOUBLE_SMOOTH_STONE_SLAB, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::SMOOTH_STONE_SLAB, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::BRICKS, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::TNT, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::BOOKSHELF, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::MOSSY_COBBLESTONE, material::Material({0, 0, 0, 0}));
        REGISTER_BLOCK_FUNC(&Blocks::OBSIDIAN, material::Material({0, 0, 0, 0}));
    }

    BlockRegistry &BlockRegistry::getInstance()  {
        static BlockRegistry sInstance;
        return sInstance;
    }

    void BlockRegistry::registerBlock(const lodestone::common::registry::Identifier *id, const Block *block) {
        if (mBlocks.contains(id))
            throw std::runtime_error(std::format("Block '{}' is already registered", *id));

        item::ItemRegistry::getInstance().registerItem(id, block->getItem());
        mBlocks[id] = std::move(block);
#if CMAKE_BUILD_DEBUG
        std::cout << "Registered block '" << *id << "'" << std::endl;
#endif
    }

    bool BlockRegistry::registerBlockIfNonExistent(const lodestone::common::registry::Identifier *id,
                                                   const Block *block) noexcept {
        if (mBlocks.contains(id))
            return false;

        item::ItemRegistry::getInstance().registerItemIfNonExistent(id, block->getItem());
        mBlocks[id] = std::move(block);


#if CMAKE_BUILD_DEBUG
        std::cout << "Registered block '" << *id << "'" << std::endl;
#endif

        return true;
    }

    const Block *BlockRegistry::getBlock(const lodestone::common::registry::Identifier *id) const {
        if (const auto it = mBlocks.find(id); it != mBlocks.end())
            return it->second;

        return nullptr;
    }

    const Block *BlockRegistry::operator[](const lodestone::common::registry::Identifier *id) const {
        return getBlock(id);
    }
}