//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVEL_H
#define LODESTONE_LEVEL_H
#include <Lodestone.Common/util/Util.h>

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
    class LODESTONE_LEVEL_API Level : public chunk::ChunkContainer {
      public:
        bool isChunkInBounds(const types::Vec2i &coords) override;

        const block::instance::BlockInstance &
        getBlock(signed_size_t x, signed_size_t y, signed_size_t z) const;

        void setBlock(block::instance::BlockInstance &&blk, signed_size_t x,
                      signed_size_t y, signed_size_t z);

        void setBlockRaw(block::instance::BlockInstance &&blk,
                         signed_size_t x, signed_size_t y, signed_size_t z);

        void setBlockCreate(block::instance::BlockInstance &&blk,
                            signed_size_t x, signed_size_t y, signed_size_t z,
                            int height = 256);

        void setBlockCreateRaw(block::instance::BlockInstance &&blk,
                               signed_size_t x, signed_size_t y,
                               signed_size_t z, int height = 256);

        int16_t getHeightAt(signed_size_t x, signed_size_t z) const;

        void setHeightAt(int16_t h, signed_size_t x, signed_size_t z);

        void setHeightAtCreate(int16_t h, signed_size_t x, signed_size_t z,
                               int height = 256);

        const block::instance::BlockInstance &
        getBlockmapBlockAt(signed_size_t x, signed_size_t z) const;

        void setBlockmapBlockAt(const block::instance::BlockInstance &b,
                                signed_size_t x, signed_size_t z);

        void setBlockmapBlockAtCreate(const block::instance::BlockInstance &b,
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

        virtual std::uint64_t getCreationTime() const;

        virtual void setCreationTime(std::uint64_t creationTime);
    private:
        level::types::Vec3i m_spawnPos{0, 64, 0};
        world::World *m_world = nullptr;

        std::uint64_t m_creationTime = lodestone::common::util::Util::getCurrentTimeMillis();
    };
} // namespace lodestone::level

#endif // LODESTONE_LEVEL_H