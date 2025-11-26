//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.Level/chunk/Chunk.h"

#include "Lodestone.Level/chunk/ChunkContainer.h"
#include "Lodestone.Level/properties/TemplatedProperty.h"

namespace lodestone::level::chunk {
    Chunk::Chunk() {
        this->mContainer = nullptr;
        for (int x = 0; x < lodestone::common::constants::CHUNK_WIDTH *
                                common::constants::CHUNK_DEPTH;
             ++x) {
            mBlockmap[x] = new block::properties::BlockProperties();
        }
    }

    Chunk::Chunk(const types::Vec2i &coords) : Chunk() {
        this->mCoords = std::move(coords);
        this->mContainer = nullptr;
    }

    Chunk::Chunk(ChunkContainer *container, const types::Vec2i &coords)
        : Chunk() {
        this->mCoords = std::move(coords);
        this->mContainer = container;
    }

    Chunk::~Chunk() {
        delete[] mHeightmap;
        delete[] mBlockmap;
    }

    int Chunk::getChunkBlockHeight() const {
        return getChunkHeight() * common::constants::SECTION_HEIGHT;
    }

    const int16_t *Chunk::getHeightmap() const { return mHeightmap; }

    const block::properties::BlockProperties **Chunk::getBlockmap() const {
        return const_cast<const block::properties::BlockProperties **>(
            mBlockmap);
    }

    int16_t Chunk::getHeightAt(const int x, const int z) const {
        return mHeightmap[z * common::constants::CHUNK_WIDTH + x];
    }

    void Chunk::setHeightAt(const int16_t h, const int x, const int z) {
        mHeightmap[z * common::constants::CHUNK_WIDTH + x] = h;
    }

    const block::properties::BlockProperties *
    Chunk::getBlockmapBlockAt(const int x, const int z) const {
        return mBlockmap[z * common::constants::CHUNK_WIDTH + x];
    }

    void Chunk::setBlockmapBlockAt(block::properties::BlockProperties *b,
                                   const int x, const int z) {
        mBlockmap[z * common::constants::CHUNK_WIDTH + x] = b;
    }

    bool Chunk::hasCoords() const { return mCoords.has_value(); }

    const std::optional<types::Vec2i> &Chunk::getCoords() { return mCoords; }

    void Chunk::setCoords(const std::optional<types::Vec2i> &coords) {
        mCoords = std::move(coords);
    }

    void Chunk::invalidateCoords() { this->mCoords.reset(); }

    void Chunk::attach(ChunkContainer *container) {
        this->mContainer = container;
    }

    void Chunk::attach(ChunkContainer *container, const types::Vec2i &coords) {
        attach(container);
        setCoords(coords);
    }

    void Chunk::detach(const bool shouldInvalidateCoords) {
        this->mContainer = nullptr;
        if (shouldInvalidateCoords)
            invalidateCoords();
    }

    bool Chunk::isInContainer() const { return mContainer != nullptr; }

    ChunkContainer *Chunk::getContainer() const { return mContainer; }
} // namespace lodestone::level::chunk
