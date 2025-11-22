//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONREGION_H
#define LODESTONE_MCREGIONREGION_H
#include <Lodestone.Level/region/Region.h>

namespace lodestone::minecraft::java::mcr::region {
    class McRegionRegion final : public level::region::Region {
      public:
        explicit McRegionRegion(const level::types::Vec2i &coords)
            : Region(coords) {}

        std::string getFilename() const;
        static level::types::Vec2i
        getCoordsFromFilename(const std::string &name);
    };
} // namespace lodestone::minecraft::java::mcr::region

#endif // LODESTONE_MCREGIONREGION_H
