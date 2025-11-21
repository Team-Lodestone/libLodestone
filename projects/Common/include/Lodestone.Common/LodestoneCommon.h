//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LODESTONECOMMON_H
#define LODESTONE_LODESTONECOMMON_H

#include "Lodestone.Common/Defines.h"

namespace lodestone::common {
    constexpr const char *const LIBRARY_STRING =
        "libLodestone v" LODESTONE_VERSION " (" LODESTONE_COMPILER_NAME
        " / " LODESTONE_BUILD_TYPE " | " LODESTONE_PLATFORM_NAME
        " " LODESTONE_PLATFORM_ARCH
        ") | https://github.com/Team-Lodestone/libLodestone";

    LODESTONE_API unsigned long long getCurrentTimeMillis();

    // clang-format off
    extern "C" {
        LODESTONE_API NO_DISCARD constexpr const char *lodestone_get_build_type(); // NOLINT
        LODESTONE_API NO_DISCARD constexpr const char *lodestone_get_compiler_name(); // NOLINT
        LODESTONE_API NO_DISCARD constexpr const char *lodestone_get_platform_arch(); // NOLINT
        LODESTONE_API NO_DISCARD constexpr const char *lodestone_get_platform(); // NOLINT
        LODESTONE_API NO_DISCARD constexpr const char *lodestone_get_version(); // NOLINT
        LODESTONE_API NO_DISCARD constexpr const char *lodestone_get_library_string(); // NOLINT
    }
    // clang-format on
} // namespace lodestone::common

#endif //LODESTONE_LODESTONECOMMON_H