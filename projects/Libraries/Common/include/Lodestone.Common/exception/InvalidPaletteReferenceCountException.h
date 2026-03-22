//
// Created by DexrnZacAttack on 1/9/26 using zPc-i2.
//
#ifndef LODESTONE_INVALIDPALETTEREFERENCECOUNTEXCEPTION_H
#define LODESTONE_INVALIDPALETTEREFERENCECOUNTEXCEPTION_H
#include <exception>

#include "Lodestone.Common/internal/Exports.h"

namespace lodestone::common::exception {
    class LODESTONE_COMMON_API InvalidPaletteReferenceCountException : public std::exception {
        const char *what() const noexcept override {
            return "Invalid palette reference count";
        };
    };
}

#endif // LODESTONE_INVALIDPALETTEREFERENCECOUNTEXCEPTION_H
