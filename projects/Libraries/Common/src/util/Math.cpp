//
// Created by DexrnZacAttack on 11/17/25 using zPc-i2.
//
#include "Lodestone.Common/util/Math.h"

namespace lodestone::common::util {
    std::random_device Math::rd;
    std::mt19937_64 Math::rand(rd());

    unsigned long Math::random() { return rand(); }
} // namespace lodestone::common::util
