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
    }

    Chunk::Chunk(const coords::ChunkCoordinates &coords, ChunkContainer *container) {
        this->m_coords = std::move(coords);
        this->m_container = container;
    }

    Chunk::~Chunk() {
        delete[] m_heightMap;
    }

    int Chunk::getChunkBlockHeight() const {
        return getChunkHeight() * common::constants::SECTION_HEIGHT;
    }

    section::Section * Chunk::getSectionFromBlockY(const signed_size_t &blockY) const {
        return getSection(coords::SectionCoordinates::fromBlockCoordinates(blockY));
    }

    section::Section * Chunk::getSectionFromBlockYCreate(const signed_size_t &blockY) {
        return getSectionCreate(coords::SectionCoordinates::fromBlockCoordinates(blockY));
    }

    const int16_t * Chunk::getHeightmap() const {
        return this->m_heightMap;
    }

    int16_t Chunk::getHeightAt(const int localX, const int localZ) const {
        return m_heightMap[localZ * common::constants::CHUNK_WIDTH + localX];
    }

    void Chunk::setHeightAt(const int16_t height, const int localX, const int localZ) {
        m_heightMap[localZ * common::constants::CHUNK_WIDTH + localX] = height;
    }

    const block::instance::BlockInstance & Chunk::getBlockAtHeight(const int localX, const int localZ) const {
        const int16_t y = this->getHeightAt(localX, localZ);

        return this->getBlock(localX, y - 1, localZ);
    }

    void Chunk::setBlockAtHeight(block::instance::BlockInstance &&block, const int localX, const int localZ) {
        const int16_t y = this->getHeightAt(localX, localZ);

        this->setBlock(std::move(block), localX, y - 1, localZ);
    }

    bool Chunk::hasCoords() const { return m_coords.has_value(); }

    const std::optional<coords::ChunkCoordinates> &Chunk::getCoords() const { return m_coords; }

    void Chunk::setCoords(const std::optional<coords::ChunkCoordinates> &coords) {
        m_coords = std::move(coords);
    }

    void Chunk::invalidateCoords() { this->m_coords.reset(); }

    void Chunk::attach(ChunkContainer *container) {
        this->m_container = container;
    }

    void Chunk::attach(ChunkContainer *container, const coords::ChunkCoordinates &coords) {
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

    void Chunk::postProcess() {
        this->calculateHeightmap();
    }
} // namespace lodestone::level::chunk
