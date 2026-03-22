//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_CHUNK_H
#define LODESTONE_CHUNK_H

#include "Lodestone.Level/block/instance/BlockInstance.h"
#include <Lodestone.Common/Constants.h>

#include "Lodestone.Level/block/BlockRegistry.h"
#include "Lodestone.Level/chunk/section/ImmutableSection.h"
#include "Lodestone.Level/types/Vec2.h"

namespace lodestone::level::chunk {
    class ChunkContainer;
}

namespace lodestone::level::chunk {
    class LODESTONE_LEVEL_API Chunk
        : public lodestone::common::string::StringSerializable {
      public:
        struct LODESTONE_LEVEL_API BlockmapEntry {
            const block::instance::BlockInstance *block;
            int16_t height;
        };

        Chunk();

        enum class LODESTONE_LEVEL_API ChunkType { LevelChunk, EmptyChunk };

        std::string toString() const override {
            if (this->m_coords.has_value())
                return std::format("Chunk[coords={}]", this->m_coords->toString());

            return std::format("Chunk");
        };

        explicit Chunk(const types::Vec2i &coords);

        Chunk(ChunkContainer *container, const types::Vec2i &coords);

        ~Chunk() override;

        virtual void calculateBlockmap() = 0;

        virtual void calculateBlockmapAtColumn(int x, int z, int height) = 0;

        /** Gets the height of the chunk in Sections, can be used for getting
         * section count */
        virtual int getChunkHeight() const = 0;

        /** Gets the height of the chunk in Blocks */
        int getChunkBlockHeight() const;

        virtual section::Section *getSection(int y) const = 0;

        virtual section::Section *getSectionCreate(int y) = 0;

        virtual const Chunk::BlockmapEntry *getBlockmap() const;

        virtual const block::instance::BlockInstance &getBlock(int x, int y,
                                                             int z) const = 0;

        /** Sets a block at the given X, Y, and Z coordinates.
         *
         * Also updates the blockmap and heightmap
         */
        virtual void setBlock(block::instance::BlockInstance &&blk, int x,
                              int y, int z) = 0;

        /** Sets a block at the given X, Y, and Z coordinates.
         *
         * Does not update blockmap
         */
        virtual void setBlockRaw(block::instance::BlockInstance &&blk,
                                 int x, int y, int z) = 0;

        virtual int16_t getHeightAt(int x, int z) const;

        virtual void setHeightAt(int16_t h, int x, int z);

        virtual const block::instance::BlockInstance *
        getBlockmapBlockAt(int x, int z) const;

        virtual void setBlockmapBlockAt(const block::instance::BlockInstance *b,
                                        int x, int z);

        virtual const BlockmapEntry &
            getBlockmapEntryAt(int x, int z) const;

        virtual void setBlockmapEntryAt(const BlockmapEntry &b,
                                        int x, int z);

        bool hasCoords() const;

        const std::optional<types::Vec2i> &getCoords();

        void setCoords(const std::optional<types::Vec2i> &coords);

        void invalidateCoords();

        void attach(ChunkContainer *container);

        void attach(ChunkContainer *container, const types::Vec2i &coords);

        void detach(bool shouldInvalidateCoords);

        bool isInContainer() const;

        ChunkContainer *getContainer() const;

        virtual int getSectionCount() const = 0;

        // todo: section iterator
      protected:
        std::optional<types::Vec2i> m_coords;
        /** The parent container which may hold the chunk */
        ChunkContainer *m_container;

        /** Blockmap
         *
         * Each x and z coord corresponds to the topmost block's state and it's height
         */
        BlockmapEntry *m_blockMap =
            new BlockmapEntry[common::constants::CHUNK_WIDTH *
                  common::constants::CHUNK_DEPTH] {};

        // map_t<Vec3i, TileEntity> mTileEntities;
        // map_t<Vec3i, Entity> mEntities;
    };
} // namespace lodestone::level::chunk

#endif // LODESTONE_CHUNK_H