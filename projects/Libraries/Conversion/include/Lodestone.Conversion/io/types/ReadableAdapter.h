//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_READABLEADAPTER_H
#define LODESTONE_READABLEADAPTER_H
#include <any>

#include <proxy/proxy.h>
#include <memory>
#include "Lodestone.Conversion/internal/Exports.h"

namespace lodestone::conversion::io::types {
    class LODESTONE_CONVERSION_API ReadableAdapter {
    public:
        virtual ~ReadableAdapter() = default;

        struct LODESTONE_CONVERSION_API ReallyAny : pro::facade_builder::build {};

        virtual pro::proxy<ReallyAny> baseRead(void *options) const = 0;
    };
}

#endif // LODESTONE_READABLEADAPTER_H
