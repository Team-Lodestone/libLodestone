//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#ifndef LODESTONE_CHUNKCONTAINER_H
#define LODESTONE_CHUNKCONTAINER_H
#include <memory>

#include "Lodestone.Level/chunk/Chunk.h"
#include "Lodestone.Level/types/Bounds3.h"
#include "Lodestone.Level/types/Vec2.h"

namespace lodestone::level::chunk {
    /** Holds chunks */
    class LODESTONE_API ChunkContainer : public lodestone::common::string::StringSerializable {
    public:
        ~ChunkContainer() override = default;
        ChunkContainer() = default;
        ChunkContainer(ChunkContainer&&) = default;
        ChunkContainer& operator=(ChunkContainer&&) = default;

        std::string toString() const override {
            return (common::string::OperatorStringBuilder(typeid(*this)))
                .addField("chunks", mChunks.size())
                ->addField("bounds", getChunkBounds().toString())
                ->toString();
        };

        virtual bool isChunkInBounds(const types::Vec2i &coords) = 0;

        /** Returns true if chunk at coords exist
         *
         * @param coords The coordinates you want to check for a chunk
         * @returns @c true if a chunk at given coords exist
         */
        bool hasChunk(const types::Vec2i &coords) const;

        /** Returns true if chunk at coords exist
         *
         * @param x The X coordinate you want to check for a chunk
         * @param z The Z coordinate you want to check for a chunk
         * @returns @c true if a chunk at given coords exist
         */
        bool hasChunk(const int x, const int z) const {
            return hasChunk({x, z});
        };

        /** Creates a chunk at the given coordinates with the given height
         *
         * @param coords The coordinates you want to create a chunk at
         * @param height The height you'd like to make the new chunk
         * @returns The new chunk
         */
        Chunk *createChunk(const types::Vec2i &coords, int height = 256);

        /** Creates a chunk at the given coordinates with the given height
         *
         * @param x The x coordinate you want to create a chunk at
         * @param z The z coordinate you want to create a chunk at
         * @param height The height you'd like to make the new chunk
         * @returns The new chunk
         */
        Chunk *createChunk(const int x, const int z, const int height = 256) {
            return createChunk({x, z}, height);
        };

        void addChunk(std::unique_ptr<Chunk> chunk);

        void addChunk(const types::Vec2i &coords, std::unique_ptr<Chunk> chunk);

        void addChunk(const int x, const int z, std::unique_ptr<Chunk> chunk) {
            addChunk({x, z}, std::move(chunk));
        }

        Chunk *getChunk(const types::Vec2i &coords);

        Chunk *getChunk(const int x, const int z) {
            return getChunk({x, z});
        };

        Chunk *getChunkCreate(const types::Vec2i &coords, int height = 256);

        Chunk *getChunkCreate(const int x, const int z, int height = 256) {
            return getChunkCreate({x, z});
        };

        const Chunk *getChunk(const types::Vec2i &coords) const;

        const Chunk *getChunk(const int x, const int z) const {
            return getChunk({x, z});
        };

        std::unique_ptr<Chunk> detachChunk(const types::Vec2i &coords, bool shouldInvalidateCoords = true);

        std::unique_ptr<Chunk> detachChunk(const int x, const int z, const bool shouldInvalidateCoords = true) {
            return detachChunk({x, z}, shouldInvalidateCoords);
        };

        void removeChunk(const types::Vec2i &coords);

        void removeChunk(const int x, const int z) {
            removeChunk({x, z});
        };

        void merge(std::unique_ptr<ChunkContainer> rhs);

        map_t<types::Vec2i, std::unique_ptr<Chunk> > &getChunks() {
            return mChunks;
        }

        const map_t<types::Vec2i, std::unique_ptr<Chunk> > &getChunks() const {
            return mChunks;
        }

        // todo replace with inbuilt bounds that gets updated
        types::Bounds3i getChunkBounds() const;

        ChunkContainer(const ChunkContainer &) = delete;
        ChunkContainer& operator=(const ChunkContainer&) = delete;

    protected:
        map_t<types::Vec2i, std::unique_ptr<Chunk> > mChunks;
    };
}

#endif //LODESTONE_CHUNKCONTAINER_H