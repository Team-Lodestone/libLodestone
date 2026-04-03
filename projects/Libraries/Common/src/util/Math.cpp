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

    std::string Math::encodeBase36(int value) {
        if (value == 0)
            return "0"; // gotta get that optimization

        std::string s;
        const bool n = value < 0;

        if (n) {
            value = -value;
        }

        while (value > 0) {
            s += BASE36[value % 36];
            value /= 36;
        }

        if (n) {
            s += '-';
        }

        std::ranges::reverse(s);
        return s;
    }

    int64_t Math::decodeBase36(const std::string &input) {
        int64_t result = 0;

        for (const char c : input) {
            int value;
            if (c >= '0' && c <= '9') {
                value = c - '0';
            } else if (c >= 'A' && c <= 'Z') {
                value = c - 'A' + 10;
            } else {
                continue;
            }
            result = result * 36 + value;
        }
        if (input.starts_with('-')) {
            result = -result;
        }

        return result;
    }
} // namespace lodestone::common::util
