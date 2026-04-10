//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/LevelChunk.h"

#include <Lodestone.Common/util/Math.h>

#include "Lodestone.Level/block/instance/ImmutableBlockInstance.h"

namespace lodestone::level::chunk {
    LevelChunk::LevelChunk(const int height) {
        this->m_sections = std::vector<std::unique_ptr<section::Section>>(
            common::util::Math::ceilDiv(height,
                                        common::constants::SECTION_HEIGHT));
    }

    LevelChunk::LevelChunk(const int height,
                           const coords::ChunkCoordinates &coords, ChunkContainer *container)
        : Chunk(coords, container) {
        this->m_sections = std::vector<std::unique_ptr<section::Section>>(
            common::util::Math::ceilDiv(height,
                                        common::constants::SECTION_HEIGHT));
    }

    ChunkType LevelChunk::type() {
        return ChunkType::LevelChunk;
    }

    int LevelChunk::getChunkHeight() const { return m_sections.size(); }

    bool LevelChunk::hasSection(const coords::SectionCoordinates &sectionY) const {
        if (sectionY < 0 || sectionY >= m_sections.size())
            return false;

        return (m_sections[sectionY] != nullptr);
    }

    section::Section *LevelChunk::getSection(const coords::SectionCoordinates &sectionY) const {
        // if non-existent, return fake one
        if (!hasSection(sectionY))
            return section::ImmutableSection::getInstance();

        return m_sections[sectionY].get();
    }

    section::Section *LevelChunk::getSectionCreate(const coords::SectionCoordinates &sectionY) {
        if (!m_sections[sectionY])
            m_sections[sectionY] = std::make_unique<section::LevelSection>();

        return m_sections[sectionY].get();
    }

    const block::instance::BlockInstance &LevelChunk::getBlock(const int localX, const int blockY, const int localZ) const {
        return getSectionFromBlockY(blockY)->getBlock(localX, coords::SectionCoordinates::blockToLocalSectionY(blockY), localZ);
    }

    void LevelChunk::calculateHeightmap() {
        const int height = getChunkBlockHeight();

        for (int z = 0; z < common::constants::CHUNK_DEPTH; z++) {
            for (int x = 0; x < common::constants::CHUNK_WIDTH; x++) {
               this->calculateHeightmapAtColumn(x, z, height);
            }
        }
    }

    void LevelChunk::calculateHeightmapAtColumn(const int localX, const int localZ,
                                               const int startHeight) {
        for (int y = startHeight; y >= 0; y--) {
            const block::instance::BlockInstance &s = getBlock(localX, y, localZ);
            if (!s.getBlock()->heightmapShouldIgnore()) {
                setHeightAt(y + 1, localX, localZ);
                break;
            }
        }
    }

    void LevelChunk::setBlock(block::instance::BlockInstance &&block,
                              const int localX, const int y, const int localZ) {
        setBlockRaw(std::move(block), localX, y, localZ);

        if (!block.getBlock())
            throw std::runtime_error(
                "attempted to set with instance of null block");

        const int height = getChunkBlockHeight();
        if (!block.getBlock()->heightmapShouldIgnore()) {
            // if our block is higher than the current height, and isn't air,
            // then it's obviously higher up. so we set the new height
            if (y + 1 > getHeightAt(localX, localZ)) {
                setHeightAt(std::min(y + 1, height - 1), localX, localZ);
            };
        } else {
            // if our air block's position is the topmost block of any column
            if (y + 1 == getHeightAt(localX, localZ)) {
                // then we get the new topmost block
                for (int i = y; i >= 0; i--) {
                    const block::instance::BlockInstance &s = getBlock(localX, i, localZ);

                    if (s.getBlock() && !s.getBlock()->heightmapShouldIgnore()) {
                        setHeightAt(std::min(i + 1, height - 1), localX, localZ);

                        return;
                    }
                }

                // there were no blocks
                setHeightAt(0, localX, localZ);
            }
        }
    }

    void LevelChunk::setBlockRaw(block::instance::BlockInstance &&block,
                                 const int localX, const int y, const int localZ) {
        getSectionCreate(y >> 4)->setBlock(std::move(block), localX, y & 15, localZ);
    }

    int LevelChunk::getSectionCount() const {
        return this->m_sections.size();
    }
} // namespace lodestone::level::chunk
