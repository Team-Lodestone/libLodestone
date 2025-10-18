//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_EMPTYCHUNK_H
#define LODESTONE_EMPTYCHUNK_H
#include "Lodestone.Level/Chunk/Chunk.h"

namespace lodestone::level::chunk {
    class EmptyChunk : public Chunk {
    public:
        void calculateHeightmap() override;

        int getChunkHeight() const override;

        section::Section * getSection(int y) const override;

        block::state::BlockState * getBlock(int x, int y, int z) const override;

        section::Section * getSectionCreate(int y) override;

        void setBlock(block::state::BlockState &blk, int x, int y, int z) override;

        void setBlockRaw(block::state::BlockState &blk, int x, int y, int z) override;

        void setHeightAt(int16_t h, int x, int z) override;

        void calculateBlockmap() override;

        void setBlockmapBlockAt(block::state::BlockState *h, int x, int z) override;

        void calculateMaps() override;

        void calculateBlockmapAtColumn(int x, int z, int height) override;

        void calculateHeightmapAtColumn(int x, int z, int height) override;

        void calculateMapsAtColumn(int x, int z, int height) override;
    };
}

#endif //LODESTONE_EMPTYCHUNK_H
