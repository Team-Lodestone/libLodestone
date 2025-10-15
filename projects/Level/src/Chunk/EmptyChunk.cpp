//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Chunk/EmptyChunk.h"

namespace lodestone::level::chunk {
    const int16_t * EmptyChunk::calculateHeightmap() {
        return mHeightmap;
    }

    int EmptyChunk::getHeight() const {
        return 0;
    }

    section::Section * EmptyChunk::getSection(int y) const {
        return section::EmptySection::sInstance;
    }

    block::state::BlockState * EmptyChunk::getBlock(const int x, const int y, const int z) const {
        return section::EmptySection::sInstance->getBlock(x, y, z);
    }
}
