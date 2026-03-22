//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_VERSIONEDREADFOLDEROPTIONS_H
#define LODESTONE_VERSIONEDREADFOLDEROPTIONS_H
#include "Lodestone.Conversion/io/options/OptionsBuilder.h"

namespace lodestone::conversion::io::options::versioned {
    struct LODESTONE_CONVERSION_API VersionedOptions : IOptions {
        int version;

        VersionedOptions(const int version) : version(version) {}
    };
}

#endif // LODESTONE_VERSIONEDREADFOLDEROPTIONS_H
