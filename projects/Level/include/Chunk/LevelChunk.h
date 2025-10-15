//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVELCHUNK_H
#define LODESTONE_LEVELCHUNK_H
#include "Chunk.h"

namespace lodestone::level::chunk {
    class LODESTONE_API LevelChunk : public Chunk {
    public:
        LevelChunk(int height);

        int getHeight() const override {
            return mSections.size() % 16;
        };

        section::Section *getSection(const int y) const override {
            // if non-existent, return fake one
            if (mSections.size() >= (y/16))
                return section::EmptySection::sInstance;

            return mSections[y/16];
        }

        block::state::BlockState *getBlock(const int x, const int y, const int z) const override {
            return getSection(y)->getBlock(x % 16, y % 16, z % 16);
        }

        const int16_t *calculateHeightmap() override;
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
