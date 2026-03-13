//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONPLAYERIO_H
#define LODESTONE_MCREGIONPLAYERIO_H

#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Minecraft.Common/conversion/io/ObjectIOs.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/conversion/alpha/AlphaPlayerIo.h"

#include <libnbt++/tag_compound.h>

#include <Lodestone.Level/world/World.h>

namespace lodestone::minecraft::java::mcregion::player {
    class McRegionNbtPlayerIO;

    class McRegionPlayerIO : public conversion::io::PlayerIO<&identifiers::MCREGION_PLAYER_IO, const common::conversion::io::options::OptionPresets::CommonPlayerReadOptions, const lodestone::minecraft::common::conversion::io::options::OptionPresets::CommonWriteOptions>,
    conversion::registry::RegistryIdentifierRelations<
        conversion::registry::RegistryIdentifierRelation<&identifiers::NBT_PLAYER_IO, const McRegionNbtPlayerIO, &identifiers::MCREGION_NBT_PLAYER_IO, conversion::registry::PlayerIORegistry>
        >
    {
      public:
        std::unique_ptr<lodestone::level::entity::Player> read(const common::conversion::io::options::OptionPresets::CommonPlayerReadOptions &options) const override;
        void write(lodestone::level::entity::Player *p, const lodestone::minecraft::common::conversion::io::options::OptionPresets::CommonWriteOptions &options) const override;
    };

    class McRegionNbtPlayerIO : public common::conversion::io::NbtPlayerIO<&identifiers::MCREGION_NBT_PLAYER_IO, const common::conversion::io::options::OptionPresets::CommonNbtFilesystemReadOptions, const conversion::io::options::EmptyOptions>,
    conversion::registry::RegistryIdentifierRelations<
    conversion::registry::RegistryIdentifierRelation<&lodestone::conversion::identifiers::PLAYER_IO, const McRegionPlayerIO, &identifiers::MCREGION_PLAYER_IO, conversion::registry::PlayerIORegistry>
    > {
    public:
        std::unique_ptr<level::entity::Player> read(const common::conversion::io::options::OptionPresets::CommonNbtFilesystemReadOptions &options) const override;
        void write(level::entity::Player *c,const common::conversion::io::options::OptionPresets::NbtOutputWriteOptions<const conversion::io::options::EmptyOptions> &options) const override;
    };
} // namespace lodestone::minecraft::java::mcregion::player

#endif // LODESTONE_MCREGIONPLAYERIO_H
