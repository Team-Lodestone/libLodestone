//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVELCHUNK_H
#define LODESTONE_LEVELCHUNK_H
#include "Lodestone.Level/chunk/Chunk.h"
#include "Lodestone.Level/chunk/section/LevelSection.h"
#include <memory>

namespace lodestone::level::chunk {
    class LODESTONE_LEVEL_API LevelChunk : public Chunk {
      public:
        /** Creates a new LevelChunk with chunk sections for the given height */
        explicit LevelChunk(int height);

        LevelChunk(int height, const types::Vec2i &coords);

        LevelChunk(int height, ChunkContainer *container,
                   const types::Vec2i &coords);

        [[nodiscard]] int getChunkHeight() const override;

        /** Checks if a section at the given section relative y level exists
         * (NOT BLOCK Y) */
        [[nodiscard]] bool hasSection(const int y) const;

        /** Gets/Creates a section at the given section relative y level (NOT
         * BLOCK Y) */
        section::Section *getSectionCreate(const int y) override;

        /** Creates a section at the given section relative y level (NOT BLOCK
         * Y) */
        [[nodiscard]] section::Section *getSection(const int y) const override;

        void calculateBlockmap() override;

        void calculateBlockmapAtColumn(int x, int z, int height) override;

        [[nodiscard]] const block::instance::BlockInstance &
        getBlock(const int x, const int y, const int z) const override;

        void setBlock(block::instance::BlockInstance &&blk, int x, int y,
                      int z) override;

        void setBlockRaw(block::instance::BlockInstance &&blk, int x, int y,
                         int z) override;

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