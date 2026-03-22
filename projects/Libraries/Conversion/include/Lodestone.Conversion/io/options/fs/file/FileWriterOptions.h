//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_FILEWRITEROPTIONS_H
#define LODESTONE_FILEWRITEROPTIONS_H
#include <iosfwd>

#include "Lodestone.Conversion/io/options/OptionsBuilder.h"
#include "Lodestone.Conversion/internal/Exports.h"

namespace lodestone::conversion::io::options::fs::file {
    struct LODESTONE_CONVERSION_API FileWriterOptions : IOptions {
        std::ostream &output;

        FileWriterOptions(std::ostream &output) : output(output) {}
    };
}

#endif // LODESTONE_FILEWRITEROPTIONS_H
