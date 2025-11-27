//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_VEC2I_H
#define LODESTONE_VEC2I_H

#include <Lodestone.Common/string/StringSerializable.h>
#include <format>

namespace lodestone::level::types {
    template <typename T>
    struct Vec2 final : common::string::StringSerializable {
        T x, z;

        constexpr Vec2(const T x, const T z) : x(x), z(z) {}

        constexpr operator T *() { return &x; }
        constexpr operator const T *() const { return &x; }

        constexpr bool operator==(const Vec2 &rhs) const {
            return x == rhs.x && z == rhs.z;
        }

        constexpr Vec2 operator+(const T v) const { return {x + v, z + v}; }

        constexpr Vec2 operator-(const T v) const { return {x - v, z - v}; }

        constexpr Vec2 operator*(const T v) const { return {x * v, z * v}; }

        constexpr Vec2 operator/(const T v) const { return {x / v, z / v}; }

        constexpr Vec2 operator+(const Vec2 &rhs) const {
            return {x + rhs.x, z + rhs.z};
        }

        constexpr Vec2 operator-(const Vec2 &rhs) const {
            return {x - rhs.x, z - rhs.z};
        }

        constexpr Vec2 operator*(const Vec2 &rhs) const {
            return {x * rhs.x, z * rhs.z};
        }

        constexpr Vec2 operator/(const Vec2 &rhs) const {
            return {x / rhs.x, z / rhs.z};
        }

        constexpr std::string toString() const override {
            return std::format("Vec2[x={}, z={}]", x, z);
        };

        template <typename V> Vec2<V> asVec() const {
            return Vec2<V>(static_cast<V>(x), static_cast<V>(z));
        }
    };

    typedef Vec2<int> Vec2i;
    typedef Vec2<float> Vec2f;
    typedef Vec2<double> Vec2d;
} // namespace lodestone::level::types

template <typename T> struct std::hash<lodestone::level::types::Vec2<T>> {
    size_t
    operator()(const lodestone::level::types::Vec2<T> &v) const noexcept {
        return std::hash<T>()(v.x) ^ (std::hash<T>()(v.z) << 1);
    }
};

#endif