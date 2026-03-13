//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_OPTIONPRESETS_H
#define LODESTONE_OPTIONPRESETS_H
#include <Lodestone.Conversion/io/options/fs/FilesystemPathOptions.h>
#include <Lodestone.Conversion/io/options/fs/file/FileReaderOptions.h>
#include <Lodestone.Conversion/io/options/fs/file/FileWriterOptions.h>
#include "Lodestone.Minecraft.Common/conversion/io/options/ChunkOptions.h"
#include "Lodestone.Minecraft.Common/conversion/io/options/NbtOutputOptions.h"
#include "Lodestone.Minecraft.Common/conversion/io/options/NbtReaderOptions.h"

#include <Lodestone.Conversion/io/options/OptionsBuilder.h>
#include <Lodestone.Conversion/io/options/versioned/VersionedOptions.h>

namespace lodestone::minecraft::common::conversion::io::options {
    class OptionPresets {
        OptionPresets() = delete;
    public:
        // I/O
        using CommonReadOptions = lodestone::conversion::io::options::OptionsBuilder<
            lodestone::conversion::io::options::fs::file::FileReaderOptions,
            lodestone::conversion::io::options::versioned::VersionedOptions
        >;

        using CommonWriteOptions = lodestone::conversion::io::options::OptionsBuilder<
            lodestone::conversion::io::options::fs::file::FileWriterOptions,
            lodestone::conversion::io::options::versioned::VersionedOptions
        >;

        // FS
        using CommonFilesystemOptions = lodestone::conversion::io::options::OptionsBuilder<
            lodestone::conversion::io::options::fs::FilesystemPathOptions,
            lodestone::conversion::io::options::versioned::VersionedOptions
        >;

        // NBT
        using CommonNbtReadOptions = lodestone::conversion::io::options::OptionsBuilder<
            NbtReaderOptions,
            lodestone::conversion::io::options::versioned::VersionedOptions
        >;

        template <typename WO = lodestone::conversion::io::options::EmptyOptions>
        requires std::is_base_of_v<lodestone::conversion::io::options::IOptions, WO>
        using NbtOutputWriteOptions = lodestone::conversion::io::options::OptionsBuilder<
                 WO,
                 NbtOutputOptions
             >;

        using CommonNbtFilesystemReadOptions = lodestone::conversion::io::options::OptionsBuilder<
            CommonNbtReadOptions,
            lodestone::conversion::io::options::fs::FilesystemPathOptions
        >;

        // Chunk
        using CommonChunkOptions = lodestone::conversion::io::options::OptionsBuilder<
            ChunkOptions,
            lodestone::conversion::io::options::versioned::VersionedOptions
        >;

        using CommonChunkWriteOptions = lodestone::conversion::io::options::OptionsBuilder<
            ChunkOptions,
            CommonWriteOptions
        >;

        using CommonChunkReadOptions = lodestone::conversion::io::options::OptionsBuilder<
            ChunkOptions,
            CommonReadOptions
        >;

        // Player
        using CommonPlayerReadOptions = lodestone::conversion::io::options::OptionsBuilder<
            CommonReadOptions,
            lodestone::conversion::io::options::fs::FilesystemPathOptions
        >;
    };
}

#endif // LODESTONE_OPTIONPRESETS_H
