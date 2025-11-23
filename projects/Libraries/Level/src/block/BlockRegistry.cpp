#include "Lodestone.Level/block/BlockRegistry.h"

#include "Lodestone.Level/item/ItemRegistry.h"
#include <Lodestone.Common/util/Logging.h>

#if CMAKE_BUILD_DEBUG
#include <iostream>
#endif
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
namespace lodestone::level::block {
    const Block *BlockRegistry::sDefaultBlock =
        getInstance().getBlock(&Blocks::AIR);

    BlockRegistry::BlockRegistry() {
        REGISTER_BLOCK_FUNC(&Blocks::AIR, material::Material({0, 0, 0, 0}));
    }

    BlockRegistry &BlockRegistry::getInstance() {
        static BlockRegistry sInstance;
        return sInstance;
    }

    void BlockRegistry::registerBlock(
        const lodestone::common::registry::Identifier *id, const Block *block) {
        if (mBlocks.contains(id))
            throw std::runtime_error(
                std::format("Block '{}' is already registered", *id));

        item::ItemRegistry::getInstance().registerItem(id, block->getItem());
        mBlocks[id] = std::move(block);
        LOG_DEBUG("Registered block '" << *id << "'");
    }

    bool BlockRegistry::registerBlockIfNonExistent(
        const lodestone::common::registry::Identifier *id,
        const Block *block) noexcept {
        if (mBlocks.contains(id))
            return false;

        item::ItemRegistry::getInstance().registerItemIfNonExistent(
            id, block->getItem());
        mBlocks[id] = std::move(block);

        LOG_DEBUG("Registered block '" << *id << "'");
        return true;
    }

    const Block *BlockRegistry::getBlock(
        const lodestone::common::registry::Identifier *id) const {
        if (const auto it = mBlocks.find(id); it != mBlocks.end())
            return it->second;

        return nullptr;
    }

    const Block *BlockRegistry::operator[](
        const lodestone::common::registry::Identifier *id) const {
        return getBlock(id);
    }
} // namespace lodestone::level::block