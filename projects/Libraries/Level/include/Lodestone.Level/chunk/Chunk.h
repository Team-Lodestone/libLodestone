//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_CHUNK_H
#define LODESTONE_CHUNK_H

#include <Lodestone.Common/util/IHasDerivedTypes.h>
#include "Lodestone.Level/block/instance/BlockInstance.h"
#include <Lodestone.Common/Constants.h>

#include "Lodestone.Level/block/BlockRegistry.h"
#include "Lodestone.Level/chunk/section/ImmutableSection.h"
#include "Lodestone.Level/coords/ChunkCoordinates.h"
#include "Lodestone.Level/coords/SectionCoordinates.h"
#include "Lodestone.Level/properties/ReflectiveProperties.h"
#include "Lodestone.Level/types/Vec2.h"

namespace lodestone::level::chunk {
    class ChunkContainer;
}

namespace lodestone::level::chunk {
    enum class ChunkType { LevelChunk, ImmutableChunk };

    class LODESTONE_API Chunk
        : public lodestone::common::string::StringSerializable, public properties::ReflectiveProperties, public common::util::IHasDerivedTypes<ChunkType> {
      public:
        static constexpr int TOTAL_CHUNK_2D_SIZE = common::constants::CHUNK_WIDTH * common::constants::CHUNK_DEPTH;

        Chunk();

        std::string toString() const override {
            if (this->m_coords.has_value())
                return std::format("Chunk[coords={}]", this->m_coords->toString());

            return std::format("Chunk");
        };

        Chunk(const coords::ChunkCoordinates &coords, ChunkContainer *container = nullptr);

        ~Chunk() override;

        virtual void calculateHeightmap() = 0;

        virtual void calculateHeightmapAtColumn(int localX, int localZ, int height) = 0;

        /** Gets the height of the chunk in Sections, can be used for getting
         * section count */
        virtual int getChunkHeight() const = 0;

        /** Gets the height of the chunk in Blocks */
        int getChunkBlockHeight() const;

        virtual section::Section *getSection(const coords::SectionCoordinates &sectionY) const = 0;

        virtual section::Section *getSectionCreate(const coords::SectionCoordinates &sectionY) = 0;

        virtual section::Section *getSectionFromBlockY(const signed_size_t &blockY) const;

        virtual section::Section *getSectionFromBlockYCreate(const signed_size_t &blockY);

        virtual const int16_t *getHeightmap() const;

        virtual const block::instance::BlockInstance &getBlock(int localX, int y,
                                                             int localZ) const = 0;

        /** Sets a block at the given X, Y, and Z coordinates.
         *
         * Also updates the blockmap and heightmap
         */
        virtual void setBlock(block::instance::BlockInstance &&block, int localX,
                              int y, int localZ) = 0;

        /** Sets a block at the given X, Y, and Z coordinates.
         *
         * Does not update blockmap
         */
        virtual void setBlockRaw(block::instance::BlockInstance &&block,
                                 int localX, int y, int localZ) = 0;

        virtual int16_t getHeightAt(int localX, int localZ) const;

        virtual void setHeightAt(int16_t height, int localX, int localZ);

        virtual const block::instance::BlockInstance &
        getBlockAtHeight(int localX, int localZ) const;

        virtual void setBlockAtHeight(block::instance::BlockInstance &&block,
                                        int localX, int localZ);

        bool hasCoords() const;

        const std::optional<coords::ChunkCoordinates> &getCoords() const;

        void setCoords(const std::optional<coords::ChunkCoordinates> &coords);

        void invalidateCoords();

        void attach(ChunkContainer *container);

        void attach(ChunkContainer *container, const coords::ChunkCoordinates &coords);

        void detach(bool shouldInvalidateCoords);

        bool isInContainer() const;

        ChunkContainer *getContainer() const;

        virtual int getSectionCount() const = 0;

        virtual void postProcess();

        // todo: section iterator
      protected:
        std::optional<coords::ChunkCoordinates> m_coords;
        /** The parent container which may hold the chunk */
        ChunkContainer *m_container;

        // TODO floor

        /** Heightmap
         *
         * Each x and z coord corresponds to the Y coordinate above the topmost block(height)
         */
        int16_t *m_heightMap = new int16_t[TOTAL_CHUNK_2D_SIZE] {};

        // TODO or maybe these should be held in Level with references to them from Chunk
        // map_t<Vec3i, TileEntity> mTileEntities;
        // map_t<Vec3i, Entity> mEntities;
    };
} // namespace lodestone::level::chunk

#endif // LODESTONE_CHUNK_H