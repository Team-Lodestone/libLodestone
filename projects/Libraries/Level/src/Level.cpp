//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/Level.h"

#include <iostream>
#include <limits.h>
#include <random>

#include "Lodestone.Level/block/properties/EmptyBlockProperties.h"
#include "Lodestone.Level/chunk/LevelChunk.h"
#include <Lodestone.Common/Indexing.h>

namespace lodestone::level {
#pragma region Blocks
    bool Level::isChunkInBounds(const types::Vec2i &coords) { return true; }

    block::properties::BlockProperties *Level::getBlock(const signed_size_t x,
                                                        const signed_size_t y,
                                                        const signed_size_t z) {
        if (const chunk::Chunk *c = getChunk(CHUNK_IDX(x), CHUNK_IDX(z)))
            return c->getBlock(
                CHUNK_LOCAL_IDX(x, common::constants::CHUNK_WIDTH), y,
                CHUNK_LOCAL_IDX(z, common::constants::CHUNK_DEPTH));

        return block::properties::EmptyBlockProperties::getInstance();
    }

    void Level::setBlock(block::properties::BlockProperties &&blk,
                         const signed_size_t x, const signed_size_t y,
                         const signed_size_t z) {
        if (chunk::Chunk *c = getChunk(CHUNK_IDX(x), CHUNK_IDX(z)))
            c->setBlock(std::move(blk),
                        CHUNK_LOCAL_IDX(x, common::constants::CHUNK_WIDTH), y,
                        CHUNK_LOCAL_IDX(z, common::constants::CHUNK_DEPTH));
    }

    void Level::setBlockCreate(block::properties::BlockProperties &&blk,
                               const signed_size_t x, const signed_size_t y,
                               const signed_size_t z, const int height) {
        chunk::Chunk *c = getChunk(CHUNK_IDX(x), CHUNK_IDX(z));

        if (!c)
            c = createChunk(CHUNK_IDX(x), CHUNK_IDX(z), height);

        c->setBlock(std::move(blk),
                    CHUNK_LOCAL_IDX(x, common::constants::CHUNK_WIDTH), y,
                    CHUNK_LOCAL_IDX(z, common::constants::CHUNK_DEPTH));
    }

    void Level::setBlockRaw(block::properties::BlockProperties &&blk,
                            const signed_size_t x, const signed_size_t y,
                            const signed_size_t z) {
        if (chunk::Chunk *c = getChunk(CHUNK_IDX(x), CHUNK_IDX(z)))
            c->setBlockRaw(std::move(blk),
                           CHUNK_LOCAL_IDX(x, common::constants::CHUNK_WIDTH),
                           y,
                           CHUNK_LOCAL_IDX(z, common::constants::CHUNK_DEPTH));
    }

    void Level::setBlockCreateRaw(block::properties::BlockProperties &&blk,
                                  const signed_size_t x, const signed_size_t y,
                                  const signed_size_t z, const int height) {
        chunk::Chunk *c = getChunk(CHUNK_IDX(x), CHUNK_IDX(z));

        if (!c)
            c = createChunk(CHUNK_IDX(x), CHUNK_IDX(z), height);

        c->setBlockRaw(std::move(blk),
                       CHUNK_LOCAL_IDX(x, common::constants::CHUNK_WIDTH), y,
                       CHUNK_LOCAL_IDX(z, common::constants::CHUNK_DEPTH));
    }
#pragma endregion

#pragma region Heightmap
    int16_t Level::getHeightAt(const signed_size_t x,
                               const signed_size_t z) const {
        if (const chunk::Chunk *c = getChunk(CHUNK_IDX(x), CHUNK_IDX(z)))
            return c->getHeightAt(
                CHUNK_LOCAL_IDX(x, common::constants::CHUNK_WIDTH),
                CHUNK_LOCAL_IDX(z, common::constants::CHUNK_DEPTH));

        return 0;
    }

    void Level::setHeightAt(const int16_t h, const signed_size_t x,
                            const signed_size_t z) {
        if (chunk::Chunk *c = getChunk(CHUNK_IDX(x), CHUNK_IDX(z)))
            c->setHeightAt(h,
                           CHUNK_LOCAL_IDX(x, common::constants::CHUNK_WIDTH),
                           CHUNK_LOCAL_IDX(z, common::constants::CHUNK_DEPTH));
    }

    void Level::setHeightAtCreate(const int16_t h, const signed_size_t x,
                                  const signed_size_t z, const int height) {
        chunk::Chunk *c = getChunk(CHUNK_IDX(x), CHUNK_IDX(z));

        if (!c)
            c = createChunk(CHUNK_IDX(x), CHUNK_IDX(z), height);

        c->setHeightAt(h, CHUNK_LOCAL_IDX(x, common::constants::CHUNK_WIDTH),
                       CHUNK_LOCAL_IDX(z, common::constants::CHUNK_DEPTH));
    }
#pragma endregion

#pragma region Blockmap
    const block::properties::BlockProperties *
    Level::getBlockmapBlockAt(const signed_size_t x,
                              const signed_size_t z) const {
        if (const chunk::Chunk *c = getChunk(CHUNK_IDX(x), CHUNK_IDX(z)))
            return c->getBlockmapBlockAt(
                CHUNK_LOCAL_IDX(x, common::constants::CHUNK_WIDTH),
                CHUNK_LOCAL_IDX(z, common::constants::CHUNK_DEPTH));

        return block::properties::EmptyBlockProperties::getInstance();
    }

    void Level::setBlockmapBlockAt(block::properties::BlockProperties *b,
                                   const signed_size_t x,
                                   const signed_size_t z) {
        if (chunk::Chunk *c = getChunk(CHUNK_IDX(x), CHUNK_IDX(z)))
            c->setBlockmapBlockAt(
                b, CHUNK_LOCAL_IDX(x, common::constants::CHUNK_WIDTH),
                CHUNK_LOCAL_IDX(z, common::constants::CHUNK_DEPTH));
    }

    void Level::setBlockmapBlockAtCreate(block::properties::BlockProperties *b,
                                         const signed_size_t x,
                                         const signed_size_t z,
                                         const int height) {
        chunk::Chunk *c = getChunk(CHUNK_IDX(x), CHUNK_IDX(z));

        if (!c)
            c = createChunk(CHUNK_IDX(x), CHUNK_IDX(z), height);

        c->setBlockmapBlockAt(
            b, CHUNK_LOCAL_IDX(x, common::constants::CHUNK_WIDTH),
            CHUNK_LOCAL_IDX(z, common::constants::CHUNK_DEPTH));
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

        for (const auto &[coord, chonk] : mChunks) {
            int mX = coord.x * common::constants::CHUNK_WIDTH;
            int mZ = coord.z * common::constants::CHUNK_DEPTH;

            minX = std::min(minX, mX);
            maxX = std::max(maxX, mX + common::constants::CHUNK_WIDTH - 1);
            minY = std::min(minY, 0); // TODO: minimum block height
            maxY = std::max(maxY, chonk->getChunkBlockHeight());
            minZ = std::min(minZ, mZ);
            maxZ = std::max(maxZ, mZ + common::constants::CHUNK_DEPTH - 1);
        }

        return {minX, minY, minZ, maxX, maxY, maxZ};
    }

    world::World *Level::getWorld() const { return mWorld; }

    bool Level::isInWorld() const { return getWorld(); }

    void Level::setWorld(world::World *world) { this->mWorld = world; }

    types::Vec3i Level::generateSpawnPos(const unsigned int radius) const {
        int x = 0;
        int z = 0;

        // spread the player
        if (radius != 0) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(0 - radius, 0 + radius);

            x = distrib(gen);
            z = distrib(gen);
        }

        int y = getHeightAt(x, z);
        return {x, y, z};
    }

    const level::types::Vec3i &Level::getSpawnPos() const {
        return this->mSpawnPos;
    }

    void Level::setSpawnPos(const level::types::Vec3i &spawnPos) {
        this->mSpawnPos = spawnPos;
    }
} // namespace lodestone::level
