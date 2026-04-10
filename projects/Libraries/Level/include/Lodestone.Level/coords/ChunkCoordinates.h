/** @file ChunkCoordinates.h
 *
 * @author DexrnZacAttack
 * @date 4/9/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_CHUNKCOORDINATES_H
#define LODESTONE_CHUNKCOORDINATES_H
#include <Lodestone.Common/Constants.h>
#include <Lodestone.Common/Defines.h>
#include <Lodestone.Common/util/Math.h>
#include "Lodestone.Level/types/Vec2.h"

namespace lodestone::level::coords {
    class ChunkCoordinates : public types::Vec2i {
    public:
        /**
         * Bits needed to shift right when shifting a block coordinate to a chunk coordinate.
         *
         * The base 2 logarithm of the chunk axis size is equivalent to the amount of bits
         * needed to shift the block coordinate into a chunk position.
         */
        static constexpr int CHUNK_BITS = common::util::Math::constevalLog(common::constants::CHUNK_AXIS_SIZE, 2);

        constexpr ChunkCoordinates(const int chunkX, const int chunkZ) : types::Vec2i(chunkX, chunkZ) {}
        constexpr ChunkCoordinates(const types::Vec2i &&coords) : types::Vec2i(std::move(coords)) {}
        constexpr ChunkCoordinates(const ChunkCoordinates &coords) : types::Vec2i(coords) {}

        static constexpr ChunkCoordinates fromBlockCoordinates(const signed_size_t blockX, const signed_size_t blockZ) {
            return ChunkCoordinates(blockToChunkCoord(blockX), blockToChunkCoord(blockZ));
        }

        constexpr int getX() const {
            return this->x;
        }

        constexpr int getZ() const {
            return this->y;
        }

        static constexpr int blockToChunkCoord(const signed_size_t blockCoord) {
            return blockCoord >> CHUNK_BITS;
        }

        static constexpr int blockToLocalChunkCoord(const signed_size_t blockX, size_t size) {
            return blockX & size;
        }

        static constexpr int blockToLocalChunkX(const signed_size_t blockX) {
            return blockToLocalChunkCoord(blockX, common::constants::CHUNK_WIDTH - 1);
        }

        static constexpr int blockToLocalChunkZ(const signed_size_t blockZ) {
            return blockToLocalChunkCoord(blockZ, common::constants::CHUNK_DEPTH - 1);
        }
    };
}

template <>
struct std::hash<lodestone::level::coords::ChunkCoordinates> {
    size_t
    operator()(const lodestone::level::coords::ChunkCoordinates &v) const noexcept {
        return std::hash<lodestone::level::types::Vec2i>()(v);
    }
};

#endif // LODESTONE_CHUNKCOORDINATES_H