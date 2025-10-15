//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#pragma once

namespace lodestone::level::chunk {
    struct ChunkCoords {
        int x, z;

        bool operator==(const ChunkCoords &rhs) const {
            return x == rhs.x && z == rhs.z;
        }

        ChunkCoords operator+(const int v) const {
            return {x + v, z + v};
        }

        ChunkCoords operator-(const int v) const {
            return {x - v, z - v};
        }

        ChunkCoords operator*(const int v) const {
            return {x * v, z * v};
        }

        ChunkCoords operator/(const int v) const {
            return {x / v, z / v};
        }

        ChunkCoords operator-(const ChunkCoords &rhs) const {
            return {x - rhs.x, z - rhs.z};
        }

        ChunkCoords operator+(const ChunkCoords &rhs) const {
            return {x + rhs.x, z + rhs.z};
        }

        ChunkCoords operator*(const ChunkCoords &rhs) const {
            return {x * rhs.x, z * rhs.z};
        }

        ChunkCoords operator/(const ChunkCoords &rhs) const {
            return {x / rhs.x, z / rhs.z};
        }
    };
}

template <>
struct std::hash<lodestone::level::chunk::ChunkCoords> {
    size_t operator()(const lodestone::level::chunk::ChunkCoords& v) const noexcept {
        return std::hash<int>()(v.x) ^ (std::hash<int>()(v.z) << 1);
    }
};
