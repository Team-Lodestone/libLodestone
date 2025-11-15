//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVEL_H
#define LODESTONE_LEVEL_H
#include <unordered_map>
#include <memory>

#include "Lodestone.Level/chunk/ChunkContainer.h"
#include "Lodestone.Level/chunk/Chunk.h"
#include "Lodestone.Level/types/Vec2.h"
#include "Lodestone.Level/types/Bounds3.h"

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

        block::properties::BlockProperties *getBlock(size_t x, size_t y, size_t z);

        void setBlock(block::properties::BlockProperties &&blk, size_t x, size_t y, size_t z);

        void setBlockRaw(block::properties::BlockProperties &&blk, size_t x, size_t y, size_t z);

        void setBlockCreate(block::properties::BlockProperties &&blk, size_t x, size_t y, size_t z, int height = 256);

        void setBlockCreateRaw(block::properties::BlockProperties &&blk, size_t x, size_t y, size_t z, int height = 256);

        int16_t getHeightAt(int x, int z) const;

        void setHeightAt(int16_t h, int x, int z);

        void setHeightAtCreate(int16_t h, size_t x, size_t z, int height = 256);

        const block::properties::BlockProperties *getBlockmapBlockAt(int x, int z) const;

        void setBlockmapBlockAt(block::properties::BlockProperties *b, int x, int z);

        void setBlockmapBlockAtCreate(block::properties::BlockProperties *b, int x, int z, int height = 256);

        size_t getBlockCount() const;

        types::Bounds3i getBlockBounds() const;

        world::World *getWorld() const;
        bool isInWorld() const;
        void setWorld(world::World *world);

        types::Vec3i generateSpawnPos(unsigned int radius = 21);
        virtual const level::types::Vec3i & getSpawnPos() const;
        virtual void setSpawnPos(const level::types::Vec3i &spawnPos);
    private:
        level::types::Vec3i mSpawnPos{0, 64, 0};
        world::World *mWorld = nullptr;
    };
}

#endif //LODESTONE_LEVEL_H