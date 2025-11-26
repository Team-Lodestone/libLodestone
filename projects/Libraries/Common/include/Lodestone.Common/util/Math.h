//
// Created by DexrnZacAttack on 11/17/25 using zPc-i2.
//
#ifndef LODESTONE_MATH_H
#define LODESTONE_MATH_H
#include <cstdlib>
#include <random>

namespace lodestone::common::util {
    class Math {
      public:
        static std::random_device rd;
        static std::mt19937_64 rand;

        static constexpr size_t FNV1A_64_HASH = 0xcbf29ce484222325;
        static constexpr size_t FNV1A_64_PRIME = 0x00000100000001b3;

        static constexpr int ceilDiv(const int x, const int y) {
            return (x + y - 1) / y;
        };

        // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1a_hash
        static constexpr uint64_t fnv1a64(const char *s, const size_t l) {
            // set init value to our hash so we can pass into loop directly and recurse
            uint64_t h = FNV1A_64_HASH;

            for(int i = 0; i < l; i++) {
                h = (h ^ s[i])
                    * FNV1A_64_PRIME;
            }

            return h;
        }

        static unsigned long random();
    };
} // namespace lodestone::common::util

constexpr uint64_t operator""_hash(const char* s, const size_t l) {
    return lodestone::common::util::Math::fnv1a64(s, l);
}

#endif // LODESTONE_MATH_H
