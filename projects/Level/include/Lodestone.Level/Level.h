//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVEL_H
#define LODESTONE_LEVEL_H
#include <unordered_map>
#include <memory>

#include "Lodestone.Level/Chunk/Chunk.h"
#include "Lodestone.Level/Types/Vec2i.h"
#include "Lodestone.Level/Types/Bounds.h"

namespace lodestone::level {
    /** A level, holds Chunks.
     *
     * @see Chunk
     */
    class Level {
    public:
        /** Returns true if chunk at coords exist
         *
         * @param coords The coordinates you want to check for a chunk
         * @returns @c true if a chunk at given coords exist
         */
        bool hasChunk(const types::Vec2i &coords) const;
        /** Returns true if chunk at coords exist
         *
         * @param x The X coordinate you want to check for a chunk
         * @param z The Z coordinate you want to check for a chunk
         * @returns @c true if a chunk at given coords exist
         */
        bool hasChunk(const int x, const int z) const {
            return hasChunk({x, z});
        };

        /** Creates a chunk at the given coordinates with the given height
         *
         * @param coords The coordinates you want to create a chunk at
         * @param height The height you'd like to make the new chunk
         * @returns The new chunk
         */
        chunk::Chunk *createChunk(const types::Vec2i &coords, int height = 256);
        /** Creates a chunk at the given coordinates with the given height
         *
         * @param x The x coordinate you want to create a chunk at
         * @param z The z coordinate you want to create a chunk at
         * @param height The height you'd like to make the new chunk
         * @returns The new chunk
         */
        chunk::Chunk *createChunk(const int x, const int z, const int height = 256) {
            return createChunk({x, z}, height);
        };

        chunk::Chunk *getChunk(const types::Vec2i &coords);
        chunk::Chunk *getChunk(const int x, const int z) {
            return getChunk({x, z});
        };

        const chunk::Chunk *getChunk(const types::Vec2i &coords) const;
        const chunk::Chunk *getChunk(const int x, const int z) const {
            return getChunk({x, z});
        };

        void removeChunk(const types::Vec2i &coords);
        void removeChunk(const int x, const int z) {
            removeChunk({x, z});
        };

        std::unordered_map<types::Vec2i, std::unique_ptr<chunk::Chunk>> &getChunks() {
            return mChunks;
        }

        const std::unordered_map<types::Vec2i, std::unique_ptr<chunk::Chunk>> &getChunks() const {
            return mChunks;
        }

        block::state::BlockState *getBlock(size_t x, size_t y, size_t z);
        void setBlock(block::state::BlockState &blk, size_t x, size_t y, size_t z);
        void setBlockCreate(block::state::BlockState &blk, size_t x, size_t y, size_t z, int height = 256);

        void setBlockRaw(block::state::BlockState &blk, size_t x, size_t y, size_t z);
        void setBlockCreateRaw(block::state::BlockState &blk, size_t x, size_t y, size_t z, int height = 256);

        int16_t getHeightAt(int x, int z) const;
        void setHeightAt(int16_t h, int x, int z);
        void setHeightAtCreate(int16_t h, size_t x, size_t z, int height = 256);

        const block::state::BlockState *getBlockmapBlockAt(int x, int z) const;
        void setBlockmapBlockAt(block::state::BlockState *b, int x, int z);
        void setBlockmapBlockAtCreate(block::state::BlockState *b, int x, int z, int height = 256);


        types::Bounds getChunkBounds();
        types::Bounds getBlockBounds();

        size_t getBlockCount();

        std::unordered_map<types::Vec2i, std::unique_ptr<chunk::Chunk>>::iterator begin() {
            return mChunks.begin();
        }

        std::unordered_map<types::Vec2i, std::unique_ptr<chunk::Chunk>>::iterator end() {
            return mChunks.end();
        }
    private:
        std::unordered_map<types::Vec2i, std::unique_ptr<chunk::Chunk>> mChunks;
    };
}

#endif //LODESTONE_LEVEL_H
