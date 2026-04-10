//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONREGION_H
#define LODESTONE_MCREGIONREGION_H
#include <Lodestone.Minecraft.Common/region/Region.h>

namespace lodestone::minecraft::java::mcregion::region {
    class McRegionRegion : public common::region::Region {
      public:
        explicit McRegionRegion(const level::coords::ChunkCoordinates &coords)
            : Region(coords) {}

        std::string getFilename() const;
        static level::coords::ChunkCoordinates
        getCoordsFromFilename(const std::string &name);
    };
} // namespace lodestone::minecraft::java::mcregion::region

#endif // LODESTONE_MCREGIONREGION_H
