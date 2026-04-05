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
        int64_t time = bis.readBE<int64_t>();
        int64_t isPopulated = bis.readBE<int64_t>();

        auto c = std::make_unique<InfdevChunk>(level::types::Vec2i(chunkX, chunkZ), time);

        // Skip over padding
        bis.seekRelative(232);

        const std::vector<uint8_t> blocks = bis.readOfSizeVec(32768);
        const std::vector<uint8_t> data = bis.readOfSizeVec(16384);
        const std::vector<uint8_t> skyLight = bis.readOfSizeVec(16384);
        const std::vector<uint8_t> blockLight = bis.readOfSizeVec(16384);

        const std::vector<uint8_t> heightMap = bis.readOfSizeVec(256);

        const std::unique_ptr<conversion::block::version::BlockIO> io = LodestoneJava::getInstance()->io.getIo(
            options.version);

        for (int cx = 0; cx < CHUNK_WIDTH; cx++) {
            for (int cz = 0; cz < CHUNK_DEPTH; cz++) {
                for (int cy = 0; cy < CHUNK_HEIGHT; cy++) {
                    const size_t idx =
                            INDEX_XZY(cx, cy, cz, InfdevChunkIO::CHUNK_HEIGHT, InfdevChunkIO::CHUNK_DEPTH);

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
                        c->InfdevChunk::setBlock(std::move(b), cx, cy, cz);

                    if (level::chunk::section::Section *s =
                            c->getSection(cy >> 4)) {
                        s->getBlockLight()->setNibble(
                            cx, cy & 15, cz, GET_NIBBLE(skyLight, idx));
                        s->getSkyLight()->setNibble(
                            cx, cy & 15, cz, GET_NIBBLE(blockLight, idx));
                    }
                }
            }
        }

        return c;
    }

    void InfdevChunkIO::write(level::chunk::Chunk *c,
                              const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions &options)
    const {
        bio::stream::BinaryOutputStream bos(options.output);

        const std::unique_ptr<conversion::block::version::BlockIO>
            bio = LodestoneJava::getInstance()->io.getIo(options.version);

        const level::types::Vec2i coords = c->getCoords().value();
        bos.writeBE<int32_t>(coords.x);
        bos.writeBE<int32_t>(coords.y); // Z

        // Write padding
        for (int i = 0; i < 232; i++) {
            bos.writeBE<int8_t>(0);
        }

        std::vector<int8_t> blocks(
    CHUNK_WIDTH * CHUNK_HEIGHT *
    CHUNK_DEPTH);
        std::vector<int8_t> data((CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH) /
                                 2);
        std::vector<int8_t> skyLight(
            (CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH) / 2);
        std::vector<int8_t> blockLight(
            (CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH) / 2);
        std::vector<int8_t> heightMap(CHUNK_WIDTH * CHUNK_DEPTH);
        // todo wiki says there's tileticks which is gonna be pain

        int8_t *blockData = blocks.data(); // avoid the annoying bounds checks
        // and just write directly
        int8_t *dataData = data.data();    // welcome back 4J
        int8_t *skyLightData = skyLight.data();
        int8_t *blockLightData = blockLight.data();
        int8_t *heightMapData = heightMap.data();

        for (int cx = 0; cx < CHUNK_WIDTH; cx++) {
            for (int cz = 0; cz < CHUNK_DEPTH; cz++) {
                for (int cy = 0; cy < CHUNK_HEIGHT; cy++) {
                    const size_t idx =
                        INDEX_XZY(cx, cy, cz, InfdevChunkIO::CHUNK_HEIGHT, InfdevChunkIO::CHUNK_DEPTH);
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

                        blockData[idx] = id;

                        SET_NIBBLE(dataData, idx, dat);
#ifdef USE_RISKY_OPTIMIZATIONS
                        }
#endif

                    level::chunk::section::Section *s = c->getSection(cy >> 4);

                    SET_NIBBLE(skyLightData, idx,
                               s ? s->getSkyLight()->getNibble(cx, cy & 15, cz)
                                 : 15);
                    SET_NIBBLE(
                        blockLightData, idx,
                        s ? s->getBlockLight()->getNibble(cx, cy & 15, cz)
                          : 15);
                }

                heightMapData[INDEX_YX(cx, cz, CHUNK_WIDTH)] =
                    c->getHeightAt(cx, cz);
            }

            bos.writeBytes(reinterpret_cast<uint8_t*>(blockData), 32768);
            bos.writeBytes(reinterpret_cast<uint8_t*>(dataData), 16384);
            bos.writeBytes(reinterpret_cast<uint8_t*>(skyLightData), 16384);
            bos.writeBytes(reinterpret_cast<uint8_t*>(blockLightData), 16384);
            bos.writeBytes(reinterpret_cast<uint8_t*>(heightMapData), 256);
        }
    }
}
