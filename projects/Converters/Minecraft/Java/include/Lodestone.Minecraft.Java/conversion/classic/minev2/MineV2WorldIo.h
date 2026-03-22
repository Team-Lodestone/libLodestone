//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#ifndef LODESTONE_MINEV2WORLDIO_H
#define LODESTONE_MINEV2WORLDIO_H

#include <Lodestone.Conversion/registry/RegistryRelations.h>

#include <Lodestone.Conversion/registry/Registries.h>

#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/conversion/classic/minev2/options/MineV2WorldWriteOptions.h"
#include "Lodestone.Minecraft.Java/internal/Exports.h"

namespace lodestone::minecraft::java::classic::minev2 {
    class MineV2LevelIO;

    using MineV2WriteOptions = conversion::io::options::OptionsBuilder<
        options::MineV2WorldWriteOptions,
        conversion::io::options::fs::file::FileWriterOptions,
        conversion::io::options::versioned::VersionedOptions
    >;

    class LODESTONE_MINECRAFT_JAVA_API MineV2WorldIO : public conversion::io::WorldIO<&identifiers::MINEV2_WORLD_IO, const common::conversion::io::options::OptionPresets::CommonReadOptions, const MineV2WriteOptions>,
    public conversion::registry::RegistryIdentifierRelations<
        conversion::registry::RegistryIdentifierRelation<&lodestone::conversion::identifiers::LEVEL_IO, const MineV2LevelIO, &identifiers::MINEV2_LEVEL_IO, conversion::registry::LevelIORegistry>
    > {
      public:
        static constexpr int32_t SIGNATURE = 0x271BB788;

        std::unique_ptr<level::world::World> read(const common::conversion::io::options::OptionPresets::CommonReadOptions &options) const override;
        void write(level::world::World *w, const MineV2WriteOptions &options) const override;
    };
} // namespace lodestone::minecraft::java::classic::minev2

#endif // LODESTONE_MINEV2WORLDIO_H