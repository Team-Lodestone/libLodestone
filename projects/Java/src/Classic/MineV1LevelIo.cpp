//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Classic/MineV1LevelIo.h"

#include "Classic/ClassicBlockIo.h"

namespace lodestone::java::classic {
    level::Level * MineV1LevelIO::read(uint8_t *data) const {
        level::Level *l = new level::Level();

        for (int w = 0; w < WIDTH / constants::CHUNK_WIDTH; w++) {
            for (int d = 0; d < LENGTH / constants::CHUNK_LENGTH; d++) {
                l->createChunk(w, d , 64);
            }
        }

        const size_t m = getSize();
        const uint8_t* mm = data + m;
        while (data < mm) {
            for (int x = 0; x < WIDTH; x++) {
                for (int y = 0; y < HEIGHT; y++) {
                    for (int z = 0; z < LENGTH; z++) {
                        level::block::state::BlockState b = ClassicBlockIO::sInstance->readBlock(data);
                        l->setBlock(b, x, y, z);

                        data++;
                    }
                }
            }
        }

        return l;
    }

    uint8_t * MineV1LevelIO::write(level::Level *l) const {
        uint8_t *d = new uint8_t[getSize()];
        uint8_t *dp = d;

        const uint8_t* mm = dp + getSize();
        while (dp < mm) {
            for (int x = 0; x < WIDTH; x++) {
                for (int y = 0; y < HEIGHT; y++) {
                    for (int z = 0; z < LENGTH; z++) {
                        ClassicBlockIO::sInstance->writeBlock(l->getBlock(x, y, z), dp);

                        dp++;
                    }
                }
            }
        }

        return d;
    }

    size_t MineV1LevelIO::getSize() const {
        return WIDTH * HEIGHT * LENGTH;
    }
}
