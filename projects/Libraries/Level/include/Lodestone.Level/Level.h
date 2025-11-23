//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVEL_H
#define LODESTONE_LEVEL_H
#include <memory>
#include <unordered_map>

#include "Lodestone.Level/chunk/Chunk.h"
#include "Lodestone.Level/chunk/ChunkContainer.h"
#include "Lodestone.Level/types/Bounds3.h"
#include "Lodestone.Level/types/Vec2.h"

namespace lodestone::level::world {
    class World;
}

namespace lodestone::level {
    /** A level, holds Chunks.
     *
     * @see Chunk
     */
    class LODESTONE_API Level : public chunk::ChunkContainer {
      public:
        bool isChunkInBounds(const types::Vec2i &coords) override;

        block::properties::BlockProperties *
        getBlock(signed_size_t x, signed_size_t y, signed_size_t z);

        void setBlock(block::properties::BlockProperties &&blk, signed_size_t x,
                      signed_size_t y, signed_size_t z);

        void setBlockRaw(block::properties::BlockProperties &&blk,
                         signed_size_t x, signed_size_t y, signed_size_t z);

        void setBlockCreate(block::properties::BlockProperties &&blk,
                            signed_size_t x, signed_size_t y, signed_size_t z,
                            int height = 256);

        void setBlockCreateRaw(block::properties::BlockProperties &&blk,
                               signed_size_t x, signed_size_t y,
                               signed_size_t z, int height = 256);

        int16_t getHeightAt(signed_size_t x, signed_size_t z) const;

        void setHeightAt(int16_t h, signed_size_t x, signed_size_t z);

        void setHeightAtCreate(int16_t h, signed_size_t x, signed_size_t z,
                               int height = 256);

        const block::properties::BlockProperties *
        getBlockmapBlockAt(signed_size_t x, signed_size_t z) const;

        void setBlockmapBlockAt(block::properties::BlockProperties *b,
                                signed_size_t x, signed_size_t z);

        void setBlockmapBlockAtCreate(block::properties::BlockProperties *b,
                                      signed_size_t x, signed_size_t z,
                                      int height = 256);

        size_t getBlockCount() const;

        types::Bounds3i getBlockBounds() const;

        world::World *getWorld() const;
        bool isInWorld() const;
        void setWorld(world::World *world);

        types::Vec3i generateSpawnPos(unsigned int radius = 21) const;
        virtual const level::types::Vec3i &getSpawnPos() const;
        virtual void setSpawnPos(const level::types::Vec3i &spawnPos);

      private:
        level::types::Vec3i mSpawnPos{0, 64, 0};
        world::World *mWorld = nullptr;
    };
} // namespace lodestone::level

#endif // LODESTONE_LEVEL_H