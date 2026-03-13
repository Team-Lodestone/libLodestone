//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_NBTREADEROPTIONS_H
#define LODESTONE_NBTREADEROPTIONS_H
#include <libnbt++/tag_compound.h>

#include <Lodestone.Conversion/io/options/OptionsBuilder.h>

namespace lodestone::minecraft::common::conversion::io::options {
    struct NbtReaderOptions : lodestone::conversion::io::options::IOptions {
        nbt::tag_compound &input;

        NbtReaderOptions(nbt::tag_compound &input) : input(input) {};
    };
}

#endif // LODESTONE_NBTREADEROPTIONS_H
