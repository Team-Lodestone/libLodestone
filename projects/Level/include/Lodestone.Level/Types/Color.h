//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_COLOR_H
#define  LODESTONE_COLOR_H

#include <functional>

namespace lodestone::level::types {
    struct Color final {
        unsigned char r, g, b, a;

        bool operator==(const Color &rhs) const {
            return r == rhs.r
                && g == rhs.g
                && b == rhs.b
                && a == rhs.a;
        }

        Color operator+(const int v) const {
            return {
                static_cast<unsigned char>(r + v),
                static_cast<unsigned char>(g + v),
                static_cast<unsigned char>(b + v),
                static_cast<unsigned char>(a + v)
            };
        }

        Color operator-(const int v) const {
            return {
                static_cast<unsigned char>(r - v),
                static_cast<unsigned char>(g - v),
                static_cast<unsigned char>(b - v),
                static_cast<unsigned char>(a - v)
            };
        }

        Color operator*(const int v) const {
            return {
                static_cast<unsigned char>(r * v),
                static_cast<unsigned char>(g * v),
                static_cast<unsigned char>(b * v),
                static_cast<unsigned char>(a * v)
            };
        }

        Color operator/(const int v) const {
            return {
                static_cast<unsigned char>(r / v),
                static_cast<unsigned char>(g / v),
                static_cast<unsigned char>(b / v),
                static_cast<unsigned char>(a / v)
            };
        }

        Color operator+(const Color &rhs) const {
            return {
                static_cast<unsigned char>(r + rhs.r),
                static_cast<unsigned char>(g + rhs.g),
                static_cast<unsigned char>(b + rhs.b),
                static_cast<unsigned char>(a + rhs.a)
            };
        }

        Color operator-(const Color &rhs) const {
            return {
                static_cast<unsigned char>(r - rhs.r),
                static_cast<unsigned char>(g - rhs.g),
                static_cast<unsigned char>(b - rhs.b),
                static_cast<unsigned char>(a - rhs.a)
            };
        }

        Color operator*(const Color &rhs) const {
            return {
                static_cast<unsigned char>(r * rhs.r),
                static_cast<unsigned char>(g * rhs.g),
                static_cast<unsigned char>(b * rhs.b),
                static_cast<unsigned char>(a * rhs.a)
            };
        }

        Color operator/(const Color &rhs) const {
            return {
                static_cast<unsigned char>(r / rhs.r),
                static_cast<unsigned char>(g / rhs.g),
                static_cast<unsigned char>(b / rhs.b),
                static_cast<unsigned char>(a / rhs.a)
            };
        }
    };
}

template <>
struct std::hash<lodestone::level::types::Color> {
    size_t operator()(const lodestone::level::types::Color& v) const noexcept {
        // we can just combine it into an int lol
        return (v.r << 24)
             | (v.g << 16)
             | (v.b << 8)
             | (v.a);
    }
};

#endif