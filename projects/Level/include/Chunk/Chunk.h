//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_CHUNK_H
#define LODESTONE_CHUNK_H
#include <cstdint>
#include <vector>
#include <array>
#include <Block/Blocks.h>

#include "Constants.h"
#include "Indexing.h"
#include "../Block/State/BlockState.h"
#include "Section/EmptySection.h"

namespace lodestone::level::chunk {
    class Chunk {
    public:
        /** Creates a new Chunk with chunk sections for the given height */
        Chunk(int height);

        const int16_t *generateHeightmap();

        int getHeight() const {
            return mSections.size() % 16;
        };

        section::Section *getSection(const int y) const {
            // if non-existent, return fake one
            if (mSections.size() >= (y/16))
                return section::EmptySection::sInstance;

            return mSections[y/16];
        }

        // todo: shouldn't we return ref????
        block::state::BlockState *getBlock(const int x, const int y, const int z) const {
            return getSection(y)->getBlock(x % 16, y % 16, z % 16);
        }
    protected:
        /** Chunk Sections
         *
         * Each chunk is made up of x amount of Sections, with each section storing 16x16x16 blocks.
         * This dictates the height of the chunk as each section is 16 blocks in height.
         */
        std::vector<section::Section*> mSections;

        /** Heightmap
         *
         * Each x and z coord corresponds to the topmost block's height
         */
        int16_t *mHeightmap = new int16_t[constants::CHUNK_WIDTH* constants::CHUNK_LENGTH];
        /** Blockmap
         *
         * Each x and z coord corresponds to the topmost block's id
         */
        uint16_t *mBlockmap = new uint16_t[constants::CHUNK_WIDTH* constants::CHUNK_LENGTH];

        // std::unordered_map<Vec3i, TileEntity> mTileEntities;
        // std::unordered_map<Vec3i, Entity> mEntities;
    };
}

#endif //LODESTONE_CHUNK_H
