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
    class LODESTONE_API Chunk {
    public:
        virtual ~Chunk() = default;

        virtual void calculateHeightmap() = 0;
        /** Gets the height of the chunk in Sections, can be used for getting section count */
        virtual int getChunkHeight() const = 0;
        /** Gets the height of the chunk in Blocks */
        int getChunkBlockHeight() const;

        virtual section::Section *getSection(int y) const = 0;
        virtual section::Section *getSectionCreate(int y) = 0;

        virtual const int16_t *getHeightmap() const;

        virtual block::state::BlockState *getBlock(int x, int y, int z) const = 0;
        /** Sets a block at the given X, Y, and Z coordinates.
         *
         * Also updates the blockmap and heightmap
         */
        virtual void setBlock(block::state::BlockState &blk, int x, int y, int z) = 0;
        /** Sets a block at the given X, Y, and Z coordinates.
         *
         * Does not update blockmap nor heightmap
         */
        virtual void setBlockRaw(block::state::BlockState &blk, int x, int y, int z) = 0;

        virtual int16_t getHeightAt(int x, int z) const;
        virtual void setHeightAt(int x, int z, int16_t h);
    protected:
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
