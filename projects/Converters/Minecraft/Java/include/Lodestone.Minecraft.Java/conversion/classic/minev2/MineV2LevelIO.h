//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_MINEV2LEVELIO_H
#define LODESTONE_MINEV2LEVELIO_H

#include <Lodestone.Conversion/registry/Registries.h>

#include <Lodestone.Conversion/Identifiers.h>

#include <Lodestone.Conversion/registry/RegistryRelations.h>

#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/internal/Exports.h"

namespace lodestone::minecraft::java::classic::minev2 {
    class MineV2WorldIO;

    class LODESTONE_MINECRAFT_JAVA_API MineV2LevelIO : public conversion::io::LevelIO<
        &identifiers::MINEV2_LEVEL_IO,
        const common::conversion::io::options::OptionPresets::CommonReadOptions,
        const common::conversion::io::options::OptionPresets::CommonWriteOptions
    >, public conversion::registry::RegistryIdentifierRelations<
        conversion::registry::RegistryIdentifierRelation<&lodestone::conversion::identifiers::WORLD_IO, const MineV2WorldIO, &identifiers::MINEV2_WORLD_IO, conversion::registry::WorldIORegistry>
    > {
      public:
        std::unique_ptr<level::Level>
        read(const common::conversion::io::options::OptionPresets::CommonReadOptions& options) const override;

        void write(level::Level *l, const common::conversion::io::options::OptionPresets::CommonWriteOptions &options) const override;
    };
} // namespace lodestone::minecraft::java::classic::minev2

#endif // LODESTONE_MINEV2LEVELIO_H