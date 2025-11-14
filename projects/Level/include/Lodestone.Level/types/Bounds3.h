//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_BOUNDS_H
#define LODESTONE_BOUNDS_H

#include <Lodestone.Common/LodestoneCommon.h>
#include "Lodestone.Level/types/Vec3.h"

namespace lodestone::level::types {
    template <typename T>
    struct LODESTONE_API Bounds3 final : public lodestone::common::string::StringSerializable {
        Vec3<T> min;
        Vec3<T> max;

        constexpr std::string toString() const override {
            return std::format("Bounds3[min={},max={}]", min.toString(), max.toString());
        };

        constexpr Bounds3(const Vec3<T> &min, const Vec3<T> &max) : min(min), max(max) {
        };

        constexpr Bounds3(const int x0, const int y0, const int z0, const int x1, const int y1,
                           const int z1) : min({x0, y0, z0}), max({x1, y1, z1}) {
        };

        constexpr bool operator==(const Bounds3 &rhs) const {
            return min == rhs.min
                   && max == rhs.max;
        }

        constexpr Bounds3 operator+(const int v) const {
            return {
                min + v,
                max + v
            };
        }

        constexpr Bounds3 operator-(const int v) const {
            return {
                min - v,
                max - v
            };
        }

        constexpr Bounds3 operator*(const int v) const {
            return {
                min * v,
                max * v
            };
        }

        constexpr Bounds3 operator/(const int v) const {
            return {
                min / v,
                max / v
            };
        }

        constexpr Bounds3 operator+(const Bounds3 &rhs) const {
            return {
                rhs.min * min,
                rhs.max * max
            };
        }

        constexpr Bounds3 operator-(const Bounds3 &rhs) const {
            return {
                rhs.min - min,
                rhs.max - max
            };
        }


        constexpr Bounds3 operator*(const Bounds3 &rhs) const {
            return {
                rhs.min * min,
                rhs.max * max
            };
        }

        constexpr Bounds3 operator/(const Bounds3 &rhs) const {
            return {
                rhs.min / min,
                rhs.max / max
            };
        }

        constexpr bool contains(const Vec3<T> &vec) const noexcept {
            return vec.x >= min.x && vec.x <= max.x && vec.y >= min.y && vec.y <= max.y && vec.z >= min.z && vec.z <=
                   max.z;
        }

        constexpr bool empty() const noexcept {
            return max.x < min.x || max.y < min.y || max.z < min.z;
        }

        constexpr bool intersects(const Bounds3 &rhs) const noexcept {
            if (empty() || rhs.empty()) return false;

            return !(rhs.max.x < min.x || rhs.min.x > max.x || rhs.max.y < min.y || rhs.min.y > max.y || rhs.max.z < min
                     .z || rhs.min.z > max.z);
        }

        constexpr int getWidth() const noexcept { return empty() ? 0 : (max.x - min.x + 1); }
        constexpr int getHeight() const noexcept { return empty() ? 0 : (max.y - min.y); }
        constexpr int getLength() const noexcept { return empty() ? 0 : (max.z - min.z + 1); }
    };

    typedef Bounds3<int> Bounds3i;
    typedef Bounds3<float> Bounds3f;
    typedef Bounds3<double> Bounds3d;
}

#endif //LODESTONE_BOUNDS_H