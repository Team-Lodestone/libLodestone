//
// Created by DexrnZacAttack on 1/22/26 using zPc-i2.
//
#ifndef LODESTONE_TRANSLUCENTBLOCK_H
#define LODESTONE_TRANSLUCENTBLOCK_H
#include "Lodestone.Level/block/Block.h"

namespace lodestone::level::block::blocks {
    // transculent
    // welcome back notch
    class TranslucentBlock : public lodestone::level::block::Block {
    public:
        constexpr TranslucentBlock(const lodestone::common::registry::Identifier *id,
                    const lodestone::level::material::Material &material, const properties::definition::ObjectDefinition *definition)
        : Block(id, material, definition) {
        };

        constexpr bool isTransparent() const override {
            return true;
        }
    };
}

#endif // LODESTONE_TRANSLUCENTBLOCK_H