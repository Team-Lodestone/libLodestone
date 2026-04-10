//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVELCHUNK_H
#define LODESTONE_LEVELCHUNK_H
#include "Lodestone.Level/chunk/Chunk.h"
#include <memory>

namespace lodestone::level::chunk {
    class LODESTONE_API LevelChunk : public Chunk {
      public:
        /** Creates a new LevelChunk with preallocated chunk section array for the given height */
        explicit LevelChunk(int height);

        // TODO we should replace height with some vec2i which includes floor maybe, and make it section based
        /** Creates a new LevelChunk under given parent container, with given coordinates and height
         *
         * @param height The total height in blocks of the LevelChunk (will be rounded to the nearest 16!!)
         * @param coords The coordinates of the chunk in level space
         * @param container The container that holds the chunk
         */
        LevelChunk(int height,
                   const coords::ChunkCoordinates &coords, ChunkContainer *container = nullptr);

        ChunkType type() override;

        [[nodiscard]] int getChunkHeight() const override;

        /** Checks if a section at the given section relative y level exists
         * (NOT BLOCK Y) */
        [[nodiscard]] bool hasSection(const coords::SectionCoordinates &sectionY) const;

        /** Gets/Creates a section at the given section relative y level (NOT
         * BLOCK Y) */
        section::Section *getSectionCreate(const coords::SectionCoordinates &sectionY) override;

        /** Creates a section at the given section relative y level (NOT BLOCK
         * Y) */
        [[nodiscard]] section::Section *getSection(const coords::SectionCoordinates &sectionY) const override;

        void calculateHeightmap() override;

        void calculateHeightmapAtColumn(int localX, int localZ, int startHeight) override;

        [[nodiscard]] const block::instance::BlockInstance &
        getBlock(const int localX, const int blockY, const int localZ) const override;

        void setBlock(block::instance::BlockInstance &&block, int localX, int y,
                      int localZ) override;

        void setBlockRaw(block::instance::BlockInstance &&block, int localX, int y,
                         int localZ) override;

        int getSectionCount() const override;

      protected:
        /** Chunk Sections
         *
         * Each chunk is made up of x amount of Sections, with each section
         * storing 16x16x16 blocks. This dictates the height of the chunk as
         * each section is 16 blocks in height.
         */
        std::vector<std::unique_ptr<section::Section>> m_sections;
    };
} // namespace lodestone::level::chunk

#endif // LODESTONE_LEVELCHUNK_H