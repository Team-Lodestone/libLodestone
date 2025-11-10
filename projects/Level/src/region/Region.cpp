//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#include "Lodestone.Level/region/Region.h"

#include "Lodestone.Level/FiniteLevel.h"
#include "Lodestone.Level/types/Vec2i.h"

namespace lodestone::level::region {
    Region::Region(const types::Vec2i &coords) : level::FiniteLevel(
                                                     {
                                                         {
                                                             // min
                                                             coords.x * MAX_BOUNDS.x,
                                                             coords.z * MAX_BOUNDS.z
                                                         },
                                                         {
                                                             // max
                                                             (coords.x * MAX_BOUNDS.x) + MAX_BOUNDS.x - 1,
                                                             (coords.z * MAX_BOUNDS.z) + MAX_BOUNDS.z - 1
                                                         }
                                                     }
                                                 ), mCoords(coords) {
    }
}
