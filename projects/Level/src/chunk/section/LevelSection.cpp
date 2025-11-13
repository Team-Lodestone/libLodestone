//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/section/LevelSection.h"
#include <Lodestone.Common/Indexing.h>

namespace lodestone::level::chunk::section {
    LevelSection::~LevelSection() {
        delete[] mSkyLight;
        delete[] mBlockLight;
        delete[] mBiomes;
        delete[] mBlocks;
    }

    const uint8_t *LevelSection::getBlockLight() const {
        return mBlockLight;
    }

    const uint8_t *LevelSection::getSkyLight() const {
        return mSkyLight;
    }

    block::state::BlockState *LevelSection::getBlock(const int x, const int y, const int z) const {
        return &mBlocks[INDEX_YZX(x, y, z, constants::CHUNK_WIDTH, constants::CHUNK_DEPTH)];
    }

    const block::state::BlockState *LevelSection::getBlocks() {
        return mBlocks;
    }

    Section::SectionType LevelSection::getType() {
        return SectionType::LevelSection;
    }

    void LevelSection::setBlock(block::state::BlockState &&blk, const int x, const int y, const int z) {
        mBlocks[INDEX_YZX(x, y, z, constants::CHUNK_WIDTH, constants::CHUNK_DEPTH)] = std::move(blk);
    }
}
