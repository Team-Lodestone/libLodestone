//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/ImmutableChunk.h"

namespace lodestone::level::chunk {
    ImmutableChunk *ImmutableChunk::getInstance() {
        static ImmutableChunk s_instance;
        return &s_instance;
    }

    ChunkType ImmutableChunk::type() { return ChunkType::ImmutableChunk; }

    int ImmutableChunk::getChunkHeight() const { return 0; }

    section::Section *ImmutableChunk::getSection(const coords::SectionCoordinates &sectionY) const { return section::ImmutableSection::getInstance(); }

    const block::instance::BlockInstance &
    ImmutableChunk::getBlock(const int localX, const int y, const int localZ) const { return section::ImmutableSection::getInstance()->getBlock(localX, y, localZ); }

    section::Section *ImmutableChunk::getSectionCreate(const coords::SectionCoordinates &sectionY) { return section::ImmutableSection::getInstance(); }

    void ImmutableChunk::setBlock(block::instance::BlockInstance &&block, int localX, int y, int localZ) {}

    void ImmutableChunk::setBlockRaw(block::instance::BlockInstance &&block,
                                 int localX, int y, int localZ) {}

    void ImmutableChunk::setHeightAt(int16_t height, int localX, int localZ) {}

    void ImmutableChunk::calculateHeightmap() {}

    void ImmutableChunk::calculateHeightmapAtColumn(int localX, int localZ, int height) {}

    int ImmutableChunk::getSectionCount() const { return 0; }

    int16_t ImmutableChunk::getHeightAt(int localX, int localZ) const { return 0; }

    const block::instance::BlockInstance & ImmutableChunk::getBlockAtHeight(int localX, int localZ) const { return this->getBlock(0, 0, 0); }

    void ImmutableChunk::setBlockAtHeight(block::instance::BlockInstance &&block, int localX, int localZ) {}
} // namespace lodestone::level::chunk