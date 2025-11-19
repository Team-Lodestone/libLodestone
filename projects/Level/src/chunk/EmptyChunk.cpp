//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/EmptyChunk.h"

namespace lodestone::level::chunk {
    EmptyChunk *EmptyChunk::getInstance() {
        static EmptyChunk sInstance;
        return &sInstance;
    }

    void EmptyChunk::calculateHeightmap() {
    }

    int EmptyChunk::getChunkHeight() const {
        return 0;
    }

    section::Section *EmptyChunk::getSection(int y) const {
        return section::EmptySection::getInstance();
    }

    block::properties::BlockProperties *EmptyChunk::getBlock(const int x, const int y, const int z) const {
        return section::EmptySection::getInstance()->getBlock(x, y, z);
    }

    section::Section *EmptyChunk::getSectionCreate(int y) {
        return section::EmptySection::getInstance();
    }

    void EmptyChunk::setBlock(block::properties::BlockProperties &&blk, int x, int y, int z) {
    }

    void EmptyChunk::setBlockRaw(block::properties::BlockProperties &&blk, int x, int y, int z) {
    }

    void EmptyChunk::setHeightAt(int16_t h, int x, int z) {
    }

    void EmptyChunk::calculateBlockmap() {
    }

    void EmptyChunk::setBlockmapBlockAt(block::properties::BlockProperties *h, int x, int z) {
    }

    void EmptyChunk::calculateMaps() {
    }

    void EmptyChunk::calculateBlockmapAtColumn(int x, int z, int height) {
    }

    void EmptyChunk::calculateHeightmapAtColumn(int x, int z, int height) {
    }

    void EmptyChunk::calculateMapsAtColumn(int x, int z, int height) {
    }
}