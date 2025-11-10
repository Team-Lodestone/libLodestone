//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//

#include "mcr/region/McRegionRegionIo.h"

#include <format>
#include <iostream>
#include <BinaryIO/BinaryIO.h>

#include "Identifiers.h"
#include "Lodestone.Java/mcr/chunk/McRegionChunk.h"
#include "Lodestone.Java/mcr/chunk/McRegionChunkIo.h"
#include "Lodestone.Java/mcr/RegionChunkIndice.h"
#include "Lodestone.Java/mcr/RegionCompression.h"
#include "io/zlib_streambuf.h"
#include "Lodestone.Level/conversion/chunk/ChunkIO.h"
#include "Lodestone.Level/conversion/chunk/ChunkIORegistry.h"
#include "Lodestone.Level/region/Region.h"

namespace lodestone::java::mcr::region {
    lodestone::level::region::Region * McRegionRegionIO::read(uint8_t *data, size_t size, const int version, const level::types::Vec2i &coords) {
        bio::BinaryIO io(data);

        const chunk::McRegionChunkIO *chunkIo = dynamic_cast<const chunk::McRegionChunkIO*>(level::conversion::chunk::ChunkIORegistry::sInstance.getChunkIO(identifiers::MCREGION));

        lodestone::level::region::Region *region = new lodestone::level::region::Region(coords);

        std::vector<RegionChunkIndice> locations(CHUNK_COUNT);
        bio::BinaryIO timestampIo(io.getDataRelative() + (CHUNK_COUNT * 4));
        for (int i = 0; i < CHUNK_COUNT; i++) {
            const uint32_t offset = io.readUint24(bio::ByteOrder::BIG);
            const uint8_t sz = io.readByte();

            const int32_t timestamp = timestampIo.readBE<int32_t>();

            if (sz != 0 && offset != 0)
                locations.push_back({offset, sz, timestamp});
        }

        io.seek((CHUNK_COUNT * 4) * 2);

        for (const auto loc : locations) {
            io.seek(loc.offset * SECTOR_SIZE);

            uint32_t len = io.readBE<uint32_t>();
            RegionCompression compression = static_cast<RegionCompression>(io.readByte());

            uint32_t chunkSize = loc.size * SECTOR_SIZE;

            bool fail = false;
            switch (compression) {
                case Zlib: {
                    z_stream s{};
                    s.next_in = (Bytef*)io.getDataRelative();
                    s.avail_in = (chunkSize) - 5;

                    if (inflateInit(&s) != Z_OK) {
                        std::cerr << "Failed to decompress chunk" << std::endl;
                        continue;
                    }

                    std::vector<uint8_t> decompressed;

                    int res = Z_OK;
                    uint8_t tmpOut[chunkSize];

                    while (res != Z_STREAM_END) {
                        s.next_out = tmpOut;
                        s.avail_out = chunkSize;

                        res = inflate(&s, Z_NO_FLUSH);

                        if (res != Z_OK && res != Z_STREAM_END && res != Z_BUF_ERROR) {
                            inflateEnd(&s);
                            std::cerr << std::format("Failed to inflate: code {}", res);

                            fail = true;
                            break;
                        }

                        decompressed.insert(decompressed.end(), tmpOut, tmpOut + (chunkSize - s.avail_out));
                    }

                    if (fail) continue;

                    // now we process the chunk
                    chunk::McRegionChunk *c = static_cast<chunk::McRegionChunk *>(chunkIo->read(decompressed.data(), decompressed.size(), version));
                    region->addChunk(std::unique_ptr<chunk::McRegionChunk>(c));

                    break;
                }
                case Custom: {
                    const uint16_t l = io.readBE<uint16_t>();
                    std::string name = io.readString(l); // who cares about mutf8 :trolley:

                    // don't throw as we can keep going
                    std::cerr << std::format("Unsupported compression type '{}'", name) << std::endl;
                    continue;
                }
                default:
                    std::cerr << std::format("Unsupported compression type '{}'", static_cast<int>(compression)) << std::endl;
                    continue;
            }
        }

        return region;
    }

    uint8_t * McRegionRegionIO::write(lodestone::level::region::Region *c, int version, const level::types::Vec2i &coords) {
    }

    size_t McRegionRegionIO::getSize(lodestone::level::region::Region *c, int version) {
    }
}
