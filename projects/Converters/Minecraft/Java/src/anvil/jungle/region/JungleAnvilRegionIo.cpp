//
// Created by DexrnZacAttack on 11/26/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilRegionIo.h"

#include <libnbt++/io/ozlibstream.h>
#include <BinaryIO/stream/BinaryOutputStream.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/anvil/jungle/JungleAnvilChunk.h"
#include "Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilChunkIo.h"
#include "Lodestone.Minecraft.Java/anvil/jungle/JungleAnvilRegion.h"
#include <BinaryIO/buffer/BinaryBuffer.h>
#include <BinaryIO/stream/BinaryInputStream.h>
#include <Lodestone.Common/util/Logging.h>
#include <Lodestone.Minecraft.Common/region/RegionChunkIndice.h>
#include <Lodestone.Minecraft.Common/region/RegionCompression.h>
#include <libnbt++/io/izlibstream.h>

#include <iostream>

namespace lodestone::minecraft::java::anvil::jungle::region {
    // The format is the same as the McRegion one since they never actually
    // changed the container format
    std::unique_ptr<level::region::Region>
    JungleAnvilRegionIO::read(const common::conversion::io::options::OptionPresets::CommonChunkReadOptions &options) const {
        bio::stream::BinaryInputStream bis(options.input);

        auto chunkIo = this->getAsByRelation<const chunk::JungleAnvilChunkIO, &lodestone::conversion::identifiers::CHUNK_IO>();

        std::unique_ptr<level::region::Region> region =
            std::make_unique<JungleAnvilRegion>(options.coords);

        std::vector<common::region::RegionChunkIndice> locations;
        locations.reserve(CHUNK_COUNT);

        uint8_t *locs = new uint8_t[CHUNK_COUNT * 4];
        bis.readInto(locs, CHUNK_COUNT * 4);

        uint8_t *timestamps = new uint8_t[CHUNK_COUNT * 4];
        bis.readInto(timestamps, CHUNK_COUNT * 4);

        bio::buffer::BinaryBuffer locBuf(locs);
        bio::buffer::BinaryBuffer timeBuf(timestamps);
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
            case common::region::GZIP:
            case common::region::ZLIB: {
                zlib::izlibstream strm(bis.getStream());
                std::unique_ptr<chunk::JungleAnvilChunk> c = CAST_UNIQUE_PTR(
                    chunk::JungleAnvilChunk, chunkIo->read(common::conversion::io::options::OptionPresets::CommonReadOptions {
                        lodestone::conversion::io::options::fs::file::FileReaderOptions {
                            strm
                        },
                        conversion::io::options::versioned::VersionedOptions {
                            options.version
                        }
                    }));

                region->addChunk(std::move(c));

                break;
            }
            case common::region::CUSTOM: {
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

    void JungleAnvilRegionIO::write(lodestone::level::Level *c, const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions &options) const {
        bio::stream::BinaryOutputStream bos(options.output);

        auto *chunkIo = this->getAsByRelation<const chunk::JungleAnvilChunkIO, &lodestone::conversion::identifiers::CHUNK_IO>();

        bos.fill(0, (4 * 1024) * 2);

        // since this is such pain with a stream
        // although doing it like this is messy, I would like to refactor this
        // sometime. TODO
        for (char x = 0; x < 32; x++) {
            for (char z = 0; z < 32; z++) {
                // get chunk coords
                int cx = options.coords.x * 32 + x;
                int cz = options.coords.y * 32 + z;

                const size_t idx = ((cx & 31) + (cz & 31) * 32) * 4;

                // get our chunk
                level::chunk::Chunk *ch = c->getChunk(cx, cz);
                if (!ch)
                    continue;

                // get the position BEFORE we write the chunk
                const size_t s = bos.getOffset();

                bos.writeLE<int32_t>(0);             // size (temp)
                bos.writeByte(common::region::ZLIB); // compression

                // create z stream
                zlib::ozlibstream zs(bos.getStream());
                chunkIo->write(ch, common::conversion::io::options::OptionPresets::CommonChunkWriteOptions {
                                   common::conversion::io::options::ChunkOptions {
                                           {cx, cz}
                                   },
                                    common::conversion::io::options::OptionPresets::CommonWriteOptions {
                                        conversion::io::options::fs::file::FileWriterOptions {
                                            zs
                                        },
                                        conversion::io::options::versioned::VersionedOptions {
                                            options.version
                                        }
                                    }
                }); // write w/ zlib
                zs.close();

                // get it after, and get total bytes written
                const size_t se = bos.getOffset();
                const size_t sz = se - s;

                // and then we calculate some sector shit,
                // specifically how many sectors it will take up
                const size_t sc = (sz + SECTOR_SIZE - 1) / SECTOR_SIZE;

                // write sector padding
                bos.fill(0, sc * SECTOR_SIZE - sz);

                // get last position (needed to continue writing)
                const size_t sa = bos.getOffset();

                // write compressed size
                bos.seek(s);
                bos.writeBE<int32_t>(sz - 5);

                // now we seek back and write location
                bos.seek(idx);

                bos.writeInt24(s / 4096, bio::util::ByteOrder::BIG); // offset
                bos.writeByte(sc);                                   // size

                // write timestamp
                bos.seek(idx + SECTOR_SIZE);
                bos.writeBE<int32_t>(lodestone::common::util::Util::getCurrentTimeMillis());

                // seek back and write next one
                bos.seek(sa);
            }
        }
    }
} // namespace lodestone::minecraft::java::anvil::jungle::region