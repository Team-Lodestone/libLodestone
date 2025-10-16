//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "../include/Level.h"

#include "Chunk/LevelChunk.h"

namespace lodestone::level {
    bool Level::hasChunk(const chunk::ChunkCoords &coords) const {
        return (mChunks.count(coords) > 0);
    }

    chunk::Chunk *Level::createChunk(const chunk::ChunkCoords &coords, const int height) {
        if (hasChunk(coords)) throw new std::runtime_error("Attempted to place a chunk where there already was one");

        chunk::Chunk *c = new chunk::LevelChunk(height);
        mChunks[coords] = c;

        return c;
    }

    chunk::Chunk * Level::getChunk(const chunk::ChunkCoords &coords) {
        if (hasChunk(coords)) return mChunks[coords];

        return nullptr;
    }

    void Level::removeChunk(const chunk::ChunkCoords &coords) {
        mChunks.erase(coords);
    }

    block::state::BlockState * Level::getBlock(const size_t x, const size_t y, const size_t z) {
        if (!hasChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_LENGTH)) return new block::state::BlockState();

        return getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_LENGTH)->getBlock(x % constants::CHUNK_WIDTH, y, z % constants::CHUNK_LENGTH);
    }

    void Level::setBlock(block::state::BlockState &blk, const size_t x, const size_t y, const size_t z) {
        if (!hasChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_LENGTH)) return;

        getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_LENGTH)
            ->setBlock(blk, x % constants::CHUNK_WIDTH, y, z % constants::CHUNK_LENGTH);
    }
}
