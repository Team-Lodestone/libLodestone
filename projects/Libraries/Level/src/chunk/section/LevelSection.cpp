//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/section/LevelSection.h"

#include <Lodestone.Common/Indexing.h>

namespace lodestone::level::chunk::section {
    LevelSection::~LevelSection() {
        delete[] m_biomes;
    }

    SectionType LevelSection::type() {
        return SectionType::LevelSection;
    }

    lodestone::common::storage::bits::AbstractBitStorage *LevelSection::getBlockLightStorage() {
        return &m_blockLightStorage;
    }

    lodestone::common::storage::bits::AbstractBitStorage *LevelSection::getSkyLightStorage() {
        return &m_skyLightStorage;
    }

    void LevelSection::setBlockLight(const int localX, const int localY, const int localZ, const uint8_t lightLevel) {
        this->m_blockLightStorage.setNibble(localX, localY, localZ, lightLevel & 0xF);

        m_modificationCount++;
    }

    void LevelSection::setSkyLight(const int localX, const int localY, const int localZ,
                                   const uint8_t lightLevel) {
        this->m_skyLightStorage.setNibble(localX, localY, localZ, lightLevel & 0xF);

        m_modificationCount++;
    }

    const block::instance::BlockInstance &
    LevelSection::getBlock(const int localX, const int localY, const int localZ) const {
        return m_blockStorage.getValue(INDEX_YZX(localX, localY, localZ, common::constants::CHUNK_WIDTH,
                                  common::constants::CHUNK_DEPTH));
    }

    const common::storage::palette::PalletizedStorage<block::instance::BlockInstance> &LevelSection::getBlockStorage() {
        return m_blockStorage;
    }

    uint64_t LevelSection::getModificationCount() {
        return m_modificationCount;
    }

    void LevelSection::setBlock(block::instance::BlockInstance &&block, const int localX, const int localY, const int localZ) {
        m_blockStorage.setValue(INDEX_YZX(localX, localY, localZ, common::constants::CHUNK_WIDTH,
                          common::constants::CHUNK_DEPTH), std::move(block));

        m_modificationCount++;
    }
} // namespace lodestone::level::chunk::section
