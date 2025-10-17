//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Classic/MineV1/MineV1LevelIo.h"

#include "Classic/ClassicBlockIo.h"

namespace lodestone::java::classic::minev1 {
    level::Level * MineV1LevelIO::read(uint8_t *data) const {
        level::Level *l = new level::Level();

        for (int y = 0; y < HEIGHT; y++) {
            for (int z = 0; z < DEPTH; z++) {
                for (int x = 0; x < WIDTH; x++) {
                    level::block::state::BlockState b = ClassicBlockIO::sInstance->readBlock(data);
                    if (b.getBlock()->getID() != "lodestone:air")
                        l->setBlockCreateRaw(b, x, y, z, HEIGHT);

                    data++;
                }
            }
        }

        for (auto [coords, chunk] : l->getChunks())
            chunk->calculateHeightmap();

        return l;
    }

    uint8_t * MineV1LevelIO::write(level::Level *l) const {
        uint8_t *d = new uint8_t[getSize(l)];
        uint8_t *dp = d;

        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                for (int z = 0; z < DEPTH; z++) {
                    level::block::state::BlockState *b = l->getBlock(x, y, z);
                    if (b->getBlock()->getID() != "lodestone:air")
                        ClassicBlockIO::sInstance->writeBlock(b, dp);

                    dp++;
                }
            }
        }

        return d;
    }

    size_t MineV1LevelIO::getSize(level::Level *l) const {
        return WIDTH * HEIGHT * DEPTH;
    }
}
