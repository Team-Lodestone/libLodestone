//
// Created by DexrnZacAttack on 2/15/26 using zPc-i2.
//
#include "Lodestone.Common/util/Util.h"

#include <chrono>

unsigned long long lodestone::common::util::Util::getCurrentTimeMillis() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
                       std::chrono::system_clock::now().time_since_epoch())
                .count();
}