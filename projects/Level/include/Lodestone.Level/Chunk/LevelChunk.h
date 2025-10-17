//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVELCHUNK_H
#define LODESTONE_LEVELCHUNK_H
#include "Lodestone.Level/Chunk/Chunk.h"
#include "Lodestone.Level/Chunk/Section/LevelSection.h"

namespace lodestone::level::chunk {
    class LODESTONE_API LevelChunk : public Chunk {
    public:
        /** Creates a new LevelChunk with chunk sections for the given height */
        LevelChunk(int height);

        int getChunkHeight() const override;

        /** Checks if a section at the given section relative y level exists (NOT BLOCK Y) */
        bool hasSection(const int y) const;

        /** Gets/Creates a section at the given section relative y level (NOT BLOCK Y) */
        section::Section *getSectionCreate(const int y) override;
        /** Creates a section at the given section relative y level (NOT BLOCK Y) */
        section::Section *getSection(const int y) const override;

        void calculateHeightmap() override;

        block::state::BlockState *getBlock(const int x, const int y, const int z) const override;

        void setBlock(block::state::BlockState &blk, int x, int y, int z) override;
        void setBlockRaw(block::state::BlockState &blk, int x, int y, int z) override;

    protected:
        /** Chunk Sections
         *
         * Each chunk is made up of x amount of Sections, with each section storing 16x16x16 blocks.
         * This dictates the height of the chunk as each section is 16 blocks in height.
         */
        std::vector<section::Section*> mSections;
    };
}

#endif //LODESTONE_LEVELCHUNK_H
