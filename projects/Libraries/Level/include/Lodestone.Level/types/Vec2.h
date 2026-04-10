//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_VEC2I_H
#define LODESTONE_VEC2I_H

#include <Lodestone.Common/string/StringSerializable.h>
#include <format>

namespace lodestone::level::types {
    template <typename T>
    struct Vec2 {
        static_assert(std::is_arithmetic_v<T>, "typeof T must be numeric"); // Waiter! I want one Vec2<std::string, std::string> please.

        T x{}, y{};

        constexpr Vec2(const T x, const T z) : x(x), y(z) {}

        template <typename O>
        explicit constexpr Vec2(const Vec2<O>& rhs) : x(static_cast<T>(rhs.x)), y(static_cast<T>(rhs.y)) {
        }

        constexpr ~Vec2() = default;

        constexpr operator T *() { return &x; }
        constexpr operator const T *() const { return &x; }

        constexpr bool operator==(const Vec2 &rhs) const {
            return x == rhs.x && y == rhs.y;
        }

        constexpr Vec2 operator+(const T v) const { return {x + v, y + v}; }

        constexpr Vec2 operator-(const T v) const { return {x - v, y - v}; }

        constexpr Vec2 operator*(const T v) const { return {x * v, y * v}; }

        constexpr Vec2 operator/(const T v) const { return {x / v, y / v}; }

        constexpr Vec2 operator+(const Vec2 &rhs) const {
            return {x + rhs.x, y + rhs.y};
        }

        constexpr Vec2 operator-(const Vec2 &rhs) const {
            return {x - rhs.x, y - rhs.y};
        }

        constexpr Vec2 operator*(const Vec2 &rhs) const {
            return {x * rhs.x, y * rhs.y};
        }

        constexpr Vec2 operator/(const Vec2 &rhs) const {
            return {x / rhs.x, y / rhs.y};
        }

        std::string toString() const {
            return std::format("Vec2[x={}, y={}]", x, y);
        };
    };

    template <typename T>
    constexpr Vec2<T> VEC2_ZERO{0,0};

    template <typename T>
    constexpr Vec2<T> VEC2_ONE{1,1};

    using Vec2i = Vec2<int>;
    using Vec2f = Vec2<float>;
    using Vec2d = Vec2<double>;
} // namespace lodestone::level::types

template <typename T> struct std::hash<lodestone::level::types::Vec2<T>> {
    size_t
    operator()(const lodestone::level::types::Vec2<T> &v) const noexcept {
        return std::hash<T>()(v.x) ^ (std::hash<T>()(v.y) << 1);
    }
};

template <typename T>
struct std::formatter<lodestone::level::types::Vec2<T>> {
    template <typename FormatParseContext> constexpr auto parse(FormatParseContext &pc) { return pc.begin(); }
    template <typename FormatContext> auto format(lodestone::level::types::Vec2<T> vec, FormatContext &fc) const { return std::format_to(fc.out(), "x={}, y={}", vec.x, vec.y); }
};

#endif