//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Lodestone.Java/classic/minev1/MineV1LevelIO.h"

#include <ranges>

#include "Lodestone.Java/LodestoneJava.h"
#include "Lodestone.Level/FiniteLevel.h"
#include <Lodestone.Common/Indexing.h>
#include "Lodestone.Level/conversion/block/BlockIO.h"
#include "Lodestone.Level/conversion/block/data/ClassicBlockData.h"

namespace lodestone::java::classic::minev1 {
    std::unique_ptr<level::Level> MineV1LevelIO::read(uint8_t *data, const int version) const {
        std::unique_ptr<level::FiniteLevel> l = std::make_unique<level::FiniteLevel>(
            level::types::Bounds2i {
                {
                    0,
                    0
                },
                {
                    BLOCK_IDX_TO_CHUNK_IDX(WIDTH) - 1,
                    BLOCK_IDX_TO_CHUNK_IDX(DEPTH) - 1
                }
            }
        );

        const std::unique_ptr<level::conversion::block::version::BlockIO> io = LodestoneJava::getInstance()->io.
                getIo(version);

        for (int y = 0; y < HEIGHT; y++) {
            for (int z = 0; z < DEPTH; z++) {
                for (int x = 0; x < WIDTH; x++) {
                    level::block::state::BlockState b = io->convertBlockToInternal(
                        level::conversion::block::data::ClassicBlockData(*data));
                    if (b.getBlock() != level::block::BlockRegistry::sDefaultBlock)
                        l->setBlockCreate(std::move(b), x, y, z, HEIGHT);

                    data++;
                }
            }
        }

        return l;
    }

    uint8_t *MineV1LevelIO::write(level::Level *l, const int version) const {
        uint8_t *d = new uint8_t[getSize(l, version)]{};
        write(l, d, version);

        return d;
    }

    void MineV1LevelIO::write(level::Level *l, uint8_t *out, const int version) const {
        const std::unique_ptr<level::conversion::block::version::BlockIO> io = LodestoneJava::getInstance()->io.
                getIo(version);

        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                for (int z = 0; z < DEPTH; z++) {
                    const level::block::state::BlockState *b = l->getBlock(x, y, z);
                    if (b->getBlock() != level::block::BlockRegistry::sDefaultBlock) {
                        const level::conversion::block::data::AbstractBlockData *bd = io->convertBlockFromInternal(b);
                        out[INDEX_YZX(x, y, z, WIDTH, DEPTH)] = (bd->as<
                            level::conversion::block::data::ClassicBlockData>())->getId();
                    }
                }
            }
        }
    }

    size_t MineV1LevelIO::getSize(level::Level *l, int version) const {
        return WIDTH * HEIGHT * DEPTH;
    }
}