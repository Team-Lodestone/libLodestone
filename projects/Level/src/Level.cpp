//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/Level.h"

#include <iostream>
#include <limits.h>

#include "Lodestone.Level/chunk/LevelChunk.h"

namespace lodestone::level {
#pragma region Blocks
    bool Level::isChunkInBounds(const types::Vec2i &coords) {
        return true;
    }

    block::state::BlockState *Level::getBlock(const size_t x, const size_t y, const size_t z) {
        if (const chunk::Chunk *c = getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH))
            return c->getBlock(x % constants::CHUNK_WIDTH, y, z % constants::CHUNK_DEPTH);

        return new block::state::BlockState();
    }

    void Level::setBlock(block::state::BlockState &&blk, const size_t x, const size_t y, const size_t z) {
        if (chunk::Chunk *c = getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH))
            c->setBlock(std::move(blk), x % constants::CHUNK_WIDTH, y, z % constants::CHUNK_DEPTH);
    }

    void Level::setBlockCreate(block::state::BlockState &&blk, const size_t x, const size_t y, const size_t z,
                               const int height) {
        chunk::Chunk *c = getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH);

        if (!c) c = createChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH, height);

        c->setBlock(std::move(blk), x % constants::CHUNK_WIDTH, y, z % constants::CHUNK_DEPTH);
    }

    void Level::setBlockRaw(block::state::BlockState &&blk, const size_t x, const size_t y, const size_t z) {
        if (chunk::Chunk *c = getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH))
            c->setBlockRaw(std::move(blk), x % constants::CHUNK_WIDTH, y, z % constants::CHUNK_DEPTH);
    }

    void Level::setBlockCreateRaw(block::state::BlockState &&blk, const size_t x, const size_t y, const size_t z,
                                  const int height) {
        chunk::Chunk *c = getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH);

        if (!c) c = createChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH, height);

        c->setBlockRaw(std::move(blk), x % constants::CHUNK_WIDTH, y, z % constants::CHUNK_DEPTH);
    }
#pragma endregion

#pragma region Heightmap
    int16_t Level::getHeightAt(const int x, const int z) const {
        if (const chunk::Chunk *c = getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH))
            return c->getHeightAt(x % constants::CHUNK_WIDTH, z % constants::CHUNK_DEPTH);

        return 0;
    }

    void Level::setHeightAt(const int16_t h, const int x, const int z) {
        if (chunk::Chunk *c = getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH))
            c->setHeightAt(h, x % constants::CHUNK_WIDTH, z % constants::CHUNK_DEPTH);
    }

    void Level::setHeightAtCreate(const int16_t h, const size_t x, const size_t z, const int height) {
        chunk::Chunk *c = getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH);

        if (!c) c = createChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH, height);

        c->setHeightAt(h, x % constants::CHUNK_WIDTH, z % constants::CHUNK_DEPTH);
    }
#pragma endregion

#pragma region Blockmap
    const block::state::BlockState *Level::getBlockmapBlockAt(const int x, const int z) const {
        if (const chunk::Chunk *c = getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH))
            return c->getBlockmapBlockAt(x % constants::CHUNK_WIDTH, z % constants::CHUNK_DEPTH);

        return new block::state::BlockState();
    }

    void Level::setBlockmapBlockAt(block::state::BlockState *b, const int x, const int z) {
        if (chunk::Chunk *c = getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH))
            c->setBlockmapBlockAt(b, x % constants::CHUNK_WIDTH, z % constants::CHUNK_DEPTH);
    }

    void Level::setBlockmapBlockAtCreate(block::state::BlockState *b, const int x, const int z, const int height) {
        chunk::Chunk *c = getChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH);

        if (!c) c = createChunk(x / constants::CHUNK_WIDTH, z / constants::CHUNK_DEPTH, height);

        c->setBlockmapBlockAt(b, x % constants::CHUNK_WIDTH, z % constants::CHUNK_DEPTH);
    }
#pragma endregion

    size_t Level::getBlockCount() const {
        auto [min, max] = getBlockBounds();

        return (max.x - min.x + 1) * (max.y - min.y) * (max.z - min.z + 1);
    }

    types::Bounds3i Level::getBlockBounds() const {
        int minX = INT_MAX;
        int minY = INT_MAX;
        int minZ = INT_MAX;
        int maxX = INT_MIN;
        int maxY = INT_MIN;
        int maxZ = INT_MIN;

        for (const auto &[coord, chonk]: mChunks) {
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

    world::World * Level::getWorld() const {
        return mWorld;
    }

    bool Level::isInWorld() const {
        return getWorld();
    }

    void Level::setWorld(world::World *world) {
        this->mWorld = world;
    }
}
