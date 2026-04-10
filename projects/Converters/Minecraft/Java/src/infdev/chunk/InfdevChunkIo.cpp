/** @file InfdevChunkIo.cpp
*
* @author Zero_DSRS_VX
* @date 3/29/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#include "Lodestone.Minecraft.Java/conversion/infdev/InfdevChunkIo.h"

#include <BinaryIO/stream/BinaryInputStream.h>
#include <Lodestone.Common/Indexing.h>
#include <Lodestone.Conversion/block/data/NumericBlockData.h>

#include <BinaryIO/stream/BinaryOutputStream.h>
#include "Lodestone.Minecraft.Java/LodestoneJava.h"
#include "Lodestone.Minecraft.Java/infdev/InfdevChunk.h"

namespace lodestone::minecraft::java::infdev::chunk {
    std::unique_ptr<level::chunk::Chunk> InfdevChunkIO::read(
        const common::conversion::io::options::OptionPresets::CommonReadOptions &options) const {
        bio::stream::BinaryInputStream bis(options.input);

        // 256 byte entry
        const int32_t chunkX = bis.readBE<int32_t>();
        const int32_t chunkZ = bis.readBE<int32_t>();
        const int64_t time = bis.readBE<int64_t>();
        const std::unique_ptr<Properties> properties = bis.deserialize<Properties::Deserializer>();

        auto c = std::make_unique<InfdevChunk>(level::types::Vec2i(chunkX, chunkZ), time, properties->terrainPopulated);

        // Skip over padding
        bis.seekRelative(232);

        const std::vector<uint8_t> blocks = bis.readOfSizeVec(InfdevChunk::CHUNK_TOTAL_BLOCKS);
        const std::vector<uint8_t> data = bis.readOfSizeVec(InfdevChunk::CHUNK_LAYER_SIZE);
        const std::vector<uint8_t> skyLight = bis.readOfSizeVec(InfdevChunk::CHUNK_LAYER_SIZE);
        const std::vector<uint8_t> blockLight = bis.readOfSizeVec(InfdevChunk::CHUNK_LAYER_SIZE);

        const std::vector<uint8_t> heightMap = bis.readOfSizeVec(InfdevChunk::CHUNK_HEIGHTMAP_SIZE);

        const std::unique_ptr<conversion::block::version::BlockIO> io = LodestoneJava::getInstance()->io.getIo(
            options.version);

        for (int cx = 0; cx < InfdevChunk::CHUNK_WIDTH; cx++) {
            for (int cz = 0; cz < InfdevChunk::CHUNK_DEPTH; cz++) {
                for (int cy = 0; cy < InfdevChunk::CHUNK_HEIGHT; cy++) {
                    const size_t idx =
                        INDEX_XZY(cx, cy, cz, InfdevChunk::CHUNK_HEIGHT, InfdevChunk::CHUNK_DEPTH);

                    const uint8_t bb = blocks[idx];

#ifdef USE_RISKY_OPTIMIZATIONS
                    if (bb == 0) // since air is id 0
                        continue; // this skips us having to convert the block
#endif

                    const uint8_t d = GET_NIBBLE(data, idx);

                    level::block::instance::BlockInstance b =
                        io->convertBlockToInternal(
                            conversion::block::data::
                            NumericBlockData(
                                bb,
                                0));

                    if (b.getBlock() !=
                        level::block::BlockRegistry::s_defaultBlock)
                        c->InfdevChunk::setBlockRaw(std::move(b), cx, cy, cz);

                    if (level::chunk::section::Section *s =
                        c->getSection(level::coords::SectionCoordinates::blockToSectionCoord(cy))) {
                        // TODO: Metadata
                        s->getBlockLightStorage()->setNibble(
                            cx, cy & 15, cz, GET_NIBBLE(skyLight, idx));
                        s->getSkyLightStorage()->setNibble(
                            cx, cy & 15, cz, GET_NIBBLE(blockLight, idx));
                    }
                }
            }
        }

        c->postProcess();

        return c;
    }

    void InfdevChunkIO::write(level::chunk::Chunk *c,
                              const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions &options)
    const {
        bio::stream::BinaryOutputStream bos(options.output);

        const std::unique_ptr<conversion::block::version::BlockIO>
            bio = LodestoneJava::getInstance()->io.getIo(options.version);

        const level::coords::ChunkCoordinates coords = c->getCoords().value();
        bos.writeBE<int32_t>(coords.getX());
        bos.writeBE<int32_t>(coords.getZ()); // Z

        bos.writeBE<int64_t>(c->getPropertyOr<int64_t>("inhabitedTime", 0L)->getValue());
        bos.serialize<Properties::Serializer>({
            .terrainPopulated = c->getPropertyOr<bool>("terrainPopulated", true)->getValue()
        });

        // Write padding
        for (int i = 0; i < 232; i++) {
            bos.writeBE<int8_t>(0);
        }

        std::vector<int8_t> blocks(InfdevChunk::CHUNK_TOTAL_BLOCKS);
        std::vector<int8_t> data(InfdevChunk::CHUNK_LAYER_SIZE);
        std::vector<int8_t> skyLight(InfdevChunk::CHUNK_LAYER_SIZE);
        std::vector<int8_t> blockLight(InfdevChunk::CHUNK_LAYER_SIZE);
        std::vector<int8_t> heightMap(InfdevChunk::CHUNK_WIDTH * InfdevChunk::CHUNK_DEPTH);

        for (int cx = 0; cx < InfdevChunk::CHUNK_WIDTH; cx++) {
            for (int cz = 0; cz < InfdevChunk::CHUNK_DEPTH; cz++) {
                for (int cy = 0; cy < InfdevChunk::CHUNK_HEIGHT; cy++) {
                    const size_t idx =
                        INDEX_XZY(cx, cy, cz, InfdevChunk::CHUNK_HEIGHT, InfdevChunk::CHUNK_DEPTH);
                    const level::block::instance::BlockInstance &b =
                        c->getBlock(cx, cy, cz);
#ifdef USE_RISKY_OPTIMIZATIONS
                    if (b.getBlock() !=
                        level::block::BlockRegistry::s_defaultBlock) {
#endif
                        uint8_t id = 0;
                        uint8_t dat = 0;

                        if (const conversion::block::data::NumericBlockData *bl =
                            bio->convertBlockFromInternal(&b)->as<conversion::block::data::NumericBlockData>()) {
                            id = bl->getId();
                            dat = bl->getData();
                        }

                        blocks[idx] = id;

                        SET_NIBBLE(data, idx, dat);
#ifdef USE_RISKY_OPTIMIZATIONS
                    }
#endif

                    level::chunk::section::Section *s = c->getSection(cy >> 4);

                    SET_NIBBLE(skyLight, idx,
                               s ? s->getSkyLightStorage()->getNibble(cx, cy & 15, cz)
                               : 15);
                    SET_NIBBLE(
                        blockLight, idx,
                        s ? s->getBlockLightStorage()->getNibble(cx, cy & 15, cz)
                        : 15);
                }

                heightMap[INDEX_YX(cx, cz, InfdevChunk::CHUNK_WIDTH)] =
                    c->getHeightAt(cx, cz);
            }
        }

        bos.writeBytes(reinterpret_cast<uint8_t *>(blocks.data()), blocks.size());
        bos.writeBytes(reinterpret_cast<uint8_t *>(data.data()), data.size());
        bos.writeBytes(reinterpret_cast<uint8_t *>(skyLight.data()), skyLight.size());
        bos.writeBytes(reinterpret_cast<uint8_t *>(blockLight.data()), blockLight.size());
        bos.writeBytes(reinterpret_cast<uint8_t *>(heightMap.data()), heightMap.size());
    }
}