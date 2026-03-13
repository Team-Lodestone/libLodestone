//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_EMPTYCHUNK_H
#define LODESTONE_EMPTYCHUNK_H
#include "Lodestone.Level/chunk/Chunk.h"

namespace lodestone::level::chunk {
    class ImmutableChunk : public Chunk {
      public:
        static ImmutableChunk *getInstance();

        ImmutableChunk() : Chunk() {}

        explicit ImmutableChunk(const types::Vec2i &coords) : Chunk(coords) {}

        ImmutableChunk(ChunkContainer *container, const types::Vec2i &coords)
            : Chunk(container, coords) {}

        int getChunkHeight() const override;

        section::Section *getSection(int y) const override;

        const block::instance::BlockInstance &getBlock(int x, int y,
                                                     int z) const override;

        section::Section *getSectionCreate(int y) override;

        void setBlock(block::instance::BlockInstance &&blk, int x, int y,
                      int z) override;

        void setBlockRaw(block::instance::BlockInstance &&blk, int x, int y,
                         int z) override;

        void setHeightAt(int16_t h, int x, int z) override;

        void calculateBlockmap() override;

        void setBlockmapBlockAt(const block::instance::BlockInstance *h, int x,
                                int z) override;

        void setBlockmapEntryAt(const BlockmapEntry &b, int x, int z) override;

        void calculateBlockmapAtColumn(int x, int z, int height) override;

        int getSectionCount() const override;
    };
} // namespace lodestone::level::chunk

#endif // LODESTONE_EMPTYCHUNK_H