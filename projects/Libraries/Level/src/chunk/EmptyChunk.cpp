//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/ImmutableChunk.h"

namespace lodestone::level::chunk {
    ImmutableChunk *ImmutableChunk::getInstance() {
        static ImmutableChunk sInstance;
        return &sInstance;
    }

    void ImmutableChunk::calculateHeightmap() {}

    int ImmutableChunk::getChunkHeight() const { return 0; }

    section::Section *ImmutableChunk::getSection(int y) const {
        return section::ImmutableSection::getInstance();
    }

    const block::properties::BlockProperties &
    ImmutableChunk::getBlock(const int x, const int y, const int z) const {
        return section::ImmutableSection::getInstance()->getBlock(x, y, z);
    }

    section::Section *ImmutableChunk::getSectionCreate(int y) {
        return section::ImmutableSection::getInstance();
    }

    void ImmutableChunk::setBlock(block::properties::BlockProperties &&blk, int x,
                              int y, int z) {}

    void ImmutableChunk::setBlockRaw(block::properties::BlockProperties &&blk,
                                 int x, int y, int z) {}

    void ImmutableChunk::setHeightAt(int16_t h, int x, int z) {}

    void ImmutableChunk::calculateBlockmap() {}

    void ImmutableChunk::setBlockmapBlockAt(const block::properties::BlockProperties &h,
                                        int x, int z) {}

    void ImmutableChunk::calculateMaps() {}

    void ImmutableChunk::calculateBlockmapAtColumn(int x, int z, int height) {}

    void ImmutableChunk::calculateHeightmapAtColumn(int x, int z, int height) {}

    void ImmutableChunk::calculateMapsAtColumn(int x, int z, int height) {}
} // namespace lodestone::level::chunk