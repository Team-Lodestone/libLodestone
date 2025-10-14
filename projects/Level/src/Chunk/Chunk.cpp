//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "../../include/Chunk/Chunk.h"

namespace lodestone::level::chunk {
    Chunk::Chunk(const int height) {
        this->mSections = std::vector<Section>(height % 16);
    }

    const int16_t * Chunk::generateHeightmap() {
        const int16_t *heightmap = new int16_t[CHUNK_WIDTH * CHUNK_LENGTH];

        for (int z = 0; z < CHUNK_LENGTH; z++) {
            for (int x = 0; x < CHUNK_WIDTH; x++) {
                for (int y = getHeight(); y > 0; y--) {
                    // TODO: port
                    // let blk = self.get_block(x, y, z);
                    // if blk != Block::Air {
                    //     heightmap[z as usize * CHUNK_WIDTH as usize + x as usize] =
                    //         (y + 1).min(self.height - 1);
                    //     break;
                    // }
                }
            }
        }

        return heightmap;
    }
}
