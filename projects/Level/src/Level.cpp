//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Level.h"

#include <iostream>
#include <limits.h>

#include "Chunk/LevelChunk.h"

namespace lodestone::level {
    bool Level::hasChunk(const types::Vec2i &coords) const {
        return mChunks.contains(coords);
    }

    chunk::Chunk *Level::createChunk(const types::Vec2i &coords, const int height) {
        if (hasChunk(coords)) throw new std::runtime_error("Attempted to place a chunk where there already was one");

        std::unique_ptr<chunk::LevelChunk> ch = std::make_unique<chunk::LevelChunk>(height);

        chunk::Chunk *c = ch.get();
        mChunks[coords] = std::move(ch);

#if CMAKE_BUILD_DEBUG
        std::cout << "Created chunk at X: " << coords.x << ", Z: " << coords.z << std::endl;
#endif

        return c;
    }

    chunk::Chunk * Level::getChunk(const types::Vec2i &coords) {
        if (hasChunk(coords)) return mChunks[coords].get();

        return nullptr;
    }

    void Level::removeChunk(const types::Vec2i &coords) {
        mChunks.erase(coords);
    }

    block::state::BlockState * Level::getBlock(const size_t x, const size_t y, const size_t z) {
        if (!hasChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH)) return new block::state::BlockState();

        return getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH)->getBlock(x % constants::CHUNK_WIDTH, y, z % constants::CHUNK_DEPTH);
    }

    void Level::setBlock(block::state::BlockState &blk, const size_t x, const size_t y, const size_t z) {
        if (!hasChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH)) return;

        getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH)
            ->setBlock(blk, x % constants::CHUNK_WIDTH, y, z % constants::CHUNK_DEPTH);
    }

    void Level::setBlockCreate(block::state::BlockState &blk, const size_t x, const size_t y, const size_t z, const int height) {
        if (!hasChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH)) createChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH, height);

        getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH)
            ->setBlock(blk, x % constants::CHUNK_WIDTH, y, z % constants::CHUNK_DEPTH);
    }

    void Level::setBlockRaw(block::state::BlockState &blk, const size_t x, const size_t y, const size_t z) {
        if (!hasChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH)) return;

        getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH)
            ->setBlockRaw(blk, x % constants::CHUNK_WIDTH, y, z % constants::CHUNK_DEPTH);
    }

    void Level::setBlockCreateRaw(block::state::BlockState &blk, size_t x, size_t y, size_t z, int height) {
        if (!hasChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH)) createChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH, height);

        getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH)
            ->setBlockRaw(blk, x % constants::CHUNK_WIDTH, y, z % constants::CHUNK_DEPTH);
    }

    types::Bounds Level::getChunkBounds() {
        int minX = INT_MAX;
        int minY = INT_MAX;
        int minZ = INT_MAX;
        int maxX = INT_MIN;
        int maxY = INT_MIN;
        int maxZ = INT_MIN;

        for (const auto& [coord, chonk] : mChunks) {
            minX = std::min(minX, coord.x);
            maxX = std::max(maxX, coord.x);
            minY = std::min(minY, 0);
            maxY = std::max(maxY, chonk->getChunkHeight());
            minZ = std::min(minZ, coord.z);
            maxZ = std::max(maxZ, coord.z);
        }

        return {minX, minY, minZ, maxX, maxY, maxZ};
    }

    types::Bounds Level::getBlockBounds() {
        int minX = INT_MAX;
        int minY = INT_MAX;
        int minZ = INT_MAX;
        int maxX = INT_MIN;
        int maxY = INT_MIN;
        int maxZ = INT_MIN;

        for (const auto& [coord, chonk] : mChunks) {
            int mX = coord.x * constants::CHUNK_WIDTH;
            int mZ = coord.z * constants::CHUNK_DEPTH;

            minX = std::min(minX, mX);
            maxX = std::max(maxX, mX + constants::CHUNK_WIDTH - 1);
            minY = std::min(minY, 0); // TODO: minimum block height
            maxY = std::max(maxY, chonk->getChunkBlockHeight());
            minZ = std::min(minZ, mZ);
            maxZ = std::max(maxZ, mZ + constants::CHUNK_DEPTH - 1);
        }

        return {minX, minY, minZ, maxX, maxY, maxZ};
    }

    size_t Level::getBlockCount() {
        auto [min, max] = getBlockBounds();

        return (max.x - min.x + 1) * (max.y - min.y) * (max.z - min.z + 1);
    }
}
