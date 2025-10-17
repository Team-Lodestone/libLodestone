#include "Block/Blocks.h"
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
namespace lodestone::level::block {
    Blocks *Blocks::sInstance = new Blocks();
    const Block *Blocks::sDefaultBlock = Blocks::sInstance->getBlock("lodestone:air");

    Blocks::Blocks() {
    }

    void Blocks::registerBlock(const std::string &id, const Block *block) {
        if (mBlocks.count(id))
            throw std::runtime_error("Block already exists");

        mBlocks[id] = std::move(block);
    }

    const Block * Blocks::getBlock(const std::string &id) const {
        if (mBlocks.count(id))
            return mBlocks.at(id);

        return nullptr;
    }
}
