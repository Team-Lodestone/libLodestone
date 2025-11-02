#include "Block/BlockRegistry.h"

#if CMAKE_BUILD_DEBUG
    #include <iostream>
#endif
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
namespace lodestone::level::block {
    BlockRegistry BlockRegistry::sInstance = BlockRegistry();
    const Block *BlockRegistry::sDefaultBlock = sInstance.getBlock({ "lodestone", "air" });

    void BlockRegistry::registerBlock(const registry::NamespacedString &id, const Block *block) {
        if (mBlocks.contains(id))
            throw std::runtime_error(std::format("Block '{}' is already registered", id));

        mBlocks[id] = std::move(block);
#if CMAKE_BUILD_DEBUG
        std::cout << "Registered block '" << id << "'" << std::endl;
#endif
    }

    bool BlockRegistry::registerBlockIfNonExistent(const registry::NamespacedString &id, const Block *block) noexcept {
        if (mBlocks.contains(id))
            return false;

        mBlocks[id] = std::move(block);
#if CMAKE_BUILD_DEBUG
        std::cout << "Registered block '" << id << "'" << std::endl;
#endif

        return true;
    }

    const Block * BlockRegistry::getBlock(const std::string &id) const {
        if (const auto it = mBlocks.find(id); it != mBlocks.end())
            return it->second;

        return nullptr;
    }

    const Block * BlockRegistry::operator[](const std::string &id) const {
        return getBlock(id);
    }
}
