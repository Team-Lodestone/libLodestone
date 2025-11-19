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

#include <libnbt++/tag_list.h>
#include "Lodestone.Java/mcr/chunk/McRegionChunk.h"
#include <Lodestone.Common/Indexing.h>

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

        for (int cx = 0; cx < CHUNK_WIDTH; cx++) {
            for (int cz = 0; cz < CHUNK_DEPTH; cz++) {
                for (int cy = 0; cy < CHUNK_HEIGHT; cy++) {
                    const size_t idx = INDEX_XZY(cx, cy, cz, CHUNK_HEIGHT, CHUNK_DEPTH);

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
                        c->McRegionChunk::setBlock(std::move(b), cx, cy, cz);
                }
            }
        }
        
        return c;
    }

    nbt::tag_compound McRegionChunkIO::write(level::chunk::Chunk *c, const level::types::Vec2i &coords, const int version) const {
        nbt::tag_compound root{};
        nbt::tag_compound level{};

        const std::unique_ptr<lodestone::conversion::block::version::BlockIO> bio = LodestoneJava::getInstance()->io.
                getIo(version);

        // todo make sure to not write EmptyChunk
        level["xPos"] = static_cast<int32_t>(coords.x);
        level["zPos"] = static_cast<int32_t>(coords.z);
        level["LastUpdate"] = static_cast<int64_t>(0); // TODO
        level["TerrainPopulated"] = static_cast<int8_t>(true);

        // this is shit but nbt lib begs for vector
        std::vector<int8_t> blocks(CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH); // I didn't want to use vector but I guess I have to for nbt::tag_array
        std::vector<int8_t> data((CHUNK_WIDTH*CHUNK_HEIGHT * CHUNK_DEPTH) / 2);
        std::vector<int8_t> skyLight((CHUNK_WIDTH*CHUNK_HEIGHT*CHUNK_DEPTH) / 2);
        std::vector<int8_t> blockLight((CHUNK_WIDTH*CHUNK_HEIGHT*CHUNK_DEPTH) / 2);
        std::vector<int8_t> heightMap(CHUNK_WIDTH*CHUNK_DEPTH);
        // todo wiki says there's tileticks which is gonna be pain

        int8_t *blockData = blocks.data(); // avoid the annoying bounds checks and just write directly
        int8_t *dataData = data.data(); // welcome back 4J
        int8_t *skyLightData = skyLight.data();
        int8_t *blockLightData = blockLight.data();
        int8_t *heightMapData = heightMap.data();

        for (int cx = 0; cx < CHUNK_WIDTH; cx++) {
            for (int cz = 0; cz < CHUNK_DEPTH; cz++) {
                for (int cy = 0; cy < CHUNK_HEIGHT; cy++) {
                    const size_t idx = INDEX_XZY(cx, cy, cz, CHUNK_HEIGHT, CHUNK_DEPTH);
                    const level::block::properties::BlockProperties *b = c->getBlock(cx, cy, cz);
#ifdef USE_RISKY_OPTIMIZATIONS
                    if (b->getBlock() != level::block::BlockRegistry::sDefaultBlock) {
#endif
                        uint8_t id = 0;
                        uint8_t dat = 0;
                        if (b->getBlock() != level::block::BlockRegistry::sDefaultBlock) {
                            if (const lodestone::conversion::block::data::NumericBlockData *bl = bio->convertBlockFromInternal(b)->as<lodestone::conversion::block::data::NumericBlockData>()) {
                                id = bl->getId();
                                dat = bl->getData();
                            }
                        }

                        blockData[idx] = id;

                        SET_NIBBLE(dataData, idx, dat);
#ifdef USE_RISKY_OPTIMIZATIONS
                    }
#endif

                    // TODO we can readd lighting once we actually have support for it in our chunks
                    SET_NIBBLE(skyLightData, idx, 15); // TODO get/set methods in Section for lighting
                    SET_NIBBLE(blockLightData, idx, 15); // TODO get/set methods in Section for lighting
                }

                heightMapData[INDEX_YX(cx, cz, CHUNK_WIDTH)] = c->getHeightAt(cx, cz);
            }
        }

        level["Blocks"] = nbt::tag_byte_array(std::move(blocks));
        level["Data"] = nbt::tag_byte_array(std::move(data));
        level["SkyLight"] = nbt::tag_byte_array(std::move(skyLight));
        level["BlockLight"] = nbt::tag_byte_array(std::move(blockLight));
        level["HeightMap"] = nbt::tag_byte_array(std::move(heightMap));

        // TODO entities
        level["Entities"] = nbt::tag_list(); // TODO
        level["TileEntities"] = nbt::tag_list(); // TODO

        root["Level"] = std::move(level);

        return root;
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

    void McRegionChunkIO::write(lodestone::level::chunk::Chunk *c, const level::types::Vec2i &coords, const int version,
        std::ostream &out) const {
        nbt::io::stream_writer w = nbt::io::stream_writer(out, endian::big);

        w.write_tag("", write(c, coords, version));
    }
}
