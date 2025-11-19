//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_CHUNK_H
#define LODESTONE_CHUNK_H

#include "Lodestone.Level/block/properties/BlockProperties.h"
#include <Lodestone.Common/Constants.h>

#include "Lodestone.Level/block/BlockRegistry.h"
#include "Lodestone.Level/chunk/section/EmptySection.h"
#include "Lodestone.Level/types/Vec2.h"

namespace lodestone::level::chunk {
    class ChunkContainer;
}

namespace lodestone::level::chunk {
    class LODESTONE_API Chunk : public lodestone::common::string::StringSerializable {
    public:
        Chunk();

        enum class ChunkType {
            LevelChunk,
            EmptyChunk
        };

        constexpr std::string toString() const override {
            if (this->mCoords.has_value())
                return (common::string::OperatorStringBuilder(typeid(*this)))
                    .addField("coords", this->mCoords->toString())
                    ->toString();

            return (common::string::OperatorStringBuilder(typeid(*this))).toString();
        };

        explicit Chunk(const types::Vec2i &coords);

        Chunk(ChunkContainer *container, const types::Vec2i &coords);

        ~Chunk() override;

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

        virtual const block::properties::BlockProperties **getBlockmap() const;

        virtual block::properties::BlockProperties *getBlock(int x, int y, int z) const = 0;

        /** Sets a block at the given X, Y, and Z coordinates.
         *
         * Also updates the blockmap and heightmap
         */
        virtual void setBlock(block::properties::BlockProperties &&blk, int x, int y, int z) = 0;

        /** Sets a block at the given X, Y, and Z coordinates.
         *
         * Does not update blockmap nor heightmap
         */
        virtual void setBlockRaw(block::properties::BlockProperties &&blk, int x, int y, int z) = 0;

        virtual int16_t getHeightAt(int x, int z) const;

        virtual void setHeightAt(int16_t h, int x, int z);

        virtual const block::properties::BlockProperties *getBlockmapBlockAt(int x, int z) const;

        virtual void setBlockmapBlockAt(block::properties::BlockProperties *b, int x, int z);

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
        int16_t *mHeightmap = new int16_t[common::constants::CHUNK_WIDTH * common::constants::CHUNK_DEPTH]{};
        /** Blockmap
         *
         * Each x and z coord corresponds to the topmost block's state
         */
        block::properties::BlockProperties **mBlockmap = new block::properties::BlockProperties *[
            common::constants::CHUNK_WIDTH * common::constants::CHUNK_DEPTH]{};

        // map_t<Vec3i, TileEntity> mTileEntities;
        // map_t<Vec3i, Entity> mEntities;
    };
}

#endif //LODESTONE_CHUNK_H