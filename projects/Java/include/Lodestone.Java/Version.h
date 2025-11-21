//
// Created by DexrnZacAttack on 10/25/25 using zPc-i2.
//
#ifndef LODESTONE_VERSION_H
#define LODESTONE_VERSION_H

#include <Lodestone.Common/Defines.h>

namespace lodestone::java {
    enum LODESTONE_API Version {
        // Pre-classic (rubydung)
        rd131655,
        rd20090515,
        rd161348,
        // Classic
        c0_0_12a,
        c0_0_14a,
        c0_0_19a,
        c0_0_20a,
        c0_26st, // survival test
        c0_28,
        c0_30_CPE, // specifically for classic protocol extensions, which adds
                   // additional blocks
        // Indev
        in20091223_1457,
        in20100109_1939,
        in20100114,
        in20100122_2251,
        in20100124_2119,
        in20100128_2200,
        in20100129_2332,
        in20100206_2034,
        in20100219,
        // Infdev
        inf20100607,
        inf20100618,
        inf20100624,
        inf20100625_1917,
        inf20100629,
        // Alpha

        // Beta
        b1_3 // todo this should be first version with numeric + metadata block
             // type
    };
}

#endif // LODESTONE_VERSION_H