//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_CHUNK_H
#define LODESTONE_CHUNK_H

#include "Lodestone.Level/block/state/BlockState.h"
#include <Lodestone.Common/Constants.h>

#include "Lodestone.Level/block/BlockRegistry.h"
#include "Lodestone.Level/chunk/section/EmptySection.h"
#include "Lodestone.Level/types/Vec2i.h"

namespace lodestone::level::chunk {
    class ChunkContainer;
}

namespace lodestone::level::chunk {
    class LODESTONE_API Chunk : public StringSerializable {
    public:
        Chunk();

        enum class ChunkType {
            LevelChunk,
            EmptyChunk
        };

        constexpr std::string toString() const override {
            if (this->mCoords.has_value())
                return std::format("Chunk[coords={}]", mCoords->toString());

            return std::format("Chunk");
        };

        explicit Chunk(const types::Vec2i &coords);
        Chunk(ChunkContainer *container, const types::Vec2i &coords);
        
        virtual ~Chunk() = default;

        virtual void calculateBlockmap() = 0;
        virtual void calculateHeightmap() = 0;
        virtual void calculateMaps() = 0;

        virtual void calculateBlockmapAtColumn(int x, int z, int height) = 0;
        virtual void calculateHeightmapAtColumn(int x, int z, int height) = 0;
        virtual void calculateMapsAtColumn(int x, int z, int height) = 0;

        /** Gets the height of the chunk in Sections, can be used for getting section count */
        virtual int getChunkHeight() const = 0;
        /** Gets the height of the chunk in Blocks */
        int getChunkBlockHeight() const;

        virtual section::Section *getSection(int y) const = 0;
        virtual section::Section *getSectionCreate(int y) = 0;

        virtual const int16_t *getHeightmap() const;
        virtual const block::state::BlockState **getBlockmap() const;

        virtual block::state::BlockState *getBlock(int x, int y, int z) const = 0;
        /** Sets a block at the given X, Y, and Z coordinates.
         *
         * Also updates the blockmap and heightmap
         */
        virtual void setBlock(block::state::BlockState &blk, int x, int y, int z) = 0;
        /** Sets a block at the given X, Y, and Z coordinates.
         *
         * Does not update blockmap nor heightmap
         */
        virtual void setBlockRaw(block::state::BlockState &blk, int x, int y, int z) = 0;

        virtual int16_t getHeightAt(int x, int z) const;
        virtual void setHeightAt(int16_t h, int x, int z);

        virtual const block::state::BlockState *getBlockmapBlockAt(int x, int z) const;
        virtual void setBlockmapBlockAt(block::state::BlockState *b, int x, int z);

        bool hasCoords() const;
        const std::optional<types::Vec2i> &getCoords();
        void setCoords(const types::Vec2i &coords);
        void invalidateCoords();

        void attach(ChunkContainer *container);
        void attach(ChunkContainer *container, const types::Vec2i &coords);
        void detach(bool shouldInvalidateCoords);

        bool isInContainer() const;

        ChunkContainer *getContainer() const;
        // todo: section iterator
    protected:
        std::optional<types::Vec2i> mCoords;
        /** The parent container which may hold the chunk */
        ChunkContainer *mContainer;

        /** Heightmap
         *
         * Each x and z coord corresponds to the topmost block's height
         */
        int16_t *mHeightmap = new int16_t[constants::CHUNK_WIDTH* constants::CHUNK_DEPTH]{};
        /** Blockmap
         *
         * Each x and z coord corresponds to the topmost block's state
         */
        block::state::BlockState **mBlockmap = new block::state::BlockState*[constants::CHUNK_WIDTH* constants::CHUNK_DEPTH]{};

        // gtl::flat_hash_map<Vec3i, TileEntity> mTileEntities;
        // gtl::flat_hash_map<Vec3i, Entity> mEntities;
    };
}

#endif //LODESTONE_CHUNK_H
