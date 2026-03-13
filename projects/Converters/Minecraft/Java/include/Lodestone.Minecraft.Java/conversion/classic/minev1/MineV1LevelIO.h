//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_MINEV1CHUNKIO_H
#define LODESTONE_MINEV1CHUNKIO_H

#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Conversion/io/options/fs/file/FileReaderOptions.h>

#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"

namespace lodestone::minecraft::java::classic::minev1 {
    class MineV1LevelIO : public conversion::io::LevelIO<&identifiers::MINEV1_LEVEL_IO, const common::conversion::io::options::OptionPresets::CommonReadOptions, const common::conversion::io::options::OptionPresets::CommonWriteOptions> {
    public:
        static constexpr int WIDTH = 256;
        static constexpr int HEIGHT = 64;
        static constexpr int DEPTH = 256;

        std::unique_ptr<level::Level> read(const common::conversion::io::options::OptionPresets::CommonReadOptions &options) const override;

        void write(level::Level *l, const common::conversion::io::options::OptionPresets::CommonWriteOptions &options) const override;
    };
} // namespace lodestone::minecraft::java::classic::minev1

#endif // LODESTONE_MINEV1CHUNKIO_H