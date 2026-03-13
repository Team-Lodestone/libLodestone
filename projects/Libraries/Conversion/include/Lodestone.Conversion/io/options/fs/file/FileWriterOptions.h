//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_FILEWRITEROPTIONS_H
#define LODESTONE_FILEWRITEROPTIONS_H
#include <iosfwd>

#include "Lodestone.Conversion/io/options/OptionsBuilder.h"

namespace lodestone::conversion::io::options::fs::file {
    struct FileWriterOptions : IOptions {
        std::ostream &output;

        FileWriterOptions(std::ostream &output) : output(output) {}
    };
}

#endif // LODESTONE_FILEWRITEROPTIONS_H
