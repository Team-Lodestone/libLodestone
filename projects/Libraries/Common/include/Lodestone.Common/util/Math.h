//
// Created by DexrnZacAttack on 11/17/25 using zPc-i2.
//
#ifndef LODESTONE_MATH_H
#define LODESTONE_MATH_H
#include "Lodestone.Common/util/Util.h"

#include <cstring>
#include <random>

namespace lodestone::common::util {
    class Math {
    private:
        // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1a_hash
        template <typename I>
        requires std::is_integral_v<I>
        static constexpr I _fnv1a(const char *s, const size_t l, const I hash, const I prime) {
            // set init value to our hash so we can pass into loop directly and
            // recurse
            uint64_t h = hash;

            for (int i = 0; i < l; i++) {
                h = (h ^ s[i]) * prime;
            }

            return h;
        }

    public:
        Math() = delete;

        static std::random_device s_randomDevice;
        static std::mt19937_64 s_random;

        static constexpr size_t FNV1A_64_HASH = 0xcbf29ce484222325;
        static constexpr size_t FNV1A_64_PRIME = 0x00000100000001b3;

        static constexpr uint32_t FNV1A_32_HASH = 0x811c9dc5;
        static constexpr uint32_t FNV1A_32_PRIME = 0x01000193;

        static constexpr auto BASE36 = "0123456789abcdefghijklmnopqrstuvwxyz";

        static constexpr int ceilDiv(const int x, const int y) {
            return (x + y - 1) / y;
        };

        static constexpr uint64_t fnv1a64(const char *s, const size_t l) {
            return _fnv1a<uint64_t>(s, l, FNV1A_64_HASH, FNV1A_64_PRIME);
        }

        static constexpr uint32_t fnv1a32(const char *s, const size_t l) {
            return _fnv1a<uint32_t>(s, l, FNV1A_32_HASH, FNV1A_32_PRIME);
        }

        static constexpr uint64_t fnv1a64(const std::string &s) {
            return fnv1a64(s.data(), s.length());
        }

        static constexpr uint64_t fnv1a64(const char *s) {
            return fnv1a64(s, Util::strlenConstexpr(s));
        }

        static constexpr uint32_t fnv1a32(const std::string &s) {
            return fnv1a32(s.data(), s.length());
        }

        static constexpr uint32_t fnv1a32(const char *s) {
            return fnv1a32(s, Util::strlenConstexpr(s));
        }

        /** Gets a random number
         *
         * @return A random number
         */
        static unsigned long random();

        /** Converts an integer to two's complement Base36
         *
         * @param value Integer value
         * @return String of base36 of value
         */
        static std::string base36(int value);

        static constexpr float degreesToRadians(const float deg) {
            return deg * (std::numbers::pi / 180.0);
        }

        static constexpr float radiansToDegrees(const float deg) {
            return deg * (180.0 / std::numbers::pi);
        }
    };
} // namespace lodestone::common::util

constexpr uint64_t operator""_hash(const char *s, const size_t l) {
    return lodestone::common::util::Math::fnv1a64(s, l);
}

#endif // LODESTONE_MATH_H