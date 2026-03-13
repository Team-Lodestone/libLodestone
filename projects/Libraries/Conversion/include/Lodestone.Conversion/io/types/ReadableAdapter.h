//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_READABLEADAPTER_H
#define LODESTONE_READABLEADAPTER_H
#include <any>

#include <proxy/proxy.h>
#include <memory>

namespace lodestone::conversion::io::types {
    class ReadableAdapter {
    public:
        virtual ~ReadableAdapter() = default;

        struct ReallyAny : pro::facade_builder::build {};

        virtual pro::proxy<ReallyAny> baseRead(void *options) const = 0;
    };
}

#endif // LODESTONE_READABLEADAPTER_H
