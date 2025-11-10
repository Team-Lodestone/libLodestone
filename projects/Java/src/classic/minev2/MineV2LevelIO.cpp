//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#include "classic/minev2/MineV2LevelIO.h"

#include <ranges>
#include <BinaryIO/BinaryIO.h>

#include "LodestoneJava.h"
#include "classic/minev1/MineV1LevelIO.h"
#include "Lodestone.Level/FiniteLevel.h"
#include "Lodestone.Level/Indexing.h"
#include "Lodestone.Level/conversion/block/BlockIO.h"
#include "Lodestone.Level/conversion/block/data/ClassicBlockData.h"

namespace lodestone::java::classic::minev2 {
    level::Level * MineV2LevelIO::read(uint8_t *data, int version) const {
        bio::BinaryIO io(data);

        const int width = io.readBE<uint16_t>();
        const int depth = io.readBE<uint16_t>();
        const int height = io.readBE<uint16_t>();

        level::FiniteLevel *l = new level::FiniteLevel(
            {
                {0, 0},
                {
                    BLOCK_IDX_TO_CHUNK_IDX(width) - 1,
                    BLOCK_IDX_TO_CHUNK_IDX(depth) - 1
                }
            });

        uint8_t *rd = io.getDataRelative();
        for (int y = 0; y < height; y++) {
            for (int z = 0; z < depth; z++) {
                for (int x = 0; x < width; x++) {
                    // level::block::state::BlockState b = ClassicBlockIO::sInstance->readBlock(rd);
                    // if (b.getBlock() != level::block::BlockRegistry::sDefaultBlock)
                        // l->setBlockCreateRaw(b, x, y, z, height);

                    rd++;
                }
            }
        }

        for (auto &chunk: l->getChunks() | std::views::values)
            chunk->calculateMaps();

        return l;
    }

     void MineV2LevelIO::write(level::Level *l, uint8_t *out, const int version) const {
        bio::BinaryIO io(out);
        const std::unique_ptr<level::conversion::block::version::BlockIO> bio = LodestoneJava::getInstance()->io.getIo(version);

        auto [min, max] = l->getBlockBounds();

        const int w = (max.x - min.x + 1);
        const int h = (max.y - min.y);
        const int d = (max.z - min.z + 1);

        // TODO if there's a singular chunk at a far away distance it will never be written since we normalize the values to the size and read from the center of the world

        io.writeBE<uint16_t>(w);
        io.writeBE<uint16_t>(d);
        io.writeBE<uint16_t>(h);

        uint8_t *blocks = io.getDataRelative();
        for (int y = 0; y < h; y++) {
            for (int z = 0; z < d; z++) {
                for (int x = 0; x < w; x++) {
                    level::block::state::BlockState *b = l->getBlock(x + min.x, y + min.y, z + min.z);
                    if (b->getBlock() != level::block::BlockRegistry::sDefaultBlock) {
                        level::conversion::block::data::AbstractBlockData *bl = bio->convertBlockFromInternal(b);
                        if (!bl)
                            blocks[INDEX_YZX(x, y, z, w, d)] = 0;
                        else
                            blocks[INDEX_YZX(x, y, z, w, d)] = bl->as<level::conversion::block::data::ClassicBlockData>()->getId();
                    }

                    // io.seekRelative(1); // TODO: I can make this operator++
                }
            }
        }
    }

    uint8_t * MineV2LevelIO::write(level::Level *l, const int version) const {
        uint8_t *d = new uint8_t[getSize(l, version)]{};
        write(l, d, version);

        return d;
    }

    size_t MineV2LevelIO::getSize(level::Level *l, int version) const {
        return 2 + 2 + 2 + l->getBlockCount();
    }
}
