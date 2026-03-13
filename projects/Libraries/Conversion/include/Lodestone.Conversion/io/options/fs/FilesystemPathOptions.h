//
// Created by DexrnZacAttack on 2/15/26 using zPc-i2.
//
#ifndef LODESTONE_FILESYSTEMPATHOPTIONS_H
#define LODESTONE_FILESYSTEMPATHOPTIONS_H
#include "Lodestone.Conversion/io/options/OptionsBuilder.h"

#include <filesystem>

namespace lodestone::conversion::io::options::fs {
    struct FilesystemPathOptions : public IOptions {
        std::filesystem::path path;

        FilesystemPathOptions(const std::filesystem::path &path) : path(path) {}
    };
}

#endif // LODESTONE_FILESYSTEMPATHOPTIONS_H