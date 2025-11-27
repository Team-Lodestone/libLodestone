//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//

#include "Lodestone.Minecraft.Java/mcregion/region/McRegionRegionIo.h"

#include <BinaryIO/BinaryBuffer.h>
#include <format>
#include <iostream>
#ifdef USE_OPENMP
#include <omp.h>
#endif
#include <Lodestone.Minecraft.Common/region/RegionChunkIndice.h>
#include <Lodestone.Minecraft.Common/region/RegionCompression.h>

#include <zlib.h>

#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/mcregion/chunk/McRegionChunk.h"
#include "Lodestone.Minecraft.Java/mcregion/chunk/McRegionChunkIo.h"
#include <Lodestone.Conversion/chunk/ChunkIO.h>
#include <Lodestone.Conversion/chunk/ChunkIORegistry.h>
#include <Lodestone.Level/region/Region.h>

#include <BinaryIO/stream/BinaryInputStream.h>

#include <libnbt++/io/izlibstream.h>

#include "Lodestone.Minecraft.Java/mcregion/region/McRegionRegion.h"
#include <BinaryIO/stream/BinaryOutputStream.h>
#include <libnbt++/io/ozlibstream.h>

namespace lodestone::minecraft::java::mcregion::region {

    std::unique_ptr<lodestone::level::region::Region>
    McRegionRegionIO::read(std::istream &in, const int version,
                           const lodestone::level::types::Vec2i &coords) const {
        bio::stream::BinaryInputStream bis(in);

        const chunk::McRegionChunkIO *chunkIo =
            dynamic_cast<const chunk::McRegionChunkIO *>(getChunkIO(version));

        std::unique_ptr<lodestone::level::region::Region> region =
            std::make_unique<McRegionRegion>(coords);

        std::vector<common::region::RegionChunkIndice> locations;
        locations.reserve(CHUNK_COUNT);

        uint8_t *locs = new uint8_t[CHUNK_COUNT * 4];
        bis.readInto(locs, CHUNK_COUNT * 4);

        uint8_t *timestamps = new uint8_t[CHUNK_COUNT * 4];
        bis.readInto(timestamps, CHUNK_COUNT * 4);

        bio::BinaryBuffer locBuf(locs);
        bio::BinaryBuffer timeBuf(timestamps);
        for (int i = 0; i < CHUNK_COUNT; i++) {
            const uint32_t offset =
                locBuf.readUint24(bio::util::ByteOrder::BIG);
            const uint8_t sz = locBuf.readByte();

            const int32_t timestamp = timeBuf.readBE<int32_t>();

            if (sz != 0 && offset != 0)
                locations.push_back({offset, sz, timestamp});
        }

        delete[] timestamps;
        delete[] locs;

        for (const auto loc : locations) {
            bis.seek(loc.offset * SECTOR_SIZE);

            uint32_t len = bis.readBE<uint32_t>();
            common::region::RegionCompression compression =
                static_cast<common::region::RegionCompression>(bis.readByte());

            if (compression == 0)
                continue;

            switch (compression) {
            case common::region::GZip:
            case common::region::Zlib: {
                zlib::izlibstream strm(bis.getStream());
                std::unique_ptr<chunk::McRegionChunk> c = CAST_UNIQUE_PTR(
                    chunk::McRegionChunk, chunkIo->read(strm, version));
                region->addChunk(std::move(c));

                break;
            }
            default:
                std::cerr << std::format("Unsupported compression type '{}'",
                                         static_cast<int>(compression))
                          << std::endl;
                continue;
            }
        }

        return region;
    }

    void McRegionRegionIO::write(lodestone::level::Level *c, const int version,
                                 const lodestone::level::types::Vec2i &coords,
                                 std::ostream &out) const {
        bio::stream::BinaryOutputStream bos(out);

        const chunk::McRegionChunkIO *chunkIo =
            dynamic_cast<const chunk::McRegionChunkIO *>(getChunkIO(version));

        bos.fill(0, (4 * 1024) * 2);

        const int minX = coords.x << 5;
        const int minZ = coords.z << 5;

        // since this is such pain with a stream
        // although doing it like this is messy, I would like to refactor this
        // sometime. TODO
        for (char x = 0; x < 16; x++) {
            for (char z = 0; z < 16; z++) {
                // get chunk coords
                int cx = minX + x;
                int cz = minZ + z;

                size_t idx = ((cx % 32) + (cz % 32) * 32) * 4;

                // get our chunk
                level::chunk::Chunk *ch = c->getChunk(cx, cz);
                if (!ch)
                    continue;

                // get the position BEFORE we write the chunk
                const size_t s = bos.getPosition();

                bos.writeLE<int32_t>(0);             // size (temp)
                bos.writeByte(common::region::Zlib); // compression

                // create z stream
                zlib::ozlibstream zs(bos.getStream());
                chunkIo->write(ch, {cx, cz}, version, zs); // write w/ zlib
                zs.close();

                // get it after, and get total bytes written
                const size_t se = bos.getPosition();
                const size_t sz = se - s;

                // and then we calculate some sector shit,
                // specifically how many sectors it will take up
                const size_t sc = (sz + SECTOR_SIZE - 1) / SECTOR_SIZE;

                // write sector padding
                bos.fill(0, sc * SECTOR_SIZE - sz);

                // get last position (needed to continue writing)
                const size_t sa = bos.getPosition();

                // write compressed size
                bos.seek(s);
                bos.writeBE<int32_t>(sz - 5);

                // now we seek back and write location
                bos.seek(idx);

                bos.writeInt24(s / 4096, bio::util::ByteOrder::BIG); // offset
                bos.writeByte(sc);                                   // size

                // write timestamp
                bos.seek(idx + SECTOR_SIZE);
                bos.writeBE<int32_t>(lodestone::common::getCurrentTimeMillis());

                // seek back and write next one
                bos.seek(sa);
            }
        }
    }

    const conversion::chunk::ChunkIO *
    McRegionRegionIO::getChunkIO(int version) const {
        return conversion::chunk::ChunkIORegistry::getInstance().getChunkIO(
            identifiers::MCREGION);
    }
} // namespace lodestone::minecraft::java::mcregion::region
