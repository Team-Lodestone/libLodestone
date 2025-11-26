//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_REGIONIO_H
#define LODESTONE_REGIONIO_H
#include <Lodestone.Common/Defines.h>
#include <Lodestone.Level/region/Region.h>
#include <Lodestone.Level/types/Vec2.h>

#include "Lodestone.Conversion/chunk/ChunkIO.h"

namespace lodestone::conversion::region {
    class LODESTONE_API RegionIO {
      public:
        virtual ~RegionIO() = default;

        /** Creates a new Region from data in the given input stream */
        virtual std::unique_ptr<lodestone::level::region::Region>
        read(std::istream &in, int version,
             const lodestone::level::types::Vec2i &coords) const = 0;

        /** Writes a 512*512 to the given output stream */
        virtual void write(lodestone::level::Level *c, int version,
                           const lodestone::level::types::Vec2i &coords,
                           std::ostream &out) const = 0;

        virtual const chunk::ChunkIO *getChunkIO(int version) const = 0;
    };
} // namespace lodestone::conversion::region

#endif // LODESTONE_REGIONIO_H