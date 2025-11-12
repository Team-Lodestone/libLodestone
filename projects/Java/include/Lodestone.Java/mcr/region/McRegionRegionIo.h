//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONREGIONIO_H
#define LODESTONE_MCREGIONREGIONIO_H
#include <cstdint>
#include <stddef.h>

#include <Lodestone.Level/region/Region.h>
#include <Lodestone.Level/conversion/region/RegionIO.h>
#include <Lodestone.Level/types/Vec2.h>

namespace lodestone::java::mcr::region {
    class McRegionRegionIO : public level::conversion::region::RegionIO {
    public:
        static constexpr int CHUNK_COUNT = 1024;
        static constexpr int SECTOR_SIZE = 4096;

        /** Reads data into a new Region */
        lodestone::level::region::Region *read(uint8_t *data, size_t size, int version,
                                               const level::types::Vec2i &coords) override;

        /** Writes a region to data */
        uint8_t *write(lodestone::level::region::Region *c, int version, const level::types::Vec2i &coords) override;

        size_t getSize(lodestone::level::region::Region *c, int version) override;
    };
}

#endif //LODESTONE_MCREGIONREGIONIO_H