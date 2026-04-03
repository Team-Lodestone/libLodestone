//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#ifndef LODESTONE_REGION_H
#define LODESTONE_REGION_H
#include <Lodestone.Level/FiniteLevel.h>

namespace lodestone::minecraft::common::region {
    /** A container which holds 32x32 chunks */
    class LODESTONE_API Region : public  lodestone::level::FiniteLevel {
      public:
        static constexpr lodestone::level::types::Vec2i MAX_BOUNDS = {32, 32};

        explicit Region(const lodestone::level::types::Vec2i &coords);

      protected:
        lodestone::level::types::Vec2i m_coords;
    };
} // namespace lodestone::minecraft::common::region

#endif // LODESTONE_REGION_H