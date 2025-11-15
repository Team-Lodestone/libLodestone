//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_VEC3I_H
#define LODESTONE_VEC3I_H
#include <Lodestone.Common/Defines.h>

namespace lodestone::level::types {
    template <typename T>
    struct LODESTONE_API Vec3 final : public lodestone::common::string::StringSerializable {
        T x, y, z;

        constexpr Vec3(const T x, const T y, const T z) : x(x), y(y), z(z) {
        }

        constexpr std::string toString() const override {
            return std::format("Vec3[x={}, y={}, z={}]", x, y, z);
        };

        constexpr operator T *() { return &x; }
        constexpr operator const T *() const { return &x; }

        constexpr bool operator==(const Vec3 &rhs) const {
            return x == rhs.x
                   && y == rhs.y
                   && z == rhs.z;
        }

        constexpr Vec3 operator+(const T v) const {
            return {
                x + v,
                y + v,
                z + v
            };
        }

        constexpr Vec3 operator-(const T v) const {
            return {
                x - v,
                y - v,
                z - v
            };
        }

        constexpr Vec3 operator*(const T v) const {
            return {
                x * v,
                y * v,
                z * v
            };
        }

        constexpr Vec3 operator/(const T v) const {
            return {
                x / v,
                y / v,
                z / v
            };
        }

        constexpr Vec3 operator+(const Vec3 &rhs) const {
            return {
                x + rhs.x,
                y + rhs.y,
                z + rhs.z
            };
        }

        constexpr Vec3 operator-(const Vec3 &rhs) const {
            return {
                x - rhs.x,
                x - rhs.y,
                z - rhs.z
            };
        }

        constexpr Vec3 operator*(const Vec3 &rhs) const {
            return {
                x * rhs.x,
                y * rhs.y,
                z * rhs.z
            };
        }

        constexpr Vec3 operator/(const Vec3 &rhs) const {
            return {
                x / rhs.x,
                y / rhs.y,
                z / rhs.z
            };
        }

        template <typename V>
        Vec3<V> asVec() const {
            return Vec3<V>(static_cast<V>(x), static_cast<V>(y), static_cast<V>(z));
        }
    };

    typedef Vec3<int> Vec3i;
    typedef Vec3<float> Vec3f;
    typedef Vec3<double> Vec3d;
}

template<typename T>
struct std::hash<lodestone::level::types::Vec3<T>> {
    size_t operator()(const lodestone::level::types::Vec3<T> &v) const noexcept {
        return std::hash<T>()(v.x)
               ^ (std::hash<T>()(v.y) << 1)
               ^ (std::hash<T>()(v.z) << 2);
    }
};

#endif