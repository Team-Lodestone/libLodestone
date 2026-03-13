//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/Chunk.h"

#include "Lodestone.Level/block/instance/ImmutableBlockInstance.h"
#include "Lodestone.Level/chunk/ChunkContainer.h"
#include "Lodestone.Level/properties/TemplatedProperty.h"

namespace lodestone::level::chunk {
    Chunk::Chunk() {
        this->m_container = nullptr;
        for (int x = 0; x < lodestone::common::constants::CHUNK_WIDTH *
                                common::constants::CHUNK_DEPTH;
             ++x) {
            m_blockMap[x] = Chunk::BlockmapEntry { block::instance::ImmutableBlockInstance::getInstance(), 0 };
        }
    }

    Chunk::Chunk(const types::Vec2i &coords) : Chunk() {
        this->m_coords = std::move(coords);
        this->m_container = nullptr;
    }

    Chunk::Chunk(ChunkContainer *container, const types::Vec2i &coords)
        : Chunk() {
        this->m_coords = std::move(coords);
        this->m_container = container;
    }

    Chunk::~Chunk() {
        delete[] m_blockMap;
    }

    int Chunk::getChunkBlockHeight() const {
        return getChunkHeight() * common::constants::SECTION_HEIGHT;
    }

    const Chunk::BlockmapEntry *Chunk::getBlockmap() const {
        return m_blockMap;
    }

    int16_t Chunk::getHeightAt(const int x, const int z) const {
        return m_blockMap[z * common::constants::CHUNK_WIDTH + x].height;
    }

    void Chunk::setHeightAt(const int16_t h, const int x, const int z) {
        m_blockMap[z * common::constants::CHUNK_WIDTH + x].height = h;
    }

    const block::instance::BlockInstance *
    Chunk::getBlockmapBlockAt(const int x, const int z) const {
        return m_blockMap[z * common::constants::CHUNK_WIDTH + x].block;
    }

    void Chunk::setBlockmapBlockAt(const block::instance::BlockInstance *b,
                                   const int x, const int z) {
        m_blockMap[z * common::constants::CHUNK_WIDTH + x].block = b;
    }

    const Chunk::BlockmapEntry & Chunk::getBlockmapEntryAt(const int x,
        const int z) const {
        return m_blockMap[z * common::constants::CHUNK_WIDTH + x];
    }

    void Chunk::setBlockmapEntryAt(const BlockmapEntry &b, int x, int z) {
        this->m_blockMap[z * common::constants::CHUNK_WIDTH + x] = b;
    }

    bool Chunk::hasCoords() const { return m_coords.has_value(); }

    const std::optional<types::Vec2i> &Chunk::getCoords() { return m_coords; }

    void Chunk::setCoords(const std::optional<types::Vec2i> &coords) {
        m_coords = std::move(coords);
    }

    void Chunk::invalidateCoords() { this->m_coords.reset(); }

    void Chunk::attach(ChunkContainer *container) {
        this->m_container = container;
    }

    void Chunk::attach(ChunkContainer *container, const types::Vec2i &coords) {
        attach(container);
        setCoords(coords);
    }

    void Chunk::detach(const bool shouldInvalidateCoords) {
        this->m_container = nullptr;
        if (shouldInvalidateCoords)
            invalidateCoords();
    }

    bool Chunk::isInContainer() const { return m_container != nullptr; }

    ChunkContainer *Chunk::getContainer() const { return m_container; }
} // namespace lodestone::level::chunk
