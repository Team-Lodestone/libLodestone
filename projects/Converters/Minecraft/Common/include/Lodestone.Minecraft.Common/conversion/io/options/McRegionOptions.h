//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_CHUNKOPTIONS_H
#define LODESTONE_CHUNKOPTIONS_H
#include "Lodestone.Minecraft.Common/region/RegionCompression.h"

#include <Lodestone.Conversion/io/options/OptionsBuilder.h>

namespace lodestone::minecraft::common::conversion::io::options {
    struct McRegionOptions : lodestone::conversion::io::options::IOptions {
        region::RegionCompression compression;

        McRegionOptions(const region::RegionCompression &compression) : compression(compression) {}
    };
}

#endif // LODESTONE_CHUNKOPTIONS_H
