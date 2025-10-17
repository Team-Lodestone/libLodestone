//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVEL_H
#define LODESTONE_LEVEL_H
#include <unordered_map>
#include <Chunk/Chunk.h>
#include <Chunk/ChunkCoords.h>

#include "Bounds.h"
#include "Vector3.h"

namespace lodestone::level {
    class Level {
    public:
        bool hasChunk(const chunk::ChunkCoords &coords) const;
        bool hasChunk(const int x, const int z) const {
            return hasChunk({x, z});
        };

        chunk::Chunk *createChunk(const chunk::ChunkCoords &coords, int height = 256);
        chunk::Chunk *createChunk(const int x, const int z, const int height = 256) {
            return createChunk({x, z}, height);
        };

        chunk::Chunk *getChunk(const chunk::ChunkCoords &coords);
        chunk::Chunk *getChunk(const int x, const int z) {
            return getChunk({x, z});
        };

        void removeChunk(const chunk::ChunkCoords &coords);
        void removeChunk(const int x, const int z) {
            removeChunk({x, z});
        };

        std::unordered_map<chunk::ChunkCoords, chunk::Chunk*> &getChunks() {
            return mChunks;
        }

        const std::unordered_map<chunk::ChunkCoords, chunk::Chunk*> &getChunks() const {
            return mChunks;
        }

        block::state::BlockState *getBlock(size_t x, size_t y, size_t z);
        void setBlock(block::state::BlockState &blk, size_t x, size_t y, size_t z);
        void setBlockCreate(block::state::BlockState &blk, size_t x, size_t y, size_t z, int height = 256);

        void setBlockRaw(block::state::BlockState &blk, size_t x, size_t y, size_t z);
        void setBlockCreateRaw(block::state::BlockState &blk, size_t x, size_t y, size_t z, int height = 256);

        void getChunkBounds(int &minX, int &minY, int &minZ, int &maxX, int &maxY, int &maxZ);
        void getBlockBounds(int &minX, int &minY, int &minZ, int &maxX, int &maxY, int &maxZ);

        Bounds getChunkBounds();
        Bounds getBlockBounds();

        size_t getBlockCount();
    private:
        std::unordered_map<chunk::ChunkCoords, chunk::Chunk*> mChunks; // or should it be ordered?
    };
}

#endif //LODESTONE_LEVEL_H
