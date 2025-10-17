#include "Block/BlockRegistry.h"
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
namespace lodestone::level::block {
    BlockRegistry *BlockRegistry::sInstance = new BlockRegistry();
    const Block *BlockRegistry::sDefaultBlock = sInstance->getBlock("lodestone:air");

    void BlockRegistry::registerBlock(const std::string &id, const Block *block) {
        if (mBlocks.count(id))
            throw std::runtime_error("Block already exists");

        mBlocks[id] = std::move(block);
    }

    const Block * BlockRegistry::getBlock(const std::string &id) const {
        if (mBlocks.count(id))
            return mBlocks.at(id);

        return nullptr;
    }
}
