//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#include "Lodestone.Level/FiniteLevel.h"

namespace lodestone::level {
    FiniteLevel::FiniteLevel(const types::Bounds2i &bounds) : m_bounds(bounds) {}

    bool FiniteLevel::isChunkInBounds(const types::Vec2i &coords) {
        return !m_bounds.empty() && m_bounds.contains(coords);
    }

    const types::Bounds2i &FiniteLevel::getBounds() const { return m_bounds; }
} // namespace lodestone::level
