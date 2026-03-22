//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_OPTIONS_H
#define LODESTONE_OPTIONS_H

#include "Lodestone.Conversion/internal/Exports.h"

namespace lodestone::conversion::io::options {
    struct LODESTONE_CONVERSION_API IOptions {
        IOptions() = default;
    };

    struct LODESTONE_CONVERSION_API EmptyOptions : IOptions {};

    template <typename... O>
    struct LODESTONE_CONVERSION_API OptionsBuilder : IOptions, O... {
        template <typename... A>
        explicit OptionsBuilder(A&&... args)
            : O(std::forward<A>(args))... {}
    };
}

#endif // LODESTONE_OPTIONS_H
