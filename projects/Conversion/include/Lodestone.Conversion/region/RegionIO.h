//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_REGIONIO_H
#define LODESTONE_REGIONIO_H
#include <Lodestone.Level/region/Region.h>
#include <Lodestone.Common/Defines.h>
#include <Lodestone.Level/types/Vec2.h>

namespace lodestone::conversion::region {
    class LODESTONE_API RegionIO {
    public:
        virtual ~RegionIO() = default;

        /** Reads data into a new Region */
        virtual std::unique_ptr<lodestone::level::region::Region> read(uint8_t *data, size_t size, int version,
                                                       const lodestone::level::types::Vec2i &coords) const = 0;

        /** Writes a region to data */
        virtual uint8_t *write(lodestone::level::region::Region *c, int version, const lodestone::level::types::Vec2i &coords) const = 0;

        /** Gets the size of the region in bytes */
        virtual size_t getSize(lodestone::level::region::Region *c, int version) const = 0;
    };
}

#endif //LODESTONE_REGIONIO_H