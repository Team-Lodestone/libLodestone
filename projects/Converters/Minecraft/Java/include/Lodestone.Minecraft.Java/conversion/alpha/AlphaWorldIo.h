//
// Created by Zero on 11/20/25.
//

#ifndef LODESTONE_JAVA_ALPHAWORLDIO_H
#define LODESTONE_JAVA_ALPHAWORLDIO_H
#include <Lodestone.Conversion/Identifiers.h>
#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Conversion/registry/RegistryRelations.h>
#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/conversion/alpha/AlphaPlayerIo.h"
#include "Lodestone.Minecraft.Java/conversion/mcregion/McRegionChunkIo.h"


namespace lodestone::minecraft::java::alpha::world {
    class AlphaWorldIo : public conversion::io::WorldIO<&identifiers::ALPHA_WORLD_IO, const common::conversion::io::options::OptionPresets::CommonFilesystemOptions, const common::conversion::io::options::OptionPresets::CommonFilesystemOptions>,
    public conversion::registry::RegistryIdentifierRelations<
            conversion::registry::RegistryIdentifierRelation<&conversion::identifiers::CHUNK_IO, const mcregion::chunk::McRegionChunkIO, &identifiers::MCREGION_CHUNK_IO, conversion::registry::ChunkIORegistry>,
            conversion::registry::RegistryIdentifierRelation<&conversion::identifiers::PLAYER_IO, const player::AlphaPlayerIO, &identifiers::ALPHA_PLAYER_IO, conversion::registry::PlayerIORegistry>,
            conversion::registry::RegistryIdentifierRelation<&identifiers::NBT_PLAYER_IO, const player::AlphaNbtPlayerIO, &identifiers::ALPHA_NBT_PLAYER_IO, conversion::registry::PlayerIORegistry>
        > {
      public:
        std::unique_ptr<level::world::World> read(const common::conversion::io::options::OptionPresets::CommonFilesystemOptions &options) const override;
        void write(level::world::World *w, const common::conversion::io::options::OptionPresets::CommonFilesystemOptions &options) const override;
    };
} // namespace lodestone::minecraft::java::alpha::world

#endif // LODESTONE_JAVA_ALPHAWORLDIO_H
