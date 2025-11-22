//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Lodestone.Java/classic/minev1/MineV1LevelIO.h"

#include <ranges>

#include "Lodestone.Java/LodestoneJava.h"
#include "Lodestone.Level/FiniteLevel.h"
#include <Lodestone.Common/Indexing.h>
#include <Lodestone.Conversion/block/BlockIO.h>
#include <Lodestone.Conversion/block/data/ClassicBlockData.h>

#include <BinaryIO/stream/BinaryInputStream.h>
#include <BinaryIO/stream/BinaryOutputStream.h>

namespace lodestone::java::classic::minev1 {

    size_t MineV1LevelIO::getSize(level::Level *l, int version) const {
        return WIDTH * HEIGHT * DEPTH;
    }

    std::unique_ptr<lodestone::level::Level>
    MineV1LevelIO::read(std::istream &in, const int version) const {
        bio::stream::BinaryInputStream bis(in);

        std::unique_ptr<level::FiniteLevel> l =
            std::make_unique<level::FiniteLevel>(level::types::Bounds2i{
                {0, 0}, {CHUNK_IDX(WIDTH) - 1, CHUNK_IDX(DEPTH) - 1}});

        const std::unique_ptr<lodestone::conversion::block::version::BlockIO>
            io = LodestoneJava::getInstance()->io.getIo(version);

        for (int y = 0; y < HEIGHT; y++) {
            for (int z = 0; z < DEPTH; z++) {
                for (int x = 0; x < WIDTH; x++) {
                    const uint8_t bb = bis.readByte();

#ifdef USE_RISKY_OPTIMIZATIONS
                    if (bb == 0)  // since air is id 0
                        continue; // this skips us having to convert the block
#endif

                    level::block::properties::BlockProperties b =
                        io->convertBlockToInternal(
                            lodestone::conversion::block::data::
                                ClassicBlockData(bb));

                    if (b.getBlock() !=
                        level::block::BlockRegistry::sDefaultBlock)
                        l->setBlockCreate(std::move(b), x, y, z, HEIGHT);
                }
            }
        }

        return l;
    }

    void MineV1LevelIO::write(lodestone::level::Level *l, const int version,
                              std::ostream &out) const {
        bio::stream::BinaryOutputStream bos(out);

        const std::unique_ptr<lodestone::conversion::block::version::BlockIO>
            io = LodestoneJava::getInstance()->io.getIo(version);

        for (int y = 0; y < HEIGHT; y++) {
            for (int z = 0; z < DEPTH; z++) {
                for (int x = 0; x < WIDTH; x++) {
                    const level::block::properties::BlockProperties *b =
                        l->getBlock(x, y, z);

                    uint8_t v = 0;
                    if (b->getBlock() !=
                        level::block::BlockRegistry::sDefaultBlock) {
                        const lodestone::conversion::block::data::
                            AbstractBlockData *bd =
                                io->convertBlockFromInternal(b);
                        v = (bd->as<lodestone::conversion::block::data::
                                        ClassicBlockData>())
                                ->getId();
                    }

                    bos << v;
                }
            }
        }
    }
} // namespace lodestone::java::classic::minev1