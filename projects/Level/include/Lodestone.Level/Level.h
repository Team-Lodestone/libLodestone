//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVEL_H
#define LODESTONE_LEVEL_H
#include <unordered_map>
#include <memory>

#include "Lodestone.Level/chunk/ChunkContainer.h"
#include "Lodestone.Level/chunk/Chunk.h"
#include "Lodestone.Level/types/Vec2i.h"
#include "Lodestone.Level/types/Bounds3i.h"

namespace lodestone::level {
    /** A level, holds Chunks.
     *
     * @see Chunk
     */
    class LODESTONE_API Level : public chunk::ChunkContainer {
    public:
        bool isChunkInBounds(const types::Vec2i &coords) override;

        block::state::BlockState *getBlock(size_t x, size_t y, size_t z);

        void setBlock(block::state::BlockState &blk, size_t x, size_t y, size_t z);

        void setBlockRaw(block::state::BlockState &blk, size_t x, size_t y, size_t z);

        void setBlockCreate(block::state::BlockState *blk, size_t x, size_t y, size_t z, int height = 256);

        void setBlockCreateRaw(block::state::BlockState &blk, size_t x, size_t y, size_t z, int height = 256);

        int16_t getHeightAt(int x, int z) const;

        void setHeightAt(int16_t h, int x, int z);

        void setHeightAtCreate(int16_t h, size_t x, size_t z, int height = 256);

        const block::state::BlockState *getBlockmapBlockAt(int x, int z) const;

        void setBlockmapBlockAt(block::state::BlockState *b, int x, int z);

        void setBlockmapBlockAtCreate(block::state::BlockState *b, int x, int z, int height = 256);

        size_t getBlockCount() const;

        types::Bounds3i getBlockBounds() const;
    };
}

#endif //LODESTONE_LEVEL_H