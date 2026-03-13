//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_ALPHAPLAYERIO_H
#define LODESTONE_ALPHAPLAYERIO_H

#include <Lodestone.Conversion/registry/Registries.h>
#include <Lodestone.Conversion/registry/RegistryRelations.h>
#include <Lodestone.Minecraft.Common/conversion/io/ObjectIOs.h>

#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"

namespace lodestone::minecraft::java::alpha::player {
    class AlphaNbtPlayerIO;

    class AlphaPlayerIO : public conversion::io::PlayerIO<&identifiers::ALPHA_PLAYER_IO,
                                           const common::conversion::io::options::OptionPresets::CommonPlayerReadOptions,
                                           const
                                           common::conversion::io::options::OptionPresets::CommonWriteOptions>,
    public conversion::registry::RegistryIdentifierRelations<
            conversion::registry::RegistryIdentifierRelation<&identifiers::NBT_PLAYER_IO,
                const AlphaNbtPlayerIO, &identifiers::ALPHA_NBT_PLAYER_IO,
                conversion::registry::PlayerIORegistry>
        > {
    public:
        std::unique_ptr<level::entity::Player>
        read(const common::conversion::io::options::OptionPresets::CommonPlayerReadOptions &options) const override;

        void write(level::entity::Player *p,
                   const
                   common::conversion::io::options::OptionPresets::CommonWriteOptions
                   &options) const override;
    };

    class AlphaNbtPlayerIO : public common::conversion::io::NbtPlayerIO<
            &identifiers::ALPHA_NBT_PLAYER_IO,
            const
            common::conversion::io::options::OptionPresets::CommonNbtFilesystemReadOptions
            ,
    const conversion::io::options::versioned::VersionedOptions>, public conversion::registry::RegistryIdentifierRelations<
    conversion::registry::RegistryIdentifierRelation<&conversion::identifiers::PLAYER_IO,
        const AlphaPlayerIO, &identifiers::ALPHA_PLAYER_IO,
        conversion::registry::PlayerIORegistry>
> {
    public:
        std::unique_ptr<level::entity::Player>
        read(const
            common::conversion::io::options::OptionPresets::CommonNbtFilesystemReadOptions
            &options) const override;

        void write(level::entity::Player *plr,
                   const common::conversion::io::options::OptionPresets::NbtOutputWriteOptions
                   <const conversion::io::options::versioned::VersionedOptions>
                   &options) const override;
    };
} // namespace lodestone::minecraft::java::alpha::player

#endif // LODESTONE_ALPHAPLAYERIO_H
