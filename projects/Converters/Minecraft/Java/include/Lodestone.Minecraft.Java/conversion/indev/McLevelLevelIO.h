//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_MCLEVELLEVELIO_H
#define LODESTONE_MCLEVELLEVELIO_H

#include <Lodestone.Conversion/registry/Registries.h>
#include <Lodestone.Conversion/registry/RegistryRelations.h>

#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Minecraft.Common/conversion/io/ObjectIOs.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"

#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>

#include <libnbt++/nbt_tags.h>
#include "Lodestone.Minecraft.Java/internal/Exports.h"

namespace lodestone::minecraft::java::indev {
    class McLevelNbtLevelIO;

    class LODESTONE_MINECRAFT_JAVA_API McLevelLevelIO : public lodestone::conversion::io::LevelIO<&identifiers::MCLEVEL_LEVEL_IO, const common::conversion::io::options::OptionPresets::CommonReadOptions, const common::conversion::io::options::OptionPresets::CommonWriteOptions>,
    public conversion::registry::RegistryIdentifierRelations<
        conversion::registry::RegistryIdentifierRelation<&identifiers::NBT_LEVEL_IO, McLevelNbtLevelIO, &identifiers::MCLEVEL_NBT_LEVEL_IO, conversion::registry::LevelIORegistry>
        > {
      public:
        std::unique_ptr<lodestone::level::Level>
        read(const common::conversion::io::options::OptionPresets::CommonReadOptions &options) const override;

        void write(lodestone::level::Level *l, const common::conversion::io::options::OptionPresets::CommonWriteOptions &options) const override;
    };

    class LODESTONE_MINECRAFT_JAVA_API McLevelNbtLevelIO : public common::conversion::io::NbtLevelIO<&identifiers::MCLEVEL_NBT_LEVEL_IO, const common::conversion::io::options::OptionPresets::CommonNbtReadOptions, const conversion::io::options::EmptyOptions>,
    public conversion::registry::RegistryIdentifierRelations<
        conversion::registry::RegistryIdentifierRelation<&conversion::identifiers::LEVEL_IO, McLevelLevelIO, &identifiers::MCLEVEL_LEVEL_IO, conversion::registry::LevelIORegistry>
        > {
        /** Creates a Level from a mclevel Map compound tag */
        std::unique_ptr<level::Level> read(const common::conversion::io::options::OptionPresets::CommonNbtReadOptions &options) const override;

        /** Writes a level to a given NBT compound tag */
        void write(level::Level *l, const common::conversion::io::options::OptionPresets::NbtOutputWriteOptions<const conversion::io::options::EmptyOptions> &options) const override;
    };
} // namespace lodestone::minecraft::java::indev

#endif // LODESTONE_MCLEVELLEVELIO_H
