//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Lodestone.h"

namespace lodestone {
    extern "C" {
        // clang-format off
        constexpr const char *lodestone_get_build_type() { return BUILD_TYPE; } // NOLINT
        constexpr const char *lodestone_get_compiler_name() { return COMPILER_NAME; } // NOLINT
        constexpr const char *lodestone_get_platform_arch() { return PLATFORM_ARCH; } // NOLINT
        constexpr const char *lodestone_get_platform() { return PLATFORM_NAME; } // NOLINT
        constexpr const char *lodestone_get_version() { return LODESTONE_VERSION; } // NOLINT
        constexpr const char *lodestone_get_library_string() { return LIBRARY_STRING; } // NOLINT
        // clang-format on
    }

    unsigned long long getCurrentTimeMillis() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count();
    }
} // lodestone