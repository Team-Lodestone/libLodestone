//
// Created by DexrnZacAttack on 1/22/26 using zPc-i2.
//
#ifndef LODESTONE_AIRBLOCK_H
#define LODESTONE_AIRBLOCK_H
#include "Lodestone.Level/block/blocks/TranslucentBlock.h"

namespace lodestone::level::block::blocks {
    class AirBlock : public TranslucentBlock {
    public:
        constexpr AirBlock(const lodestone::common::registry::Identifier *id,
            const lodestone::level::material::Material &material)
: TranslucentBlock(id, material) {
        };

        constexpr bool heightmapShouldIgnore() const override {
            return true;
        };
    };
}

#endif // LODESTONE_AIRBLOCK_H