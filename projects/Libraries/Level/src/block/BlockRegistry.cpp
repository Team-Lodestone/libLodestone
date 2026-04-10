#include "Lodestone.Level/block/BlockRegistry.h"

#include "Lodestone.Level/item/ItemRegistry.h"
#include <Lodestone.Common/util/Logging.h>

#include "Lodestone.Level/block/blocks/AirBlock.h"

#if CMAKE_BUILD_DEBUG
#include <iostream>
#endif
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
namespace lodestone::level::block {
    const Block *BlockRegistry::s_defaultBlock =
        getInstance().getBlock(&Blocks::NONE);

    BlockRegistry::BlockRegistry() {
        REGISTER_DERIVED_BLOCK_FUNC(&Blocks::NONE, material::Material({0, 0, 0, 0}), nullptr, blocks::AirBlock);
    }

    BlockRegistry &BlockRegistry::getInstance() {
        static BlockRegistry s_instance;
        return s_instance;
    }

    void BlockRegistry::registerBlock(
        const lodestone::common::registry::Identifier *id, const Block *block) {
        if (m_blocks.contains(id))
            throw std::runtime_error(
                std::format("Block '{}' is already registered", *id));

        item::ItemRegistry::getInstance().registerItem(id, block->getItem());
        m_blocks[id] = block;
        // LOG_DEBUG("Registered block '" << *id << "'");

        this->blockRegisteredEvent.notify(id, block);
    }

    bool BlockRegistry::registerBlockIfNonExistent(
        const lodestone::common::registry::Identifier *id,
        const Block *block) noexcept {
        if (m_blocks.contains(id))
            return false;

        item::ItemRegistry::getInstance().registerItemIfNonExistent(
            id, block->getItem());
        m_blocks[id] = std::move(block);

        this->blockRegisteredEvent.notify(id, block);
        return true;
    }

    const Block *BlockRegistry::getBlock(
        const lodestone::common::registry::Identifier *id) const {
        if (const auto it = m_blocks.find(id); it != m_blocks.end())
            return it->second;

        return nullptr;
    }

    const Block *BlockRegistry::operator[](
        const lodestone::common::registry::Identifier *id) const {
        return getBlock(id);
    }
} // namespace lodestone::level::block