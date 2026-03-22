//
// Created by DexrnZacAttack on 1/9/26 using zPc-i2.
//
#ifndef LODESTONE_PALETTEINDEXTOOLARGEEXCEPTION_H
#define LODESTONE_PALETTEINDEXTOOLARGEEXCEPTION_H
#include <stdexcept>

#include "Lodestone.Common/internal/Exports.h"

namespace lodestone::common::exception {
    class LODESTONE_COMMON_API PaletteIndexTooLargeException : public std::exception {
        const char *what() const noexcept override {
            return "Index palette too large";
        };
    };
}

#endif // LODESTONE_PALETTEINDEXTOOLARGEEXCEPTION_H