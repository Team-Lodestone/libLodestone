//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONREGIONIO_H
#define LODESTONE_MCREGIONREGIONIO_H
#include <cstdint>
#include <stddef.h>

#include <Lodestone.Conversion/region/RegionIO.h>
#include <Lodestone.Level/region/Region.h>
#include <Lodestone.Level/types/Vec2.h>

namespace lodestone::minecraft::java::mcregion::region {
    class McRegionRegionIO : public lodestone::conversion::region::RegionIO {
      public:
        static constexpr int CHUNK_COUNT = 1024;
        static constexpr int SECTOR_SIZE = 4096;

        std::unique_ptr<lodestone::level::region::Region>
        read(std::istream &in, int version,
             const lodestone::level::types::Vec2i &coords) const override;

        // We take coords here so we don't have to convert our existing Level
        // into a Region. The coords are enough information to correctly write
        // the chunks
        void write(lodestone::level::Level *c, int version,
                   const lodestone::level::types::Vec2i &coords,
                   std::ostream &out) const override;

        const conversion::chunk::ChunkIO *
        getChunkIO(int version) const override;
    };
} // namespace lodestone::minecraft::java::mcregion::region

#endif // LODESTONE_MCREGIONREGIONIO_H