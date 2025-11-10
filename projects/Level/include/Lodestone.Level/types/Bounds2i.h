//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_BOUNDS2I_H
#define LODESTONE_BOUNDS2I_H

#include <format>
#include <Lodestone.Common/Lodestone.h>

#include "Lodestone.Common/String/StringSerializable.h"
#include "Lodestone.Level/types/Vec2i.h"

namespace lodestone::level::types {
    struct LODESTONE_API Bounds2i : public StringSerializable {
        Vec2i min;
        Vec2i max;

        constexpr std::string toString() const override {
            return std::format("Bounds2i[min={},max={}]", min.toString(), max.toString());
        };

        constexpr Bounds2i(const Vec2i &min, const Vec2i &max) : min(min), max(max) {};
        constexpr Bounds2i(const int x0, const int z0, const int x1, const int z1) : min({x0, z0}), max({x1, z1}) {};

        constexpr bool operator==(const Bounds2i &rhs) const {
            return min == rhs.min
                && max == rhs.max;
        }

        constexpr Bounds2i operator+(const int v) const {
            return {
                min + v,
                max + v
            };
        }

        constexpr Bounds2i operator-(const int v) const {
            return {
                min - v,
                max - v
            };
        }

        constexpr Bounds2i operator*(const int v) const {
            return {
                min * v,
                max * v
            };
        }

        constexpr Bounds2i operator/(const int v) const {
            return {
                min / v,
                max / v
            };
        }

        constexpr Bounds2i operator+(const Bounds2i &rhs) const {
            return {
                rhs.min * min,
                rhs.max * max
            };
        }

        constexpr Bounds2i operator-(const Bounds2i &rhs) const {
            return {
                rhs.min - min,
                rhs.max - max
            };
        }

        constexpr Bounds2i operator*(const Bounds2i &rhs) const {
            return {
                rhs.min * min,
                rhs.max * max
            };
        }

        constexpr Bounds2i operator/(const Bounds2i &rhs) const {
            return {
                rhs.min / min,
                rhs.max / max
            };
        }

        constexpr bool contains(const Vec2i &vec) const noexcept {
            return vec.x >= min.x && vec.x <= max.x && vec.z >= min.z && vec.z <= max.z;
        }

        constexpr bool empty() const noexcept {
            return max.x < min.x || max.z < min.z;
        }

        constexpr bool intersects(const Bounds2i &rhs) const noexcept {
            if (empty() || rhs.empty()) return false;

            return !(rhs.max.x < min.x || rhs.min.x > max.x || rhs.max.z < min.z || rhs.min.z > max.z);
        }

        constexpr int getWidth() const noexcept { return empty() ? 0 : (max.x - min.x + 1); }
        constexpr int getLength() const noexcept {
            return empty()
            ? 0
            : (max.z - min.z + 1);
        }
    };
}

#endif //LODESTONE_BOUNDS2I_H