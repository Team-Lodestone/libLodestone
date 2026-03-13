//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/ImmutableChunk.h"

namespace lodestone::level::chunk {
    ImmutableChunk *ImmutableChunk::getInstance() {
        static ImmutableChunk s_instance;
        return &s_instance;
    }

    int ImmutableChunk::getChunkHeight() const { return 0; }

    section::Section *ImmutableChunk::getSection(int y) const {
        return section::ImmutableSection::getInstance();
    }

    const block::instance::BlockInstance &
    ImmutableChunk::getBlock(const int x, const int y, const int z) const {
        return section::ImmutableSection::getInstance()->getBlock(x, y, z);
    }

    section::Section *ImmutableChunk::getSectionCreate(int y) {
        return section::ImmutableSection::getInstance();
    }

    void ImmutableChunk::setBlock(block::instance::BlockInstance &&blk, int x,
                              int y, int z) {}

    void ImmutableChunk::setBlockRaw(block::instance::BlockInstance &&blk,
                                 int x, int y, int z) {}

    void ImmutableChunk::setHeightAt(int16_t h, int x, int z) {}

    void ImmutableChunk::calculateBlockmap() {}

    void ImmutableChunk::setBlockmapBlockAt(const block::instance::BlockInstance *h,
                                        int x, int z) {}

    void ImmutableChunk::setBlockmapEntryAt(const BlockmapEntry &b, int x,
        int z) {}

    void ImmutableChunk::calculateBlockmapAtColumn(int x, int z, int height) {}

    int ImmutableChunk::getSectionCount() const {
        return 0;
    }
} // namespace lodestone::level::chunk