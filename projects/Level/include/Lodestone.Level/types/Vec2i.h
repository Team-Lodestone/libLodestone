//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_VEC2I_H
#define  LODESTONE_VEC2I_H

namespace lodestone::level::types {
    struct Vec2i : public StringSerializable {
        int x, z;

        constexpr Vec2i(const int x, const int z) : x(x), z(z) {}

        constexpr operator int*() { return &x; }
        constexpr operator const int*() const { return &x; }

        constexpr bool operator==(const Vec2i &rhs) const {
            return x == rhs.x
                && z == rhs.z;
        }

        constexpr Vec2i operator+(const int v) const {
            return {
                x + v,
                z + v
            };
        }

        constexpr Vec2i operator-(const int v) const {
            return {
                x - v,
                z - v
            };
        }

        constexpr Vec2i operator*(const int v) const {
            return {
                x * v,
                z * v
            };
        }

        constexpr Vec2i operator/(const int v) const {
            return {
                x / v,
                z / v
            };
        }

        constexpr Vec2i operator+(const Vec2i &rhs) const {
            return {
                x + rhs.x,
                z + rhs.z
            };
        }

        constexpr Vec2i operator-(const Vec2i &rhs) const {
            return {
                x - rhs.x,
                z - rhs.z
            };
        }

        constexpr Vec2i operator*(const Vec2i &rhs) const {
            return {
                x * rhs.x,
                z * rhs.z
            };
        }

        constexpr Vec2i operator/(const Vec2i &rhs) const {
            return {
                x / rhs.x,
                z / rhs.z
            };
        }

        constexpr std::string toString() const override {
            return std::format("Vec2i[x={},z={}]", x, z);
        };
    };
}

template <>
struct std::hash<lodestone::level::types::Vec2i> {
    size_t operator()(const lodestone::level::types::Vec2i& v) const noexcept {
        return std::hash<int>()(v.x)
            ^ (std::hash<int>()(v.z) << 1);
    }
};

#endif