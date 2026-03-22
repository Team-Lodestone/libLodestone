//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_CHUNKOPTIONS_H
#define LODESTONE_CHUNKOPTIONS_H
#include <Lodestone.Conversion/io/options/OptionsBuilder.h>
#include <Lodestone.Level/types/Vec2.h>

#include "Lodestone.Minecraft.Common/internal/Exports.h"

namespace lodestone::minecraft::common::conversion::io::options {
    struct LODESTONE_MINECRAFT_COMMON_API ChunkOptions : lodestone::conversion::io::options::IOptions  {
        level::types::Vec2i coords;

        ChunkOptions(const level::types::Vec2i &coords) : coords(coords) {}
    };
}

#endif // LODESTONE_CHUNKOPTIONS_H
