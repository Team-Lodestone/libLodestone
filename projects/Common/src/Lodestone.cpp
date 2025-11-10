//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include <chrono>

#include "Lodestone.h"

namespace lodestone {
    extern "C" {
        // clang-format off
        constexpr const char *lodestone_get_build_type() { return LODESTONE_BUILD_TYPE; } // NOLINT
        constexpr const char *lodestone_get_compiler_name() { return LODESTONE_COMPILER_NAME; } // NOLINT
        constexpr const char *lodestone_get_platform_arch() { return LODESTONE_PLATFORM_ARCH; } // NOLINT
        constexpr const char *lodestone_get_platform() { return LODESTONE_PLATFORM_NAME; } // NOLINT
        constexpr const char *lodestone_get_version() { return LODESTONE_VERSION; } // NOLINT
        constexpr const char *lodestone_get_library_string() { return lodestone::LIBRARY_STRING; } // NOLINT
    // clang-format on
    }

    unsigned long long getCurrentTimeMillis() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch())
                .count();
    }
} // lodestone