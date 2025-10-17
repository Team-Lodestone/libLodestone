//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Chunk/Chunk.h"

namespace lodestone::level::chunk {
    int Chunk::getChunkBlockHeight() const {
        return getChunkHeight() * constants::SECTION_HEIGHT;
    }

    const int16_t *Chunk::getHeightmap() const {
        return mHeightmap;
    }

    int16_t Chunk::getHeightAt(const int x, const int z) const {
        return mHeightmap[z * constants::CHUNK_WIDTH + x];
    }

    void Chunk::setHeightAt(const int x, const int z, const int16_t h) {
        mHeightmap[z * constants::CHUNK_WIDTH + x] = h;
    }
}
