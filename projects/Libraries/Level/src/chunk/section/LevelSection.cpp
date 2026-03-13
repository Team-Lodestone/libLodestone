//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/section/LevelSection.h"

#include <Lodestone.Common/Indexing.h>

namespace lodestone::level::chunk::section {
    LevelSection::~LevelSection() {
        delete[] m_biomes;
    }

    lodestone::common::storage::bits::AbstractBitStorage *LevelSection::getBlockLight() {
        return &m_blockLight;
    }

    lodestone::common::storage::bits::AbstractBitStorage *LevelSection::getSkyLight() {
        return &m_skyLight;
    }

    void LevelSection::setBlockLight(const int x, const int y, const int z,
                                     const uint8_t l) {
        this->m_blockLight.setNibble(x, y, z, l & 0xF);

        m_modificationCount++;
    }

    void LevelSection::setSkyLight(const int x, const int y, const int z,
                                   const uint8_t l) {
        this->m_skyLight.setNibble(x, y, z, l & 0xF);

        m_modificationCount++;
    }

    const block::instance::BlockInstance &
    LevelSection::getBlock(const int x, const int y, const int z) const {
        return m_blocks.getValue(INDEX_YZX(x, y, z, common::constants::CHUNK_WIDTH,
                                  common::constants::CHUNK_DEPTH));
    }

    const common::storage::palette::PalletizedStorage<block::instance::BlockInstance> &LevelSection::getStorage() {
        return m_blocks;
    }

    Section::SectionType LevelSection::getType() {
        return SectionType::LevelSection;
    }

    uint64_t LevelSection::getModificationCount() {
        return m_modificationCount;
    }

    void LevelSection::setBlock(block::instance::BlockInstance &&blk,
                                const int x, const int y, const int z) {
        m_blocks.setValue(INDEX_YZX(x, y, z, common::constants::CHUNK_WIDTH,
                          common::constants::CHUNK_DEPTH), std::move(blk));

        m_modificationCount++;
    }
} // namespace lodestone::level::chunk::section
