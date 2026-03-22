//
// Created by DexrnZacAttack on 2/15/26 using zPc-i2.
//
#ifndef LODESTONE_UTIL_H
#define LODESTONE_UTIL_H
#include <cstring>

#include "Lodestone.Common/internal/Exports.h"

namespace lodestone::common::util {
    class LODESTONE_COMMON_API Util {
    public:
        Util() = delete;

#define SWITCH_STRING(s) switch(lodestone::common::util::Math::fnv1a64(s))

        static constexpr bool strcmpConstexpr(const char *lhs, const char *rhs) {
            while (*lhs || *rhs) {
                if (*lhs++ != *rhs++)
                    return false;
            }

            return true;
        }

        static constexpr size_t strlenConstexpr(const char *s) {
            size_t l = 0;
            while (*s++) {
                ++l;
            }

            return l;
        }

        template <size_t Len>
        static consteval size_t strlenCompileTime(const char (&)[Len]) {
            return Len-1;
        }

        static unsigned long long getCurrentTimeMillis();
    };
}

#endif // LODESTONE_UTIL_H