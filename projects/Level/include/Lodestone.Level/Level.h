//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVEL_H
#define LODESTONE_LEVEL_H
#include <unordered_map>

#include "Lodestone.Level/Chunk/Chunk.h"
#include "Lodestone.Level/Types/Vec2i.h"
#include "Lodestone.Level/Types/Bounds.h"

namespace lodestone::level {
    class Level {
    public:
        bool hasChunk(const types::Vec2i &coords) const;
        bool hasChunk(const int x, const int z) const {
            return hasChunk({x, z});
        };

        chunk::Chunk *createChunk(const types::Vec2i &coords, int height = 256);
        chunk::Chunk *createChunk(const int x, const int z, const int height = 256) {
            return createChunk({x, z}, height);
        };

        chunk::Chunk *getChunk(const types::Vec2i &coords);
        chunk::Chunk *getChunk(const int x, const int z) {
            return getChunk({x, z});
        };

        void removeChunk(const types::Vec2i &coords);
        void removeChunk(const int x, const int z) {
            removeChunk({x, z});
        };

        std::unordered_map<types::Vec2i, chunk::Chunk*> &getChunks() {
            return mChunks;
        }

        const std::unordered_map<types::Vec2i, chunk::Chunk*> &getChunks() const {
            return mChunks;
        }

        block::state::BlockState *getBlock(size_t x, size_t y, size_t z);
        void setBlock(block::state::BlockState &blk, size_t x, size_t y, size_t z);
        void setBlockCreate(block::state::BlockState &blk, size_t x, size_t y, size_t z, int height = 256);

        void setBlockRaw(block::state::BlockState &blk, size_t x, size_t y, size_t z);
        void setBlockCreateRaw(block::state::BlockState &blk, size_t x, size_t y, size_t z, int height = 256);

        void getChunkBounds(int &minX, int &minY, int &minZ, int &maxX, int &maxY, int &maxZ);
        void getBlockBounds(int &minX, int &minY, int &minZ, int &maxX, int &maxY, int &maxZ);

        types::Bounds getChunkBounds();

        types::Bounds getBlockBounds();

        size_t getBlockCount();
    private:
        std::unordered_map<types::Vec2i, chunk::Chunk*> mChunks; // or should it be ordered?
    };
}

#endif //LODESTONE_LEVEL_H
