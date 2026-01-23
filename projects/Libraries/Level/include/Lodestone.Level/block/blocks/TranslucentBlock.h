//
// Created by DexrnZacAttack on 1/22/26 using zPc-i2.
//
#ifndef LODESTONE_TRANSLUCENTBLOCK_H
#define LODESTONE_TRANSLUCENTBLOCK_H
#include "Lodestone.Level/block/Block.h"

namespace lodestone::level::block::blocks {
    class TranslucentBlock : public lodestone::level::block::Block {
    public:
        constexpr TranslucentBlock(const lodestone::common::registry::Identifier *id,
                    const lodestone::level::material::Material &material)
        : Block(id, material) {
        };

        constexpr bool isTransparent() const override {
            return true;
        }
    };
}

#endif // LODESTONE_TRANSLUCENTBLOCK_H