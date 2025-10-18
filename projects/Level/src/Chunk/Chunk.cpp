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

    const block::state::BlockState **Chunk::getBlockmap() const {
        return const_cast<const block::state::BlockState **>(mBlockmap);
    }

    int16_t Chunk::getHeightAt(const int x, const int z) const {
        return mHeightmap[z * constants::CHUNK_WIDTH + x];
    }

    void Chunk::setHeightAt(const int16_t h, const int x, const int z) {
        mHeightmap[z * constants::CHUNK_WIDTH + x] = h;
    }

    const block::state::BlockState *Chunk::getBlockmapBlockAt(const int x, const int z) const {
        return mBlockmap[z * constants::CHUNK_WIDTH + x];
    }

    void Chunk::setBlockmapBlockAt(block::state::BlockState *b, const int x, const int z) {
        mBlockmap[z * constants::CHUNK_WIDTH + x] = b;
    }
}
