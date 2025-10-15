//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_CHUNK_H
#define LODESTONE_CHUNK_H
#include <cstdint>
#include <vector>
#include <array>
#include <Block/Blocks.h>

#include "Block/BlockState.h"

namespace lodestone::level::chunk {
    class Chunk {
    public:
        static constexpr int CHUNK_WIDTH = 16;
        static constexpr int CHUNK_LENGTH = 16;

        class Section {
        public:
            static constexpr int SECTION_HEIGHT = 16;

            const block::BlockState *getBlocks() const {
                return mBlocks;
            }

            const uint8_t *getBlockLight() const {
                return mBlockLight;
            }

            const uint8_t *getSkyLight() const {
                return mBlockLight;
            }
        private:
            block::BlockState *mBlocks = new block::BlockState[CHUNK_WIDTH * SECTION_HEIGHT * CHUNK_LENGTH];

            uint8_t *mBlockLight = new uint8_t[CHUNK_WIDTH * SECTION_HEIGHT * CHUNK_LENGTH];
            uint8_t *mSkyLight = new uint8_t[CHUNK_WIDTH * SECTION_HEIGHT * CHUNK_LENGTH];
        };

        /** Creates a new Chunk with chunk sections for the given height */
        Chunk(int height);

        const int16_t *generateHeightmap();

        int getHeight() const {
            return mSections.size() % 16;
        };
    protected:
        /** Chunk Sections
         *
         * Each chunk is made up of x amount of Sections, with each section storing 16x16x16 blocks.
         * This dictates the height of the chunk as each section is 16 blocks in height.
         */
        std::vector<Section> mSections;

        /** Heightmap
         *
         * Each x and z coord corresponds to the topmost block's height
         */
        int16_t *mHeightmap = new int16_t[CHUNK_WIDTH*CHUNK_LENGTH];
        /** Blockmap
         *
         * Each x and z coord corresponds to the topmost block's id
         */
        uint16_t *mBlockmap = new uint16_t[CHUNK_WIDTH*CHUNK_LENGTH];

        // std::unordered_map<Vec3i, TileEntity> mTileEntities;
        // std::unordered_map<Vec3i, Entity> mEntities;
    };
}

#endif //LODESTONE_CHUNK_H
