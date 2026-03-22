//
// Created by DexrnZacAttack on 1/22/26 using zPc-i2.
//
#ifndef LODESTONE_AIRBLOCK_H
#define LODESTONE_AIRBLOCK_H
#include "Lodestone.Level/block/blocks/TranslucentBlock.h"

namespace lodestone::level::block::blocks {
    class LODESTONE_LEVEL_API AirBlock : public TranslucentBlock {
    public:
        constexpr AirBlock(const common::registry::Identifier *id,
            const material::Material &material, const properties::definition::ObjectDefinition *definition)
: TranslucentBlock(id, material, definition) {
        };

        constexpr bool heightmapShouldIgnore() const override {
            return true;
        };

        bool hasCollision() const override {
            return false;
        }
    };
}

#endif // LODESTONE_AIRBLOCK_H