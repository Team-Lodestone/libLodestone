//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#include "FiniteLevel.h"

namespace lodestone::level {
    FiniteLevel::FiniteLevel(const types::Bounds2i &bounds) : mBounds(bounds) {}

    bool FiniteLevel::isChunkInBounds(const types::Vec2i &coords) {
        return !mBounds.empty() && mBounds.contains(coords);
    }

    const types::Bounds2i & FiniteLevel::getBounds() const {
        return mBounds;
    }
}
