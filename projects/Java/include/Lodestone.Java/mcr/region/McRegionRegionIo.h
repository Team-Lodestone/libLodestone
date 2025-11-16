//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONREGIONIO_H
#define LODESTONE_MCREGIONREGIONIO_H
#include <cstdint>
#include <stddef.h>

#include <Lodestone.Level/region/Region.h>
#include <Lodestone.Conversion/region/RegionIO.h>
#include <Lodestone.Level/types/Vec2.h>

namespace lodestone::java::mcr::region {
    class McRegionRegionIO : public lodestone::conversion::region::RegionIO {
    public:
        static constexpr int CHUNK_COUNT = 1024;
        static constexpr int SECTOR_SIZE = 4096;

        size_t getSize(lodestone::level::region::Region *c, int version) const override;

        std::unique_ptr<lodestone::level::region::Region> read(std::istream &in, int version,
            const lodestone::level::types::Vec2i &coords) const override;

        void write(lodestone::level::region::Region *c, int version, const lodestone::level::types::Vec2i &coords,
            std::ostream &out) const override;
    };
}

#endif //LODESTONE_MCREGIONREGIONIO_H