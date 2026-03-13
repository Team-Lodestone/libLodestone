//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/ChunkContainer.h"

#include <iostream>

#include "Lodestone.Level/chunk/LevelChunk.h"
#include "Lodestone.Level/types/Bounds3.h"
#include <Lodestone.Common/util/Math.h>

#include <Lodestone.Common/util/Logging.h>

namespace lodestone::level::chunk {
    bool ChunkContainer::hasChunk(const types::Vec2i &coords) const {
        return m_chunks.contains(coords);
    }

    chunk::Chunk *ChunkContainer::createChunk(const types::Vec2i &coords,
                                              const int height) {
        if (hasChunk(coords))
            throw std::runtime_error(
                "Attempted to place a chunk where there already was one");
        if (!isChunkInBounds(coords))
            throw std::runtime_error("Attempted to place a chunk past the "
                                     "bounds of the ChunkContainer");

        std::unique_ptr<chunk::LevelChunk> ch =
            std::make_unique<chunk::LevelChunk>(height);
        ch->attach(this, coords);

        chunk::Chunk *c = ch.get();
        m_chunks[coords] = std::move(ch);

        LOG_DEBUG("Created chunk at X: " << coords.x << ", Z: " << coords.y);

        return c;
    }

    void ChunkContainer::addChunk(std::unique_ptr<chunk::Chunk> chunk) {
        const std::optional<types::Vec2i> &optCoords = chunk->getCoords();

        if (!optCoords.has_value())
            throw std::runtime_error(
                "Tried to place chunk that does not contain coords");
        const types::Vec2i &coords = optCoords.value();

        if (m_chunks.contains(coords))
            throw std::runtime_error(std::format(
                "Tried to place chunk over existing chunk at coordinates {}",
                coords.toString()));
        if (!isChunkInBounds(coords))
            throw new std::runtime_error("Attempted to place a chunk past the "
                                         "bounds of the ChunkContainer");

        chunk->attach(this);
        m_chunks[coords] = std::move(chunk);
    }

    void ChunkContainer::addChunk(const types::Vec2i &coords,
                                  std::unique_ptr<chunk::Chunk> chunk) {
        if (m_chunks.contains(coords))
            throw std::runtime_error(std::format(
                "Tried to place chunk over existing chunk at coordinates {}",
                coords.toString()));
        if (!isChunkInBounds(coords))
            throw new std::runtime_error("Attempted to place a chunk past the "
                                         "bounds of the ChunkContainer");

        chunk->attach(this, coords);
        m_chunks[coords] = std::move(chunk);
    }

    chunk::Chunk *ChunkContainer::getChunk(const types::Vec2i &coords) {
        if (const auto it = m_chunks.find(coords); it != m_chunks.end())
            return it->second.get();

        return nullptr;
    }

    chunk::Chunk *ChunkContainer::getChunkCreate(const types::Vec2i &coords,
                                                 const int height) {
        if (const auto it = m_chunks.find(coords); it != m_chunks.end())
            return it->second.get();

        return createChunk(coords, height);
    }

    const chunk::Chunk *
    ChunkContainer::getChunk(const types::Vec2i &coords) const {
        if (const auto it = m_chunks.find(coords); it != m_chunks.end())
            return it->second.get();

        return nullptr;
    }

    std::unique_ptr<chunk::Chunk>
    ChunkContainer::detachChunk(const types::Vec2i &coords,
                                const bool shouldInvalidateCoords) {
        const auto it = m_chunks.find(coords);
        if (it == m_chunks.end())
            throw std::runtime_error(
                std::format("Tried to detach nonexistent chunk at coords {}",
                            coords.toString()));

        std::unique_ptr<chunk::Chunk> chunk = std::move(it->second);
        chunk->detach(shouldInvalidateCoords);

        m_chunks.erase(it);

        return chunk;
    }

    void ChunkContainer::removeChunk(const types::Vec2i &coords) {
        m_chunks.erase(coords);
    }

    void ChunkContainer::merge(std::unique_ptr<ChunkContainer> rhs) {
        for (auto it = rhs->m_chunks.begin(); it != rhs->m_chunks.end();) {
            if (auto dest = m_chunks.find(it->first);
                dest == m_chunks.end() && this->isChunkInBounds(it->first)) {
                it->second->attach(this);
                this->m_chunks.emplace(it->first, std::move(it->second));
            }

            it = rhs->m_chunks.erase(it);
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

        if (m_chunks.empty()) {
            return {0, 0, 0, 0, 0, 0};
        }

        for (const auto &[coord, chonk] : m_chunks) {
            minX = std::min(minX, coord.x);
            maxX = std::max(maxX, coord.x);
            minY = std::min(minY, 0);
            maxY = std::max(maxY, chonk->getChunkHeight());
            minZ = std::min(minZ, coord.y);
            maxZ = std::max(maxZ, coord.y);
        }

        return {minX,
                minY,
                minZ,
                common::util::Math::ceilDiv(maxX - minX + 1, 1),
                common::util::Math::ceilDiv(maxY - minY + 1, 1),
                common::util::Math::ceilDiv(maxZ - minZ + 1, 1)};
    }
} // namespace lodestone::level::chunk