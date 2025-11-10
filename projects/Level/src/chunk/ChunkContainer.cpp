//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/ChunkContainer.h"

#include <iostream>

#include "Lodestone.Level/chunk/LevelChunk.h"
#include "Lodestone.Level/types/Bounds3i.h"

namespace lodestone::level::chunk {
    bool ChunkContainer::hasChunk(const types::Vec2i &coords) const {
        return mChunks.contains(coords);
    }

    chunk::Chunk *ChunkContainer::createChunk(const types::Vec2i &coords, const int height) {
        if (hasChunk(coords)) throw new std::runtime_error("Attempted to place a chunk where there already was one");
        if (!isChunkInBounds(coords)) throw new std::runtime_error(
            "Attempted to place a chunk past the bounds of the ChunkContainer");

        std::unique_ptr<chunk::LevelChunk> ch = std::make_unique<chunk::LevelChunk>(height);
        ch->attach(this, coords);

        chunk::Chunk *c = ch.get();
        mChunks[coords] = std::move(ch);

#if CMAKE_BUILD_DEBUG
        std::cout << "Created chunk at X: " << coords.x << ", Z: " << coords.z << std::endl;
#endif

        return c;
    }

    void ChunkContainer::addChunk(std::unique_ptr<chunk::Chunk> chunk) {
        const std::optional<types::Vec2i> &optCoords = chunk->getCoords();

        if (!optCoords.has_value()) throw std::runtime_error("Tried to place chunk that does not contain coords");
        const types::Vec2i &coords = optCoords.value();

        if (mChunks.contains(coords)) throw std::runtime_error(
            std::format("Tried to place chunk over existing chunk at coordinates {}", coords.toString()));
        if (!isChunkInBounds(coords)) throw new std::runtime_error(
            "Attempted to place a chunk past the bounds of the ChunkContainer");

        chunk->attach(this);
        mChunks[coords] = std::move(chunk);
    }

    void ChunkContainer::addChunk(const types::Vec2i &coords, std::unique_ptr<chunk::Chunk> chunk) {
        if (mChunks.contains(coords)) throw std::runtime_error(
            std::format("Tried to place chunk over existing chunk at coordinates {}", coords.toString()));
        if (!isChunkInBounds(coords)) throw new std::runtime_error(
            "Attempted to place a chunk past the bounds of the ChunkContainer");

        chunk->attach(this, coords);
        mChunks[coords] = std::move(chunk);
    }

    chunk::Chunk *ChunkContainer::getChunk(const types::Vec2i &coords) {
        if (const auto it = mChunks.find(coords); it != mChunks.end()) return it->second.get();

        return nullptr;
    }

    chunk::Chunk *ChunkContainer::getChunkCreate(const types::Vec2i &coords, const int height) {
        if (const auto it = mChunks.find(coords); it != mChunks.end()) return it->second.get();

        return createChunk(coords, height);
    }

    const chunk::Chunk *ChunkContainer::getChunk(const types::Vec2i &coords) const {
        if (const auto it = mChunks.find(coords); it != mChunks.end()) return it->second.get();

        return nullptr;
    }

    std::unique_ptr<chunk::Chunk> ChunkContainer::detachChunk(const types::Vec2i &coords,
                                                              const bool shouldInvalidateCoords) {
        const auto it = mChunks.find(coords);
        if (it == mChunks.end()) throw std::runtime_error(
            std::format("Tried to detach nonexistent chunk at coords {}", coords.toString()));

        std::unique_ptr<chunk::Chunk> chunk = std::move(it->second);
        chunk->detach(shouldInvalidateCoords);

        mChunks.erase(it);

        return chunk;
    }

    void ChunkContainer::removeChunk(const types::Vec2i &coords) {
        mChunks.erase(coords);
    }

    void ChunkContainer::merge(ChunkContainer &rhs) {
        for (auto it = rhs.mChunks.begin(); it != rhs.mChunks.end();) {
            if (auto dest = mChunks.find(it->first); dest == mChunks.end()
                                                     && this->isChunkInBounds(it->first)) {
                it->second->attach(this);
                this->mChunks.emplace(it->first, std::move(it->second));
            }

            it = rhs.mChunks.erase(it);
        }
    }

    // TODO recalculate bounds on modification
    types::Bounds3i ChunkContainer::getChunkBounds() const {
        int minX = INT_MAX;
        int minY = INT_MAX;
        int minZ = INT_MAX;
        int maxX = INT_MIN;
        int maxY = INT_MIN;
        int maxZ = INT_MIN;

        for (const auto &[coord, chonk]: mChunks) {
            minX = std::min(minX, coord.x);
            maxX = std::max(maxX, coord.x);
            minY = std::min(minY, 0);
            maxY = std::max(maxY, chonk->getChunkHeight());
            minZ = std::min(minZ, coord.z);
            maxZ = std::max(maxZ, coord.z);
        }

        return {minX, minY, minZ, maxX, maxY, maxZ};
    }
}