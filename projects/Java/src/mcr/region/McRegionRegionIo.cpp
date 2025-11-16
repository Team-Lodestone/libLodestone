//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//

#include "Lodestone.Java/mcr/region/McRegionRegionIo.h"

#include <format>
#include <iostream>
#include <zlib.h>
#include <BinaryIO/BinaryBuffer.h>

#include "Lodestone.Java/Identifiers.h"
#include "Lodestone.Java/mcr/chunk/McRegionChunk.h"
#include "Lodestone.Java/mcr/chunk/McRegionChunkIo.h"
#include "Lodestone.Java/mcr/RegionChunkIndice.h"
#include "Lodestone.Java/mcr/RegionCompression.h"
#include <Lodestone.Conversion/chunk/ChunkIO.h>
#include <Lodestone.Conversion/chunk/ChunkIORegistry.h>
#include <Lodestone.Level/region/Region.h>

#include <BinaryIO/stream/BinaryInputStream.h>

#include <libnbt++/io/izlibstream.h>
#include "Lodestone.Java/mcr/region/McRegionRegion.h"

namespace lodestone::java::mcr::region {
    size_t McRegionRegionIO::getSize(lodestone::level::region::Region *c, int version) const {
    }

    std::unique_ptr<lodestone::level::region::Region> McRegionRegionIO::read(std::istream &in, const int version,
        const lodestone::level::types::Vec2i &coords) const {
        bio::stream::BinaryInputStream bis(in);

        const chunk::McRegionChunkIO *chunkIo = dynamic_cast<const chunk::McRegionChunkIO *>(
            lodestone::conversion::chunk::ChunkIORegistry::sInstance.getChunkIO(identifiers::MCREGION));

        std::unique_ptr<lodestone::level::region::Region> region = std::make_unique<McRegionRegion>(coords);

        std::vector<RegionChunkIndice> locations;
        locations.reserve(CHUNK_COUNT);

        uint8_t *locs = new uint8_t[CHUNK_COUNT * 4];
        bis.readInto(locs, CHUNK_COUNT * 4);

        uint8_t *timestamps = new uint8_t[CHUNK_COUNT * 4];
        bis.readInto(timestamps, CHUNK_COUNT * 4);

        bio::BinaryBuffer locBuf(locs);
        bio::BinaryBuffer timeBuf(timestamps);
        for (int i = 0; i < CHUNK_COUNT; i++) {
            const uint32_t offset = locBuf.readUint24(bio::util::ByteOrder::BIG);
            const uint8_t sz = locBuf.readByte();

            const int32_t timestamp = timeBuf.readBE<int32_t>();

            if (sz != 0 && offset != 0)
                locations.push_back({offset, sz, timestamp});
        }

        delete[] timestamps;
        delete[] locs;

        for (const auto loc: locations) {
            bis.seek(loc.offset * SECTOR_SIZE);

            uint32_t len = bis.readBE<uint32_t>();
            RegionCompression compression = static_cast<RegionCompression>(bis.readByte());

            if (compression == 0) continue;

            uint32_t chunkSize = loc.size * SECTOR_SIZE;

            bool fail = false;
            switch (compression) {
                case Zlib: {
                    zlib::izlibstream strm(bis.getStream());
                    std::unique_ptr<chunk::McRegionChunk> c = CAST_UNIQUE_PTR(chunk::McRegionChunk, chunkIo->read(
                        strm, version));
                    region->addChunk(std::move(c));

                    break;
                }
                case Custom: {
                    const uint16_t l = bis.readBE<uint16_t>();
                    std::string name = bis.readString(l); // who cares about mutf8 :trolley:

                    // don't throw as we can keep going
                    std::cerr << std::format("Unsupported compression type '{}'", name) << std::endl;
                    continue;
                }
                default:
                    std::cerr << std::format("Unsupported compression type '{}'", static_cast<int>(compression)) <<
                            std::endl;
                    continue;
            }
        }

        return region;
    }

    void McRegionRegionIO::write(lodestone::level::region::Region *c, int version,
        const lodestone::level::types::Vec2i &coords, std::ostream &out) const {
    }
}
