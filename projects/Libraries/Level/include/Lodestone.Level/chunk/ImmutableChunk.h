//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_EMPTYCHUNK_H
#define LODESTONE_EMPTYCHUNK_H
#include "Lodestone.Level/chunk/Chunk.h"

namespace lodestone::level::chunk {
    class LODESTONE_API ImmutableChunk : public Chunk {
      public:
        static ImmutableChunk *getInstance();

        ImmutableChunk() = default;

        explicit ImmutableChunk(const coords::ChunkCoordinates &coords, ChunkContainer *container = nullptr)
            : Chunk(coords, container) {}

        ChunkType type() override;

        int getChunkHeight() const override;

        section::Section *getSection(const coords::SectionCoordinates &sectionY) const override;

        const block::instance::BlockInstance &getBlock(int localX, int sectionY,
                                                     int localZ) const override;

        section::Section *getSectionCreate(const coords::SectionCoordinates &sectionY) override;

        void setBlock(block::instance::BlockInstance &&block, int localX, int y,
                      int localZ) override;

        void setBlockRaw(block::instance::BlockInstance &&block, int localX, int y,
                         int localZ) override;

        void setHeightAt(int16_t height, int localX, int localZ) override;

        void calculateHeightmap() override;

        void calculateHeightmapAtColumn(int localX, int localZ, int height) override;

        int getSectionCount() const override;

        int16_t getHeightAt(int localX, int localZ) const override;

        const block::instance::BlockInstance & getBlockAtHeight(int localX, int localZ) const override;

        void setBlockAtHeight(block::instance::BlockInstance &&block, int localX, int localZ) override;
    };
} // namespace lodestone::level::chunk

#endif // LODESTONE_EMPTYCHUNK_H