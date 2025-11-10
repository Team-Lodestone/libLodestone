//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_REGIONIO_H
#define LODESTONE_REGIONIO_H
#include "Lodestone.Level/region/Region.h"
#include "Lodestone.Common/Defines.h"
#include "Lodestone.Level/types/Vec2i.h"

namespace lodestone::level::conversion::region {
    class LODESTONE_API RegionIO {
    public:
        virtual ~RegionIO() = default;

        /** Reads data into a new Region */
        virtual lodestone::level::region::Region *read(uint8_t *data, size_t size, int version, const types::Vec2i &coords) = 0;
        /** Writes a region to data */
        virtual uint8_t *write(lodestone::level::region::Region *c, int version, const types::Vec2i &coords) = 0;
        /** Gets the size of the region in bytes */
        virtual size_t getSize(lodestone::level::region::Region *c, int version) = 0;
    };
}

#endif //LODESTONE_REGIONIO_H
