//
// Created by Zero on 11/26/25.
//

#ifndef LODESTONE_JUNGLEANVILWORLDIO_H
#define LODESTONE_JUNGLEANVILWORLDIO_H


#include <Lodestone.Minecraft.Common/conversion/registry/Registries.h>

#include <Lodestone.Minecraft.Common/Identifiers.h>

#include <Lodestone.Conversion/Identifiers.h>
#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Conversion/registry/Registries.h>
#include <Lodestone.Conversion/registry/RegistryRelations.h>
#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilChunkIo.h"
#include "Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilRegionIo.h"
#include "Lodestone.Minecraft.Java/conversion/mcregion/McRegionPlayerIo.h"

#include <filesystem>

namespace lodestone::minecraft::java::anvil::jungle::world {

    class JungleAnvilWorldIo : public conversion::io::WorldIO<&identifiers::ANVIL_JUNGLE_WORLD_IO, const common::conversion::io::options::OptionPresets::CommonFilesystemOptions, const common::conversion::io::options::OptionPresets::CommonFilesystemOptions>,
    public conversion::registry::RegistryIdentifierRelations<
        conversion::registry::RegistryIdentifierRelation<&identifiers::NBT_PLAYER_IO, const mcregion::player::McRegionNbtPlayerIO, &identifiers::MCREGION_NBT_PLAYER_IO, conversion::registry::PlayerIORegistry>, // TODO we don't have a jungle anvil player type yet
        conversion::registry::RegistryIdentifierRelation<&identifiers::NBT_CHUNK_IO, const chunk::JungleAnvilChunkIO, &identifiers::ANVIL_JUNGLE_NBT_CHUNK_IO, conversion::registry::ChunkIORegistry>,
            conversion::registry::RegistryIdentifierRelation<&lodestone::conversion::identifiers::CHUNK_IO, const chunk::JungleAnvilChunkIO, &identifiers::ANVIL_JUNGLE_CHUNK_IO, conversion::registry::ChunkIORegistry>,
            conversion::registry::RegistryIdentifierRelation<&lodestone::minecraft::common::identifiers::io::REGION_IO, const region::JungleAnvilRegionIO, &identifiers::ANVIL_JUNGLE_REGION_IO, conversion::registry::RegionIORegistry>
        > {
      public:
        std::unique_ptr<level::world::World> read(const common::conversion::io::options::OptionPresets::CommonFilesystemOptions &options) const override;
        void write(level::world::World *w, const common::conversion::io::options::OptionPresets::CommonFilesystemOptions &options) const override;
    };

} // namespace lodestone::minecraft::java::anvil::jungle::world

#endif // LODESTONE_JUNGLEANVILWORLDIO_H
