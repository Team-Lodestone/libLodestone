//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/section/LevelSection.h"

#include <Lodestone.Common/Indexing.h>

namespace lodestone::level::chunk::section {
    LevelSection::~LevelSection() {
        delete[] mBiomes;
    }

    lodestone::common::storage::bits::AbstractBitsArray *LevelSection::getBlockLight() {
        return &mBlockLight;
    }

    lodestone::common::storage::bits::AbstractBitsArray *LevelSection::getSkyLight() {
        return &mSkyLight;
    }

    void LevelSection::setBlockLight(const int x, const int y, const int z,
                                     const uint8_t l) {
        this->mBlockLight.setNibble(x, y, z, l & 0xF);
    }

    void LevelSection::setSkyLight(const int x, const int y, const int z,
                                   const uint8_t l) {
        this->mSkyLight.setNibble(x, y, z, l & 0xF);
    }

    const block::properties::BlockProperties &
    LevelSection::getBlock(const int x, const int y, const int z) const {
        return mBlocks.getValue(INDEX_YZX(x, y, z, common::constants::CHUNK_WIDTH,
                                  common::constants::CHUNK_DEPTH));
    }

    const common::storage::palette::PalletizedStorage<block::properties::BlockProperties> &LevelSection::getStorage() {
        return mBlocks;
    }

    Section::SectionType LevelSection::getType() {
        return SectionType::LevelSection;
    }

    void LevelSection::setBlock(block::properties::BlockProperties &&blk,
                                const int x, const int y, const int z) {
        mBlocks.setValue(INDEX_YZX(x, y, z, common::constants::CHUNK_WIDTH,
                          common::constants::CHUNK_DEPTH), std::move(blk));
    }
} // namespace lodestone::level::chunk::section
