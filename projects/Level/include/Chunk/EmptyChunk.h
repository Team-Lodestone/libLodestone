//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_EMPTYCHUNK_H
#define LODESTONE_EMPTYCHUNK_H
#include "Chunk.h"

namespace lodestone::level::chunk {
    class EmptyChunk : public Chunk {
    public:
        const int16_t * calculateHeightmap() override;

        int getHeight() const override;

        section::Section * getSection(int y) const override;

        block::state::BlockState * getBlock(int x, int y, int z) const override;

        section::Section * getSectionCreate(int y) override;

        void setBlock(block::state::BlockState &blk, int x, int y, int z) override;
    };
}

#endif //LODESTONE_EMPTYCHUNK_H
