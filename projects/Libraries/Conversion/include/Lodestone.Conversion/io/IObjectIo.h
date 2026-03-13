//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_IOBJECTIO_H
#define LODESTONE_IOBJECTIO_H
#include "Lodestone.Conversion/io/types/ReadableAdapter.h"
#include "Lodestone.Conversion/io/types/WritableAdapter.h"

namespace lodestone::conversion::io {
    struct IObjectIO : types::ReadableAdapter, types::WritableAdapter {
        constexpr IObjectIO() = default;

        ~IObjectIO() override = default;
    };
}

#endif // LODESTONE_IOBJECTIO_H
