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
    /** A level holds Chunks.
     *
     * @see Chunk
     */
    class LODESTONE_API Level : public chunk::ChunkContainer {
    public:
        //region Blocks
        const block::instance::BlockInstance &getBlock(signed_size_t blockX, signed_size_t blockY, signed_size_t blockZ) const;
        void setBlock(block::instance::BlockInstance &&block, signed_size_t blockX, signed_size_t blockY, signed_size_t blockZ);
        void setBlockRaw(block::instance::BlockInstance &&block, signed_size_t blockX, signed_size_t blockY, signed_size_t blockZ);
        void setBlockCreate(block::instance::BlockInstance &&block, signed_size_t blockX, signed_size_t blockY, signed_size_t blockZ, int height = 256);

        void setBlockCreateRaw(block::instance::BlockInstance &&block, signed_size_t blockX, signed_size_t blockY, signed_size_t blockZ, int height = 256);
        //endregion

        //region Heightmap
        int16_t getHeightAt(signed_size_t blockX, signed_size_t blockZ) const;
        void setHeightAt(int16_t height, signed_size_t blockX, signed_size_t blockZ);
        void setHeightAtCreate(int16_t height, signed_size_t blockX, signed_size_t blockZ, int newChunkHeight = 256);
        //endregion

        //region Blockmap
        const block::instance::BlockInstance& getBlockAtHeight(signed_size_t blockX, signed_size_t blockZ) const;
        void setBlockAtHeight(block::instance::BlockInstance &&block, signed_size_t blockX, signed_size_t blockZ);
        //endregion

        //region Extra
        bool isChunkInBounds(const coords::ChunkCoordinates &chunkCoordinates) override;
        size_t getBlockCount() const;
        types::Bounds3i getBlockBounds() const;

        //region World
        world::World *getWorld() const;
        bool isInWorld() const;
        void setWorld(world::World *world);

        //endregion

        //region Spawnpoint
        types::Vec3i generateSpawnPos(unsigned int radius = 21) const;
        virtual const level::types::Vec3i &getSpawnPos() const;
        virtual void setSpawnPos(const level::types::Vec3i &spawnPos);

        //endregion

        //region Creation Time
        virtual std::uint64_t getCreationTime() const;
        virtual void setCreationTime(std::uint64_t creationTime);

        //endregion

        //endregion
    private:
        level::types::Vec3i m_spawnPos{0, 64, 0};
        world::World *m_world = nullptr;

        std::uint64_t m_creationTime = lodestone::common::util::Util::getCurrentTimeMillis();
    };
} // namespace lodestone::level

#endif // LODESTONE_LEVEL_H