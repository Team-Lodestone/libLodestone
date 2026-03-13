//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_FILEREADEROPTIONS_H
#define LODESTONE_FILEREADEROPTIONS_H
#include <iosfwd>

#include "Lodestone.Conversion/io/options/OptionsBuilder.h"

namespace lodestone::conversion::io::options::fs::file {
    struct FileReaderOptions : IOptions {
        std::istream &input;

        FileReaderOptions(std::istream &input) : input(input) {}
    };
}

#endif // LODESTONE_FILEREADEROPTIONS_H
