//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_CHUNKOPTIONS_H
#define LODESTONE_CHUNKOPTIONS_H
#include <Lodestone.Conversion/io/options/OptionsBuilder.h>
#include <Lodestone.Level/coords/ChunkCoordinates.h>

namespace lodestone::minecraft::common::conversion::io::options {
    struct ChunkOptions : lodestone::conversion::io::options::IOptions {
        level::coords::ChunkCoordinates coords;

        ChunkOptions(const level::coords::ChunkCoordinates &coords) : coords(coords) {}
    };
}

#endif // LODESTONE_CHUNKOPTIONS_H
