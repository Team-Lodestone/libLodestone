//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#ifndef LODESTONE_REGION_H
#define LODESTONE_REGION_H
#include "Lodestone.Level/FiniteLevel.h"

namespace lodestone::level::region {
    /** A container which holds 32x32 chunks */
    class LODESTONE_API Region : public FiniteLevel {
      public:
        static constexpr types::Vec2i MAX_BOUNDS = {32, 32};

        explicit Region(const types::Vec2i &coords);

      protected:
        types::Vec2i mCoords;
    };
} // namespace lodestone::level::region

#endif // LODESTONE_REGION_H