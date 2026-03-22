//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_NBTREADEROPTIONS_H
#define LODESTONE_NBTREADEROPTIONS_H
#include <libnbt++/tag_compound.h>

#include <Lodestone.Conversion/io/options/OptionsBuilder.h>
#include "Lodestone.Minecraft.Common/internal/Exports.h"

namespace lodestone::minecraft::common::conversion::io::options {
    struct LODESTONE_MINECRAFT_COMMON_API NbtReaderOptions : lodestone::conversion::io::options::IOptions {
        nbt::tag_compound &input;

        NbtReaderOptions(nbt::tag_compound &input) : input(input) {};
    };
}

#endif // LODESTONE_NBTREADEROPTIONS_H
