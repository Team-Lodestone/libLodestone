//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_OPTIONS_H
#define LODESTONE_OPTIONS_H

namespace lodestone::conversion::io::options {
    struct IOptions {
        IOptions() = default;
    };

    struct EmptyOptions : IOptions {};

    template <typename... O>
    struct OptionsBuilder : IOptions, O... {
        template <typename... A>
        explicit OptionsBuilder(A&&... args)
            : O(std::forward<A>(args))... {}
    };
}

#endif // LODESTONE_OPTIONS_H
