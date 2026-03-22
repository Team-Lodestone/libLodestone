//
// Created by DexrnZacAttack on 2/17/26 using zPc-i2.
//
#ifndef LODESTONE_NBTOUTPUTWRITABLE_H
#define LODESTONE_NBTOUTPUTWRITABLE_H
#include <Lodestone.Conversion/io/types/Writable.h>
#include "Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h"

#include "Lodestone.Minecraft.Common/internal/Exports.h"

namespace lodestone::minecraft::common::conversion::io::types {
    template <typename W, typename WO>
    class LODESTONE_MINECRAFT_COMMON_API NbtOutputWritable : public lodestone::conversion::io::types::Writable<W, const options::OptionPresets::NbtOutputWriteOptions<WO>>  {
    };
}

#endif // LODESTONE_NBTOUTPUTWRITABLE_H