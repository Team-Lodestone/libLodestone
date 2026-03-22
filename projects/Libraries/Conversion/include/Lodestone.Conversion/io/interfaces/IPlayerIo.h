//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_IPLAYERIO_H
#define LODESTONE_IPLAYERIO_H
#include "Lodestone.Conversion/io/IObjectIo.h"
#include "Lodestone.Conversion/internal/Exports.h"

namespace lodestone::conversion::io::interfaces {
    class LODESTONE_CONVERSION_API IPlayerIO : virtual public IObjectIO {
    };
}

#endif // LODESTONE_IPLAYERIO_H
