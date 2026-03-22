//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKITEM_H
#define LODESTONE_BLOCKITEM_H
#include "Lodestone.Level/item/Item.h"

namespace lodestone::level::item::block {
    class LODESTONE_LEVEL_API BlockItem final : public Item {
      public:
        constexpr BlockItem(const common::registry::Identifier *id,
                            const level::block::Block *block)
            : Item(id, nullptr, 64), m_block(block) {};

        constexpr const level::block::Block *getBlock() const {
            return m_block;
        };

      private:
        const lodestone::level::block::Block *m_block;
    };
} // namespace lodestone::level::item::block

#endif // LODESTONE_BLOCKITEM_H
