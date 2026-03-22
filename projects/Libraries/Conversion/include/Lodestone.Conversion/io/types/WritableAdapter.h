//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_WRITABLEADAPTER_H
#define LODESTONE_WRITABLEADAPTER_H

#include "Lodestone.Conversion/internal/Exports.h"

namespace lodestone::conversion::io::types {
    class LODESTONE_CONVERSION_API WritableAdapter {
    public:
        virtual ~WritableAdapter() = default;

        virtual void baseWrite(void *obj, void *options) const = 0;
    };
}

#endif // LODESTONE_WRITABLEADAPTER_H
