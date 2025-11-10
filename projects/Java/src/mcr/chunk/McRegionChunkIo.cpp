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
#include <Lodestone.Level/conversion/block/data/NumericBlockData.h>
#include "Lodestone.Java/mcr/chunk/McRegionChunk.h"

namespace lodestone::java::mcr::chunk {
    level::chunk::Chunk *McRegionChunkIO::read(uint8_t *data, const size_t size, const int version) const {
        std::istream buf(new common::io::DataBuffer(data, size));
        nbt::io::stream_reader streamReader = nbt::io::stream_reader(buf, endian::big);

        auto root = streamReader.read_compound();
        nbt::tag_compound &level = (root.second.get()->at("Level").as<nbt::tag_compound>());
        return read(level, version);
    }

    level::chunk::Chunk *McRegionChunkIO::read(nbt::tag_compound &chunk, const int version) const {
        int32_t x = chunk["xPos"].get().as<nbt::tag_int>().get();
        int32_t z = chunk["zPos"].get().as<nbt::tag_int>().get();
        const int64_t lastUpdate = chunk["LastUpdate"].get().as<nbt::tag_long>().get();
        const bool isPopulated = chunk["TerrainPopulated"].get().as<nbt::tag_byte>().get();
        const int8_t *blocks = chunk["Blocks"].get().as<nbt::tag_byte_array>().get().data();
        const int8_t *data = chunk["Data"].get().as<nbt::tag_byte_array>().get().data();

        McRegionChunk *c = new McRegionChunk({x, z}, lastUpdate, isPopulated);

        const std::unique_ptr<level::conversion::block::version::BlockIO> io = LodestoneJava::getInstance()->io.
                getIo(version);

        for (int cx = 0; cx < 16; cx++) {
            for (int cz = 0; cz < 16; cz++) {
                for (int cy = 0; cy < 128; cy++) {
                    const size_t idx = INDEX_XZY(cx, cy, cz, 128, 16);

                    const uint8_t d = data[idx];
                    const uint8_t dat = ((idx / 2) % 2 == 0) ? (d >> 4) & 0x0F : d & 0x0F;

                    level::block::state::BlockState b = io->convertBlockToInternal(
                        new level::conversion::block::data::NumericBlockData(
                            static_cast<uint8_t>(blocks[idx]),
                            0)); // TODO metadata (maybe MetadataIO or BlockPropertyIO?)

                    if (b.getBlock() != level::block::BlockRegistry::sDefaultBlock)
                        c->setBlockRaw(b, cx, cy, cz);
                }
            }
        }

        return c;
    }

    uint8_t *McRegionChunkIO::write(level::chunk::Chunk *c, int version) const {
    }

    nbt::tag_compound McRegionChunkIO::write(level::chunk::Chunk &c) const {
    }

    size_t McRegionChunkIO::getSize(level::chunk::Chunk *c, int version) const {
        return 0;
    }
}