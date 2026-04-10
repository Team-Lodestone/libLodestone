//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_VEC3I_H
#define LODESTONE_VEC3I_H
#include <Lodestone.Common/Defines.h>

namespace lodestone::level::types {
    template <typename T>
    struct LODESTONE_API Vec3 final {
        static_assert(std::is_arithmetic_v<T>, "T must be a numeric type");

        T x, y, z;

        constexpr Vec3(const T x, const T y, const T z) : x(x), y(y), z(z) {}

        template <typename O>
        explicit constexpr Vec3(const Vec3<O>& rhs) : x(static_cast<T>(rhs.x)), y(static_cast<T>(rhs.y)), z(static_cast<T>(rhs.z)) {
        }

        std::string toString() const {
            return std::format("Vec3[x={}, y={}, z={}]", x, y, z);
        };

        constexpr operator T *() { return &x; }
        constexpr operator const T *() const { return &x; }

        constexpr bool operator==(const Vec3 &rhs) const {
            return x == rhs.x && y == rhs.y && z == rhs.z;
        }

        constexpr Vec3 operator+(const T v) const {
            return {x + v, y + v, z + v};
        }

        constexpr Vec3 operator-(const T v) const {
            return {x - v, y - v, z - v};
        }

        constexpr Vec3 operator*(const T v) const {
            return {x * v, y * v, z * v};
        }

        constexpr Vec3 operator/(const T v) const {
            return {x / v, y / v, z / v};
        }

        constexpr Vec3& operator+=(const T v) {
            this->x += v;
            this->y += v;
            this->z += v;

            return *this;
        }

        constexpr Vec3& operator-=(const T v) {
            this->x -= v;
            this->y -= v;
            this->z -= v;

            return *this;
        }

        constexpr Vec3& operator*=(const T v) {
            this->x *= v;
            this->y *= v;
            this->z *= v;

            return *this;
        }

        constexpr Vec3& operator/=(const T v) {
            this->x /= v;
            this->y /= v;
            this->z /= v;

            return *this;
        }

        constexpr Vec3 operator+(const Vec3 &rhs) const {
            return {x + rhs.x, y + rhs.y, z + rhs.z};
        }

        constexpr Vec3 operator-(const Vec3 &rhs) const {
            return {x - rhs.x, x - rhs.y, z - rhs.z};
        }

        constexpr Vec3 operator*(const Vec3 &rhs) const {
            return {x * rhs.x, y * rhs.y, z * rhs.z};
        }

        constexpr Vec3 operator/(const Vec3 &rhs) const {
            return {x / rhs.x, y / rhs.y, z / rhs.z};
        }

        constexpr Vec3& operator+=(const Vec3 &rhs) {
            this->x += rhs.x;
            this->y += rhs.y;
            this->z += rhs.z;

            return *this;
        }

        constexpr Vec3& operator-=(const Vec3 &rhs) {
            this->x -= rhs.x;
            this->y -= rhs.y;
            this->z -= rhs.z;

            return *this;
        }

        constexpr Vec3& operator*=(const Vec3 &rhs) {
            this->x *= rhs.x;
            this->y *= rhs.y;
            this->z *= rhs.z;

            return *this;
        }

        constexpr Vec3& operator/=(const Vec3 &rhs) {
            this->x /= rhs.x;
            this->y /= rhs.y;
            this->z /= rhs.z;

            return *this;
        }

        constexpr Vec3& normalize() {
            float m = std::sqrt(this->x * this->x + this->y * this-> y + this->z * this->z);

            this->x /= m;
            this->y /= m;
            this->z /= m;

            return *this;
        }

        constexpr Vec3 normalized() const {
            float m = std::sqrt(this->x * this->x + this->y * this-> y + this->z * this->z);

            return this / m;
        }

        constexpr Vec3& cross(const Vec3 &rhs) {
            T ox = this->x;
            T oy = this->y;
            T oz = this->z;

            this->x = oy * rhs.z - oz * rhs.y;
            this->y = oz * rhs.x - ox * rhs.z;
            this->z = ox * rhs.y - oy * rhs.x;

            return *this;
        }

        constexpr Vec3 crossed(const Vec3 &rhs) const {
            T ox = this->x;
            T oy = this->y;
            T oz = this->z;

            return Vec3(
                oy * rhs.z - oz * rhs.y,
                oz * rhs.x - ox * rhs.z,
                ox * rhs.y - oy * rhs.x
            );
        }
    };

    template <typename T>
    constexpr Vec3<T> VEC3_ZERO{0,0,0};

    template <typename T>
    constexpr Vec3<T> VEC3_ONE{1,1,1};

    typedef Vec3<int> Vec3i;
    typedef Vec3<float> Vec3f;
    typedef Vec3<double> Vec3d;
} // namespace lodestone::level::types

template <typename T> struct std::hash<lodestone::level::types::Vec3<T>> {
    size_t
    operator()(const lodestone::level::types::Vec3<T> &v) const noexcept {
        return std::hash<T>()(v.x) ^ (std::hash<T>()(v.y) << 1) ^
               (std::hash<T>()(v.z) << 2);
    }
};

template <typename T>
struct std::formatter<lodestone::level::types::Vec3<T>> {
    template <typename FormatParseContext> constexpr auto parse(FormatParseContext &pc) { return pc.begin(); }
    template <typename FormatContext> auto format(lodestone::level::types::Vec3<T> vec, FormatContext &fc) const { return std::format_to(fc.out(), "x={}, y={}, z={}", vec.x, vec.y, vec.z); }
};

#endif