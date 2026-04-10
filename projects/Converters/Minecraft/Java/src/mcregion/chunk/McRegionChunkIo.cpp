//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/conversion/mcregion/McRegionChunkIo.h"

#include <Lodestone.Minecraft.Common/Identifiers.h>

#include <iostream>

#include "Lodestone.Minecraft.Java/LodestoneJava.h"
#include <Lodestone.Common/Indexing.h>
#include <Lodestone.Common/io/DataBuffer.h>
#include <Lodestone.Conversion/block/data/NumericBlockData.h>
#include <libnbt++/io/stream_reader.h>
#include <libnbt++/tag_array.h>
#include <libnbt++/tag_primitive.h>

#include "Lodestone.Minecraft.Java/mcregion/McRegionChunk.h"
#include <Lodestone.Common/Indexing.h>
#include <libnbt++/tag_list.h>

namespace lodestone::minecraft::java::mcregion::chunk {
    std::unique_ptr<level::chunk::Chunk>
    McRegionNbtChunkIO::read(const common::conversion::io::options::OptionPresets::CommonNbtReadOptions &options) const {
        const int32_t x = options.input["xPos"].get().as<nbt::tag_int>().get();
        const int32_t z = options.input["zPos"].get().as<nbt::tag_int>().get();
        const int64_t lastUpdate =
            options.input["LastUpdate"].get().as<nbt::tag_long>().get();
        const int8_t *blocks =
            options.input["Blocks"].get().as<nbt::tag_byte_array>().get().data();
        const int8_t *data =
            options.input["Data"].get().as<nbt::tag_byte_array>().get().data();

        const int8_t *skyLight =
            options.input["SkyLight"].get().as<nbt::tag_byte_array>().get().data();
        const int8_t *blockLight =
            options.input["BlockLight"].get().as<nbt::tag_byte_array>().get().data();

        std::unique_ptr<McRegionChunk> c = std::make_unique<McRegionChunk>(
            level::types::Vec2i(x, z), lastUpdate);

        const std::unique_ptr<lodestone::conversion::block::version::BlockIO>
            io = LodestoneJava::getInstance()->io.getIo(options.version);

        for (int cx = 0; cx < McRegionChunkIO::CHUNK_WIDTH; cx++) {
            for (int cz = 0; cz < McRegionChunkIO::CHUNK_DEPTH; cz++) {
                for (int cy = 0; cy < McRegionChunkIO::CHUNK_HEIGHT; cy++) {
                    const size_t idx =
                        INDEX_XZY(cx, cy, cz, McRegionChunkIO::CHUNK_HEIGHT, McRegionChunkIO::CHUNK_DEPTH);

                    const uint8_t bb = blocks[idx];

#ifdef USE_RISKY_OPTIMIZATIONS
                    if (bb == 0)  // since air is id 0
                        continue; // this skips us having to convert the block
#endif

                    const uint8_t d = GET_NIBBLE(data, idx);

                    level::block::instance::BlockInstance b =
                        io->convertBlockToInternal(
                            lodestone::conversion::block::data::
                                NumericBlockData(
                                    bb,
                                    0)); // TODO metadata (maybe MetadataIO or
                                         // BlockPropertyIO?)

                    if (b.getBlock() !=
                        level::block::BlockRegistry::s_defaultBlock)
                        c->McRegionChunk::setBlock(std::move(b), cx, cy, cz);

                    if (level::chunk::section::Section *s =
                            c->getSection(cy >> 4)) {
                        s->getBlockLightStorage()->setNibble(
                            cx, cy & 15, cz, GET_NIBBLE(skyLight, idx));
                        s->getSkyLightStorage()->setNibble(
                            cx, cy & 15, cz, GET_NIBBLE(blockLight, idx));
                    }
                }
            }
        }

        return c;
    }

    void McRegionNbtChunkIO::write(level::chunk::Chunk *c,const common::conversion::io::options::OptionPresets::NbtOutputWriteOptions<const common::conversion::io::options::OptionPresets::CommonChunkOptions> &options) const {
        nbt::tag_compound root{};
        nbt::tag_compound level{};

        const std::unique_ptr<lodestone::conversion::block::version::BlockIO>
            bio = LodestoneJava::getInstance()->io.getIo(options.version);

        // todo make sure to not write EmptyChunk
        level["xPos"] = static_cast<int32_t>(options.coords.x);
        level["zPos"] = static_cast<int32_t>(options.coords.y);
        level["LastUpdate"] = static_cast<int64_t>(0); // TODO
        level["TerrainPopulated"] = static_cast<int8_t>(true);

        // this is shit but nbt lib begs for vector
        std::vector<int8_t> blocks(
            McRegionChunkIO::CHUNK_WIDTH * McRegionChunkIO::CHUNK_HEIGHT *
            McRegionChunkIO::CHUNK_DEPTH); // I didn't want to use vector but I guess I have to
                          // for nbt::tag_array
        std::vector<int8_t> data((McRegionChunkIO::CHUNK_WIDTH * McRegionChunkIO::CHUNK_HEIGHT * McRegionChunkIO::CHUNK_DEPTH) /
                                 2);
        std::vector<int8_t> skyLight(
            (McRegionChunkIO::CHUNK_WIDTH * McRegionChunkIO::CHUNK_HEIGHT * McRegionChunkIO::CHUNK_DEPTH) / 2);
        std::vector<int8_t> blockLight(
            (McRegionChunkIO::CHUNK_WIDTH * McRegionChunkIO::CHUNK_HEIGHT * McRegionChunkIO::CHUNK_DEPTH) / 2);
        std::vector<int8_t> heightMap(McRegionChunkIO::CHUNK_WIDTH * McRegionChunkIO::CHUNK_DEPTH);
        // todo wiki says there's tileticks which is gonna be pain

        int8_t *blockData = blocks.data(); // avoid the annoying bounds checks
                                           // and just write directly
        int8_t *dataData = data.data();    // welcome back 4J
        int8_t *skyLightData = skyLight.data();
        int8_t *blockLightData = blockLight.data();
        int8_t *heightMapData = heightMap.data();

        for (int cx = 0; cx < McRegionChunkIO::CHUNK_WIDTH; cx++) {
            for (int cz = 0; cz < McRegionChunkIO::CHUNK_DEPTH; cz++) {
                for (int cy = 0; cy < McRegionChunkIO::CHUNK_HEIGHT; cy++) {
                    const size_t idx =
                        INDEX_XZY(cx, cy, cz, McRegionChunkIO::CHUNK_HEIGHT, McRegionChunkIO::CHUNK_DEPTH);
                    const level::block::instance::BlockInstance &b =
                        c->getBlock(cx, cy, cz);
#ifdef USE_RISKY_OPTIMIZATIONS
                    if (b.getBlock() !=
                        level::block::BlockRegistry::s_defaultBlock) {
#endif
                        uint8_t id = 0;
                        uint8_t dat = 0;

                        if (const lodestone::conversion::block::data::NumericBlockData *bl =
                                    bio->convertBlockFromInternal(&b)->as<lodestone::conversion::block::data::NumericBlockData>()) {
                            id = bl->getId();
                            dat = bl->getData();
                        }

                        blockData[idx] = id;

                        SET_NIBBLE(dataData, idx, dat);
#ifdef USE_RISKY_OPTIMIZATIONS
                    }
#endif

                    level::chunk::section::Section *s = c->getSection(cy >> 4);

                    SET_NIBBLE(skyLightData, idx,
                               s ? s->getSkyLightStorage()->getNibble(cx, cy & 15, cz)
                                 : 15);
                    SET_NIBBLE(
                        blockLightData, idx,
                        s ? s->getBlockLightStorage()->getNibble(cx, cy & 15, cz)
                          : 15);
                }

                heightMapData[INDEX_YX(cx, cz, McRegionChunkIO::CHUNK_WIDTH)] =
                    c->getHeightAt(cx, cz);
            }
        }

        level["Blocks"] = nbt::tag_byte_array(std::move(blocks));
        level["Data"] = nbt::tag_byte_array(std::move(data));
        level["SkyLight"] = nbt::tag_byte_array(std::move(skyLight));
        level["BlockLight"] = nbt::tag_byte_array(std::move(blockLight));
        level["HeightMap"] = nbt::tag_byte_array(std::move(heightMap));

        // TODO entities
        level["Entities"] = nbt::tag_list();     // TODO
        level["TileEntities"] = nbt::tag_list(); // TODO

        root["Level"] = std::move(level);

        options.output = root;
    }

    std::unique_ptr<level::chunk::Chunk>
    McRegionChunkIO::read(const common::conversion::io::options::OptionPresets::CommonReadOptions &options) const {
        nbt::io::stream_reader streamReader =
            nbt::io::stream_reader(options.input, endian::big);

        auto [name, root] = streamReader.read_compound();
        nbt::tag_compound &level =
            (root.get()->at("Level").as<nbt::tag_compound>());

        const McRegionNbtChunkIO *io = this->getAsByRelation<const McRegionNbtChunkIO, &identifiers::NBT_CHUNK_IO>();

        return io->read(common::conversion::io::options::OptionPresets::CommonNbtReadOptions {
            common::conversion::io::options::NbtReaderOptions {
                level
            },
            conversion::io::options::versioned::VersionedOptions {
                options.version
            }
        });
    }

    void McRegionChunkIO::write(level::chunk::Chunk *c, const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions &options) const {
        nbt::io::stream_writer w = nbt::io::stream_writer(options.output, endian::big);

        const McRegionNbtChunkIO *io = this->getAsByRelation<const McRegionNbtChunkIO, &identifiers::NBT_CHUNK_IO>();
        io->writeToNbtStreamWriter(c, "", w, common::conversion::io::options::OptionPresets::CommonChunkOptions {
            common::conversion::io::options::ChunkOptions {
                options.coords
            },
            conversion::io::options::versioned::VersionedOptions {
                options.version
            }
        });
    }
} // namespace lodestone::minecraft::java::mcregion::chunk
