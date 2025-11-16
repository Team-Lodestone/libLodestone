//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#include "Lodestone.Java/mcr/chunk/McRegionChunkIo.h"

#include <iostream>

#include "Lodestone.Java/LodestoneJava.h"
#include <libnbt++/tag_primitive.h>
#include <libnbt++/tag_array.h>
#include <libnbt++/io/stream_reader.h>
#include <Lodestone.Common/io/DataBuffer.h>
#include <Lodestone.Common/Indexing.h>
#include <Lodestone.Conversion/block/data/NumericBlockData.h>
#include "Lodestone.Java/mcr/chunk/McRegionChunk.h"

namespace lodestone::java::mcr::chunk {
    std::unique_ptr<level::chunk::Chunk> McRegionChunkIO::read(nbt::tag_compound &chunk, const int version) const {
        const int32_t x = chunk["xPos"].get().as<nbt::tag_int>().get();
        const int32_t z = chunk["zPos"].get().as<nbt::tag_int>().get();
        const int64_t lastUpdate = chunk["LastUpdate"].get().as<nbt::tag_long>().get();
        const int8_t *blocks = chunk["Blocks"].get().as<nbt::tag_byte_array>().get().data();
        const int8_t *data = chunk["Data"].get().as<nbt::tag_byte_array>().get().data();

        std::unique_ptr<McRegionChunk> c = std::make_unique<McRegionChunk>(level::types::Vec2i(x, z), lastUpdate);

        const std::unique_ptr<lodestone::conversion::block::version::BlockIO> io = LodestoneJava::getInstance()->io.
                getIo(version);

        for (int cx = 0; cx < 16; cx++) {
            for (int cz = 0; cz < 16; cz++) {
                for (int cy = 0; cy < 128; cy++) {
                    const size_t idx = INDEX_XZY(cx, cy, cz, 128, 16);

                    const uint8_t bb = blocks[idx];

#ifdef USE_RISKY_OPTIMIZATIONS
                    if (bb == 0) // since air is id 0
                        continue; // this skips us having to convert the block
#endif

                    const uint8_t d = data[idx];
                    const uint8_t dat = ((idx / 2) % 2 == 0) ? (d >> 4) & 0x0F : d & 0x0F;

                    level::block::properties::BlockProperties b = io->convertBlockToInternal(
                    lodestone::conversion::block::data::NumericBlockData(
                            bb,
                            0)); // TODO metadata (maybe MetadataIO or BlockPropertyIO?)

                    if (b.getBlock() != level::block::BlockRegistry::sDefaultBlock)
                        c->McRegionChunk::setBlockRaw(std::move(b), cx, cy, cz);
                }
            }
        }
        
        return c;
    }

    nbt::tag_compound McRegionChunkIO::write(level::chunk::Chunk &c) const {
    }

    size_t McRegionChunkIO::getSize(level::chunk::Chunk *c, int version) const {
        return 0;
    }

    std::unique_ptr<lodestone::level::chunk::Chunk> McRegionChunkIO::read(std::istream &in, const int version) const {
        nbt::io::stream_reader streamReader = nbt::io::stream_reader(in, endian::big);

        auto [name, root] = streamReader.read_compound();
        nbt::tag_compound &level = (root.get()->at("Level").as<nbt::tag_compound>());
        return read(level, version);
    }

    void McRegionChunkIO::write(lodestone::level::chunk::Chunk *c, int version, std::ostream &out) const {
    }
}
