//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Common/region/Region.h"

#include <Lodestone.Level/FiniteLevel.h>
#include <Lodestone.Level/types/Vec2.h>

namespace lodestone::minecraft::common::region {
    Region::Region(const lodestone::level::types::Vec2i &coords)
        : level::FiniteLevel(
              {{// min
                coords.x * MAX_BOUNDS.x, coords.y * MAX_BOUNDS.y},
               {// max
                (coords.x * MAX_BOUNDS.x) + MAX_BOUNDS.x - 1,
                (coords.y * MAX_BOUNDS.y) + MAX_BOUNDS.y - 1}}),
          m_coords(coords) {}
} // namespace lodestone::level::region
