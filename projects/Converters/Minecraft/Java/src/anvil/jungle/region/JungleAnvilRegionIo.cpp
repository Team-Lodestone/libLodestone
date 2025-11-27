//
// Created by DexrnZacAttack on 11/26/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/anvil/jungle/region/JungleAnvilRegionIo.h"

#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/anvil/jungle/chunk/JungleAnvilChunk.h"
#include "Lodestone.Minecraft.Java/anvil/jungle/chunk/JungleAnvilChunkIo.h"
#include "Lodestone.Minecraft.Java/anvil/jungle/region/JungleAnvilRegion.h"
#include <BinaryIO/BinaryBuffer.h>
#include <BinaryIO/stream/BinaryInputStream.h>
#include <Lodestone.Common/util/Logging.h>
#include <Lodestone.Conversion/chunk/ChunkIORegistry.h>
#include <Lodestone.Minecraft.Common/region/RegionChunkIndice.h>
#include <Lodestone.Minecraft.Common/region/RegionCompression.h>
#include <libnbt++/io/izlibstream.h>

#include <iostream>

namespace lodestone::minecraft::java::anvil::jungle::region {
    // The format is the same as the McRegion one since they never actually
    // changed the container format
    std::unique_ptr<level::region::Region>
    JungleAnvilRegionIO::read(std::istream &in, int version,
                              const level::types::Vec2i &coords) const {
        bio::stream::BinaryInputStream bis(in);

        auto chunkIo = dynamic_cast<const chunk::JungleAnvilChunkIO *>(
            getChunkIO(version));

        std::unique_ptr<level::region::Region> region =
            std::make_unique<JungleAnvilRegion>(coords);

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
            auto compression =
                static_cast<common::region::RegionCompression>(bis.readByte());

            if (compression == 0)
                continue;

            switch (compression) {
            case common::region::GZip:
            case common::region::Zlib: {
                zlib::izlibstream strm(bis.getStream());
                std::unique_ptr<chunk::JungleAnvilChunk> c = CAST_UNIQUE_PTR(
                    chunk::JungleAnvilChunk, chunkIo->read(strm, version));
                region->addChunk(std::move(c));

                break;
            }
            case common::region::Custom: {
                const uint16_t l = bis.readBE<uint16_t>();
                std::string name =
                    bis.readString(l); // who cares about mutf8 :trolley:

                LOG_WARNING("Unsupported compression type '" << name << "'");
                continue;
            }
            default:
                LOG_WARNING("Unsupported compression type "
                            << static_cast<int>(compression));
            }
        }

        return region;
    }
    void
    JungleAnvilRegionIO::write(lodestone::level::Level *c, int version,
                               const lodestone::level::types::Vec2i &coords,
                               std::ostream &out) const {}

    const conversion::chunk::ChunkIO *
    JungleAnvilRegionIO::getChunkIO(int version) const {
        return conversion::chunk::ChunkIORegistry::getInstance().getChunkIO(
            identifiers::ANVIL_JUNGLE);
    }
} // namespace lodestone::minecraft::java::anvil::jungle::region