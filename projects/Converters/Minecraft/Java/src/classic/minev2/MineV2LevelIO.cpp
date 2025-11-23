//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/classic/minev2/MineV2LevelIO.h"

#include <ranges>

#include "Lodestone.Minecraft.Java/LodestoneJava.h"
#include "Lodestone.Level/FiniteLevel.h"
#include <Lodestone.Common/Indexing.h>
#include <Lodestone.Conversion/block/BlockIO.h>
#include <Lodestone.Conversion/block/data/ClassicBlockData.h>

#include <BinaryIO/stream/BinaryInputStream.h>
#include <BinaryIO/stream/BinaryOutputStream.h>

#include <Lodestone.Common/util/Math.h>

namespace lodestone::minecraft::java::classic::minev2 {

    size_t MineV2LevelIO::getSize(level::Level *l, int version) const {
        return 2 + 2 + 2 + l->getBlockCount();
    }

    std::unique_ptr<lodestone::level::Level>
    MineV2LevelIO::read(std::istream &in, const int version) const {
        bio::stream::BinaryInputStream bis(in);

        const int width = bis.readBE<uint16_t>();
        const int depth = bis.readBE<uint16_t>();
        const int height = bis.readBE<uint16_t>();

        std::unique_ptr<level::FiniteLevel> l =
            std::make_unique<level::FiniteLevel>(level::types::Bounds2i{
                {0, 0},
                {common::util::Math::ceilDiv(CHUNK_IDX(width) - 1,
                                       common::constants::CHUNK_WIDTH),
                 common::util::Math::ceilDiv(CHUNK_IDX(depth) - 1,
                                       common::constants::CHUNK_DEPTH)}});

        const std::unique_ptr<lodestone::conversion::block::version::BlockIO>
            bio = LodestoneJava::getInstance()->io.getIo(version);

        for (int y = 0; y < height; y++) {
            for (int z = 0; z < depth; z++) {
                for (int x = 0; x < width; x++) {
                    const uint8_t bb = bis.readByte();

#ifdef USE_RISKY_OPTIMIZATIONS
                    if (bb == 0)  // since air is id 0
                        continue; // this skips us having to convert the block
#endif

                    level::block::properties::BlockProperties b =
                        bio->convertBlockToInternal(
                            lodestone::conversion::block::data::
                                ClassicBlockData(bb));
                    if (b.getBlock() !=
                        level::block::BlockRegistry::sDefaultBlock)
                        l->setBlockCreate(std::move(b), x, y, z, height);
                }
            }
        }

        return l;
    }

    void MineV2LevelIO::write(lodestone::level::Level *l, const int version,
                              std::ostream &out) const {
        bio::stream::BinaryOutputStream bos(out);
        const std::unique_ptr<lodestone::conversion::block::version::BlockIO>
            bio = LodestoneJava::getInstance()->io.getIo(version);

        auto [min, max] = l->getBlockBounds();

        const int w = (max.x - min.x + 1);
        const int h = (max.y - min.y);
        const int d = (max.z - min.z + 1);

        bos.writeBE<uint16_t>(w);
        bos.writeBE<uint16_t>(d);
        bos.writeBE<uint16_t>(h);

        for (int y = 0; y < h; y++) {
            for (int z = 0; z < d; z++) {
                for (int x = 0; x < w; x++) {
                    const level::block::properties::BlockProperties *b =
                        l->getBlock(x + min.x, y + min.y, z + min.z);

                    uint8_t v = 0;
                    if (b->getBlock() !=
                        level::block::BlockRegistry::sDefaultBlock) {
                        if (const lodestone::conversion::block::data::
                                AbstractBlockData *bl =
                                    bio->convertBlockFromInternal(b))
                            v = bl->as<lodestone::conversion::block::data::
                                           ClassicBlockData>()
                                    ->getId();
                    }

                    bos << v;
                }
            }
        }
    }
} // namespace lodestone::minecraft::java::classic::minev2
