//
// Created by DexrnZacAttack on 11/17/25 using zPc-i2.
//
#include "Lodestone.Common/util/Math.h"

#include <algorithm>
#include <ranges>

namespace lodestone::common::util {
    std::random_device Math::sRd;
    std::mt19937_64 Math::sRand(sRd());

    unsigned long Math::random() { return Math::sRand(); }

    std::string Math::base36(int value) {
        if (value == 0)
            return "0"; // gotta get that optimization

        std::string s;
        const bool n = value < 0;

        if (n)
            value = -value;

        while (value > 0) {
            s += BASE36[value % 36];
            value /= 36;
        }

        if (n)
            s += '-';

        std::ranges::reverse(s);
        return s;
    }
} // namespace lodestone::common::util
