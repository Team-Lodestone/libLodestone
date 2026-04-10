//
// Created by DexrnZacAttack on 11/17/25 using zPc-i2.
//
#include "Lodestone.Common/util/Math.h"

#include <algorithm>
#include <ranges>

namespace lodestone::common::util {
    std::random_device Math::s_randomDevice;
    std::mt19937_64 Math::s_random(s_randomDevice());

    unsigned long Math::random() { return Math::s_random(); }

    std::string Math::encodeBase36(signed_size_t value) {
        if (value == 0)
            return "0"; // gotta get that optimization

        std::string s;
        const bool negative = value < 0;

        if (negative) {
            value = -value;
        }

        while (value > 0) {
            s += BASE36[value % 36];
            value /= 36;
        }

        if (negative) {
            s += '-';
        }

        std::ranges::reverse(s);
        return s;
    }
} // namespace lodestone::common::util
