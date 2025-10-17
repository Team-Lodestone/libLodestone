//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVELCHUNK_H
#define LODESTONE_LEVELCHUNK_H
#include "Chunk.h"
#include "Section/LevelSection.h"

namespace lodestone::level::chunk {
    class LODESTONE_API LevelChunk : public Chunk {
    public:
        LevelChunk(int height);

        int getHeight() const override {
            return mSections.size();
        };

        /** Checks if a section at the given section relative y level exists (NOT BLOCK Y) */
        bool hasSection(const int y) const {
            if (mSections.size() > y)
                return (mSections[y] != nullptr);
            return false;
        }

        /** Creates a section at the given section relative y level (NOT BLOCK Y) */
        section::Section *getSection(const int y) const override {
            // if non-existent, return fake one
            if (!hasSection(y))
                return section::EmptySection::sInstance;

            return mSections[y];
        }

        // todo: just overload w/o const?
        /** Gets/Creates a section at the given section relative y level (NOT BLOCK Y) */
        section::Section *getSectionCreate(const int y) override {
            if (!hasSection(y)) mSections[y] = new section::LevelSection();

            return mSections[y];
        }

        block::state::BlockState *getBlock(const int x, const int y, const int z) const override {
            return getSection(y / 16)->getBlock(x, y % 16, z);
        }

        const int16_t *calculateHeightmap() override;

        void setBlock(block::state::BlockState &blk, int x, int y, int z) override;

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
