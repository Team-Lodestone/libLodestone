//
// Created by DexrnZacAttack on 11/17/25 using zPc-i2.
//
#ifndef LODESTONE_MATH_H
#define LODESTONE_MATH_H

namespace lodestone::common {
    class Math {
    public:
        static constexpr int ceilDiv(const int x, const int y) {
            return (x + y - 1) / y;
        };
    };
}

#endif //LODESTONE_MATH_H
