//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_VEC3I_H
#define LODESTONE_VEC3I_H
#include <Lodestone.Common/Defines.h>

namespace lodestone::level::types {
    struct LODESTONE_API Vec3i {
        int x, y, z;

        bool operator==(const Vec3i &rhs) const {
            return x == rhs.x
                && y == rhs.y
                && z == rhs.z;
        }

        Vec3i operator+(const int v) const {
            return {
                x + v,
                y + v,
                z + v
            };
        }

        Vec3i operator-(const int v) const {
            return {
                x - v,
                y - v,
                z - v
            };
        }

        Vec3i operator*(const int v) const {
            return {
                x * v,
                y * v,
                z * v
            };
        }

        Vec3i operator/(const int v) const {
            return {
                x / v,
                y / v,
                z / v
            };
        }

        Vec3i operator+(const Vec3i &rhs) const {
            return {
                x + rhs.x,
                y + rhs.y,
                z + rhs.z
            };
        }

        Vec3i operator-(const Vec3i &rhs) const {
            return {
                x - rhs.x,
                x - rhs.y,
                z - rhs.z
            };
        }

        Vec3i operator*(const Vec3i &rhs) const {
            return {
                x * rhs.x,
                y * rhs.y,
                z * rhs.z
            };
        }

        Vec3i operator/(const Vec3i &rhs) const {
            return {
                x / rhs.x,
                y / rhs.y,
                z / rhs.z
            };
        }
    };
}

template <>
struct std::hash<lodestone::level::types::Vec3i> {
    size_t operator()(const lodestone::level::types::Vec3i& v) const noexcept {
        return std::hash<int>()(v.x)
            ^ (std::hash<int>()(v.y) << 1)
            ^ (std::hash<int>()(v.z) << 2);
    }
};

#endif