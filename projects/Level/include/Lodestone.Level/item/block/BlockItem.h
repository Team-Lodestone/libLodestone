//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKITEM_H
#define LODESTONE_BLOCKITEM_H
#include "Lodestone.Level/item/Item.h"

namespace lodestone::level::item::block {
    class BlockItem final : public Item {
    public:
        constexpr BlockItem(const common::registry::Identifier *id, const level::block::Block *block) : Item(id, 64), mBlock(block) {};

        constexpr const level::block::Block *getBlock() const {
            return mBlock;
        };

    private:
        const lodestone::level::block::Block *mBlock;
    };
}

#endif //LODESTONE_BLOCKITEM_H
