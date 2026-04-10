//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/Level.h"

#include <iostream>
#include <limits.h>
#include <random>

#include "Lodestone.Level/block/instance/ImmutableBlockInstance.h"
#include "Lodestone.Level/chunk/ImmutableChunk.h"
#include "Lodestone.Level/chunk/LevelChunk.h"
#include <Lodestone.Common/Indexing.h>

namespace lodestone::level {
#pragma region Blocks
    bool Level::isChunkInBounds(const coords::ChunkCoordinates &chunkCoordinates) { return true; }

    const block::instance::BlockInstance &Level::getBlock(const signed_size_t blockX,
                                                          const signed_size_t blockY,
                                                          const signed_size_t blockZ) const {
        if (const chunk::Chunk *c = getChunkFromBlockCoords(blockX, blockZ))
            return c->getBlock(coords::ChunkCoordinates::blockToLocalChunkX(blockX), blockY, coords::ChunkCoordinates::blockToLocalChunkZ(blockZ));

        return *block::instance::ImmutableBlockInstance::getInstance();
    }

    void Level::setBlock(block::instance::BlockInstance &&block,
                         const signed_size_t blockX, const signed_size_t blockY,
                         const signed_size_t blockZ) {
        if (chunk::Chunk *c = getChunkFromBlockCoords(blockX, blockZ))
            c->setBlock(std::move(block),
                        coords::ChunkCoordinates::blockToLocalChunkX(blockX), blockY,
                        coords::ChunkCoordinates::blockToLocalChunkZ(blockZ));
    }

    void Level::setBlockCreate(block::instance::BlockInstance &&block,
                               const signed_size_t blockX, const signed_size_t blockY,
                               const signed_size_t blockZ, const int height) {
        chunk::Chunk *c = getChunkFromBlockCoords(blockX, blockZ);

        if (!c)
            c = createChunk(coords::ChunkCoordinates::fromBlockCoordinates(blockX, blockZ), height);

        c->setBlock(std::move(block),
                    coords::ChunkCoordinates::blockToLocalChunkX(blockX), blockY,
                    coords::ChunkCoordinates::blockToLocalChunkZ(blockZ));
    }

    void Level::setBlockRaw(block::instance::BlockInstance &&block,
                            const signed_size_t blockX, const signed_size_t blockY,
                            const signed_size_t blockZ) {
        if (chunk::Chunk *c = getChunkFromBlockCoords(blockX, blockZ))
            c->setBlockRaw(std::move(block),
                           coords::ChunkCoordinates::blockToLocalChunkX(blockX),
                           blockY,
                           coords::ChunkCoordinates::blockToLocalChunkZ(blockZ));
    }

    void Level::setBlockCreateRaw(block::instance::BlockInstance &&block,
                                  const signed_size_t blockX, const signed_size_t blockY,
                                  const signed_size_t blockZ, const int height) {
        chunk::Chunk *c = getChunkFromBlockCoords(blockX, blockZ);

        if (!c)
            c = createChunk(coords::ChunkCoordinates::fromBlockCoordinates(blockX, blockZ), height);

        c->setBlockRaw(std::move(block),
                       coords::ChunkCoordinates::blockToLocalChunkX(blockX), blockY,
                       coords::ChunkCoordinates::blockToLocalChunkZ(blockZ));
    }
#pragma endregion

#pragma region Heightmap
    int16_t Level::getHeightAt(const signed_size_t blockX,
                               const signed_size_t blockZ) const {
        if (const chunk::Chunk *c = getChunkFromBlockCoords(blockX, blockZ))
            return c->getHeightAt(
                coords::ChunkCoordinates::blockToLocalChunkX(blockX),
                coords::ChunkCoordinates::blockToLocalChunkZ(blockZ));

        return 0;
    }

    void Level::setHeightAt(const int16_t height, const signed_size_t blockX,
                            const signed_size_t blockZ) {
        if (chunk::Chunk *c = getChunkFromBlockCoords(blockX, blockZ))
            c->setHeightAt(height,
                           coords::ChunkCoordinates::blockToLocalChunkX(blockX),
                           coords::ChunkCoordinates::blockToLocalChunkZ(blockZ));
    }

    void Level::setHeightAtCreate(const int16_t height, const signed_size_t blockX,
                                  const signed_size_t blockZ, const int newChunkHeight) {
        chunk::Chunk *c = getChunkFromBlockCoords(blockX, blockZ);

        if (!c)
            c = createChunk(coords::ChunkCoordinates::fromBlockCoordinates(blockX, blockZ), newChunkHeight);

        c->setHeightAt(height, coords::ChunkCoordinates::blockToLocalChunkX(blockX),
                       coords::ChunkCoordinates::blockToLocalChunkZ(blockZ));
    }
#pragma endregion

#pragma region Blockmap
    const block::instance::BlockInstance &Level::getBlockAtHeight(const signed_size_t blockX, const signed_size_t blockZ) const {
        const chunk::Chunk *c = getChunkFromBlockCoords(blockX, blockZ);
        if (c == nullptr) {
            c = chunk::ImmutableChunk::getInstance();
        }

        return c->getBlockAtHeight(coords::ChunkCoordinates::blockToLocalChunkX(blockX),
                                   coords::ChunkCoordinates::blockToLocalChunkZ(blockZ));
    }

    void Level::setBlockAtHeight(block::instance::BlockInstance &&block, const signed_size_t blockX, const signed_size_t blockZ) {
        chunk::Chunk *c = getChunkFromBlockCoords(blockX, blockZ);
        if (c == nullptr) {
            c = chunk::ImmutableChunk::getInstance();
        }

        c->setBlockAtHeight(std::move(block), coords::ChunkCoordinates::blockToLocalChunkX(blockX),
                            coords::ChunkCoordinates::blockToLocalChunkZ(blockZ));
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

        for (const auto &[coord, chonk] : m_chunks) {
            int mX = coord.x * common::constants::CHUNK_WIDTH;
            int mZ = coord.y * common::constants::CHUNK_DEPTH;

            minX = std::min(minX, mX);
            maxX = std::max(maxX, mX + common::constants::CHUNK_WIDTH - 1);
            minY = std::min(minY, 0); // TODO: minimum block height
            maxY = std::max(maxY, chonk->getChunkBlockHeight());
            minZ = std::min(minZ, mZ);
            maxZ = std::max(maxZ, mZ + common::constants::CHUNK_DEPTH - 1);
        }

        return {minX, minY, minZ, maxX, maxY, maxZ};
    }

    world::World *Level::getWorld() const { return m_world; }

    bool Level::isInWorld() const { return getWorld(); }

    void Level::setWorld(world::World *world) { this->m_world = world; }

    types::Vec3i Level::generateSpawnPos(const unsigned int radius) const {
        types::Vec3i pos = types::VEC3_ZERO<int>;

        if (radius != 0) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(-radius, radius);

            int iter = 0;
            while ((pos.y == 0 || getBlock(pos.x, pos.y - 1, pos.z) == block::BlockRegistry::s_defaultBlock) && iter < 20) {
                // 20 tries ig
                // spread the player
                pos.x = distrib(gen);
                pos.z = distrib(gen);

                // make sure we spawn on top, maybe we should also check if the player's height in blocks is valid too
                pos.y = getHeightAt(pos.x, pos.z);

                iter++;
            }
        }

        return pos;
    }

    const level::types::Vec3i &Level::getSpawnPos() const {
        return this->m_spawnPos;
    }

    void Level::setSpawnPos(const level::types::Vec3i &spawnPos) {
        this->m_spawnPos = spawnPos;
    }

    std::uint64_t Level::getCreationTime() const {
        return m_creationTime;
    }

    void Level::setCreationTime(const std::uint64_t creationTime) {
        m_creationTime = creationTime;
    }
} // namespace lodestone::level