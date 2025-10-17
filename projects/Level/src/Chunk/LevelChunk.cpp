//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Chunk/LevelChunk.h"

namespace lodestone::level::chunk {
    LevelChunk::LevelChunk(const int height) {
        this->mSections = std::vector<section::Section*>(height / 16);
    }

    void LevelChunk::calculateHeightmap() {
        const int height = getChunkBlockHeight();

        for (int z = 0; z < constants::CHUNK_LENGTH; z++) {
            for (int x = 0; x < constants::CHUNK_WIDTH; x++) {
                for (int y = height; y >= 0; y--) {
                    if (getBlock(x, y, z)->getBlock()->getID() != "lodestone:air") {
                        setHeightAt(x, z, std::min(y + 1,  height - 1));
                        break;
                    }
                }
            }
        }
    }

    void LevelChunk::setBlock(block::state::BlockState &blk, const int x, const int y, const int z) {
        setBlockRaw(blk, x, y, z);

        const int height = getChunkBlockHeight();
        if (blk.getBlock()->getID() != "lodestone:air") {
            // if our block is heigher than the current height, and isn't air, then it's obviously higher up.
            // so we set the new height
            if (y >= getHeightAt(x, z)) setHeightAt(x, z, std::min(y + 1, height - 1));
        } else {
            // if our air block's position is the topmost block of any column
            if (y + 1 == getHeightAt(x, z)) {
                // then we get the new topmost block
                for (int i = y; i >= 0; i--) {
                    if (getBlock(x, i, z)->getBlock()->getID() != "lodestone:air")  {
                        setHeightAt(x, z, std::min(i + 1, height - 1)); // new highest block
                        return;
                    }
                }

                // there were no blocks
                setHeightAt(x, z, 0);
            }
        }
    }

    void LevelChunk::setBlockRaw(block::state::BlockState &blk, int x, int y, int z) {
        getSectionCreate(y / 16)->setBlock(blk, x, y % 16, z);
    }
}
