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

        static constexpr int ceilDiv(const int x, const int y) {
            return (x + y - 1) / y;
        };

        static unsigned long random();
    };
} // namespace lodestone::common

#endif // LODESTONE_MATH_H
