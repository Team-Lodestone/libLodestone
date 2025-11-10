//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_VEC3I_H
#define LODESTONE_VEC3I_H
#include <Lodestone.Common/Defines.h>

namespace lodestone::level::types {
    struct LODESTONE_API Vec3i : public StringSerializable {
        int x, y, z;

        constexpr Vec3i(const int x, const int y, const int z) : x(x), y(y), z(z) {}

        constexpr std::string toString() const override {
            return std::format("Vec3i[x={},y={},z={}]", x, y, z);
        };

        constexpr operator int*() { return &x; }
        constexpr operator const int*() const { return &x; }

        constexpr bool operator==(const Vec3i &rhs) const {
            return x == rhs.x
                && y == rhs.y
                && z == rhs.z;
        }

        constexpr Vec3i operator+(const int v) const {
            return {
                x + v,
                y + v,
                z + v
            };
        }

        constexpr Vec3i operator-(const int v) const {
            return {
                x - v,
                y - v,
                z - v
            };
        }

        constexpr Vec3i operator*(const int v) const {
            return {
                x * v,
                y * v,
                z * v
            };
        }

        constexpr Vec3i operator/(const int v) const {
            return {
                x / v,
                y / v,
                z / v
            };
        }

        constexpr Vec3i operator+(const Vec3i &rhs) const {
            return {
                x + rhs.x,
                y + rhs.y,
                z + rhs.z
            };
        }

        constexpr Vec3i operator-(const Vec3i &rhs) const {
            return {
                x - rhs.x,
                x - rhs.y,
                z - rhs.z
            };
        }

        constexpr Vec3i operator*(const Vec3i &rhs) const {
            return {
                x * rhs.x,
                y * rhs.y,
                z * rhs.z
            };
        }

        constexpr Vec3i operator/(const Vec3i &rhs) const {
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