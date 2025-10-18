//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Chunk/LevelChunk.h"

namespace lodestone::level::chunk {
    LevelChunk::LevelChunk(const int height) {
        this->mSections = std::vector<std::unique_ptr<section::Section>>(height / 16);
    }

    int LevelChunk::getChunkHeight() const {
        return mSections.size();
    }

    bool LevelChunk::hasSection(const int y) const {
        if (mSections.size() > y)
            return (mSections[y] != nullptr);
        return false;
    }

    section::Section * LevelChunk::getSection(const int y) const {
        // if non-existent, return fake one
        if (!hasSection(y))
            return section::EmptySection::sInstance;

        return mSections[y].get();
    }

    section::Section * LevelChunk::getSectionCreate(const int y) {
        if (!hasSection(y)) mSections[y] = std::make_unique<section::LevelSection>();

        return mSections[y].get();
    }

    block::state::BlockState * LevelChunk::getBlock(const int x, const int y, const int z) const {
        return getSection(y >> 4)->getBlock(x, y & 15, z);
    }

    void LevelChunk::calculateHeightmap() {
        const int height = getChunkBlockHeight();

        for (int z = 0; z < constants::CHUNK_DEPTH; z++) {
            for (int x = 0; x < constants::CHUNK_WIDTH; x++) {
                for (int y = height; y >= 0; y--) {
                    if (getBlock(x, y, z)->getBlock() != block::BlockRegistry::sDefaultBlock) {
                        setHeightAt(std::min(y + 1,  height - 1), x, z);
                        break;
                    }
                }
            }
        }
    }

    void LevelChunk::calculateBlockmap() {
        const int height = getChunkBlockHeight();

        for (int z = 0; z < constants::CHUNK_DEPTH; z++) {
            for (int x = 0; x < constants::CHUNK_WIDTH; x++) {
                for (int y = height; y >= 0; y--) {
                    if (block::state::BlockState *s = getBlock(x, y, z); s != getBlockmapBlockAt(x, z) && *s != block::BlockRegistry::sDefaultBlock) {
                        setBlockmapBlockAt(s, x, z);
                        break;
                    }
                }
            }
        }
    }

    void LevelChunk::calculateMaps() {
        const int height = getChunkBlockHeight();

        for (int z = 0; z < constants::CHUNK_DEPTH; z++) {
            for (int x = 0; x < constants::CHUNK_WIDTH; x++) {
                for (int y = height; y >= 0; y--) {
                    if (block::state::BlockState *s = getBlock(x, y, z); *s != block::BlockRegistry::sDefaultBlock) {
                        setHeightAt(std::min(y + 1,  height - 1), x, z);

                        if (s != getBlockmapBlockAt(x, z))
                            setBlockmapBlockAt(s, x, z);
                        break;
                    }
                }
            }
        }
    }

    void LevelChunk::setBlock(block::state::BlockState &blk, const int x, const int y, const int z) {
        setBlockRaw(blk, x, y, z);

        const int height = getChunkBlockHeight();
        if (blk.getBlock() != block::BlockRegistry::sDefaultBlock) {
            // if our block is higher than the current height, and isn't air, then it's obviously higher up.
            // so we set the new height
            if (y >= getHeightAt(x, z)) {
                setHeightAt(std::min(y + 1, height - 1), x, z);

                if (&blk != getBlockmapBlockAt(x, z))
                    setBlockmapBlockAt(&blk, x, z);
            };
        } else {
            // if our air block's position is the topmost block of any column
            if (y + 1 == getHeightAt(x, z)) {
                // then we get the new topmost block
                for (int i = y; i >= 0; i--) {
                    if (block::state::BlockState *s = getBlock(x, i, z); s->getBlock() != block::BlockRegistry::sDefaultBlock)  {
                        setHeightAt(std::min(i + 1, height - 1), x, z); // new highest block

                        if (s != getBlockmapBlockAt(x, z))
                            setBlockmapBlockAt(s, x, z);

                        return;
                    }
                }

                // there were no blocks
                setBlockmapBlockAt(new block::state::BlockState(), x, z); // should be good?
                setHeightAt(x, z, 0);
            }
        }
    }

    void LevelChunk::setBlockRaw(block::state::BlockState &blk, const int x, const int y, const int z) {
        getSectionCreate(y >> 4)->setBlock(blk, x, y & 15, z);
    }
}
