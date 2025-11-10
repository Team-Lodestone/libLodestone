//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_BOUNDS_H
#define LODESTONE_BOUNDS_H

#include <Lodestone.Common/Lodestone.h>
#include "Lodestone.Level/types/Vec3i.h"

namespace lodestone::level::types {
    struct LODESTONE_API Bounds3i : public StringSerializable {
        Vec3i min;
        Vec3i max;

        constexpr std::string toString() const override {
            return std::format("Bounds3i[min={},max={}]", min.toString(), max.toString());
        };

        constexpr Bounds3i(const Vec3i &min, const Vec3i &max) : min(min), max(max) {};
        constexpr Bounds3i(const int x0, const int y0, const int z0, const int x1, const int y1, const int z1) : min({x0, y0, z0}), max({x1, y1, z1}) {};

        constexpr bool operator==(const Bounds3i &rhs) const {
            return min == rhs.min
                && max == rhs.max;
        }

        constexpr Bounds3i operator+(const int v) const {
            return {
                min + v,
                max + v
            };
        }

        constexpr Bounds3i operator-(const int v) const {
            return {
                min - v,
                max - v
            };
        }

        constexpr Bounds3i operator*(const int v) const {
            return {
                min * v,
                max * v
            };
        }

        constexpr Bounds3i operator/(const int v) const {
            return {
                min / v,
                max / v
            };
        }

        constexpr Bounds3i operator+(const Bounds3i &rhs) const {
            return {
                rhs.min * min,
                rhs.max * max
            };
        }

        constexpr Bounds3i operator-(const Bounds3i &rhs) const {
            return {
                rhs.min - min,
                rhs.max - max
            };
        }


        constexpr Bounds3i operator*(const Bounds3i &rhs) const {
            return {
                rhs.min * min,
                rhs.max * max
            };
        }

        constexpr Bounds3i operator/(const Bounds3i &rhs) const {
            return {
                rhs.min / min,
                rhs.max / max
            };
        }

        constexpr bool contains(const Vec3i &vec) const noexcept {
            return vec.x >= min.x && vec.x <= max.x && vec.y >= min.y && vec.y <= max.y && vec.z >= min.z && vec.z <= max.z;
        }

        constexpr bool empty() const noexcept {
            return max.x < min.x || max.y < min.y || max.z < min.z;
        }

        constexpr bool intersects(const Bounds3i &rhs) const noexcept {
            if (empty() || rhs.empty()) return false;

            return !(rhs.max.x < min.x || rhs.min.x > max.x || rhs.max.y < min.y || rhs.min.y > max.y || rhs.max.z < min.z || rhs.min.z > max.z);
        }

        constexpr int getWidth() const noexcept { return empty() ? 0 : (max.x - min.x + 1); }
        constexpr int getHeight() const noexcept { return empty() ? 0 : (max.y - min.y); }
        constexpr int getLength() const noexcept { return empty() ? 0 : (max.z - min.z + 1); }
    };
}

#endif //LODESTONE_BOUNDS_H