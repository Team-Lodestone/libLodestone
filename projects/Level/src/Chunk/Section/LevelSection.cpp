//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Chunk/Section/LevelSection.h"

namespace lodestone::level::chunk::section {
    block::state::BlockState * LevelSection::getBlock(const int x, const int y, const int z) const {
        return &mBlocks[INDEX_YZX(x, y, z, constants::CHUNK_WIDTH, constants::CHUNK_LENGTH)];
    }

    Section::SectionType LevelSection::getType() {
        return SectionType::LevelSection;
    }

    void LevelSection::setBlock(block::state::BlockState &blk, const int x, const int y, const int z) {
        mBlocks[INDEX_YZX(x, y, z, constants::CHUNK_WIDTH, constants::CHUNK_LENGTH)] = blk;
    }
}
