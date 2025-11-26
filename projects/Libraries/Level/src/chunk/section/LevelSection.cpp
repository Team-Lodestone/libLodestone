//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/section/LevelSection.h"

#include <Lodestone.Common/Indexing.h>

namespace lodestone::level::chunk::section {
    LevelSection::LevelSection() {}

    LevelSection::~LevelSection() {
        delete[] mBiomes;
        delete[] mBlocks;
    }

    types::NibbleArray LevelSection::getBlockLight() const {
        return mBlockLight;
    }

    types::NibbleArray LevelSection::getSkyLight() const { return mSkyLight; }

    block::properties::BlockProperties *
    LevelSection::getBlock(const int x, const int y, const int z) const {
        return &mBlocks[INDEX_YZX(x, y, z, common::constants::CHUNK_WIDTH,
                                  common::constants::CHUNK_DEPTH)];
    }

    const block::properties::BlockProperties *LevelSection::getBlocks() {
        return mBlocks;
    }

    Section::SectionType LevelSection::getType() {
        return SectionType::LevelSection;
    }

    void LevelSection::setBlock(block::properties::BlockProperties &&blk,
                                const int x, const int y, const int z) {
        mBlocks[INDEX_YZX(x, y, z, common::constants::CHUNK_WIDTH,
                          common::constants::CHUNK_DEPTH)] = std::move(blk);
    }
} // namespace lodestone::level::chunk::section
