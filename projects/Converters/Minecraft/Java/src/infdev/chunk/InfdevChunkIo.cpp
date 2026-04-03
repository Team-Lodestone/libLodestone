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

#include "BinaryIO/stream/BinaryInputStream.h"
#include "Lodestone.Common/Indexing.h"
#include "Lodestone.Conversion/block/data/NumericBlockData.h"
#include "Lodestone.Minecraft.Java/LodestoneJava.h"
#include "Lodestone.Minecraft.Java/infdev/InfdevChunk.h"

#include "Lodestone.Minecraft.Java/Identifiers.h"

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
        throw std::runtime_error("Not implemented");
    }
}
