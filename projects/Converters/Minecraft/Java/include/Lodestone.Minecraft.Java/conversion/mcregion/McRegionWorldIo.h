//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONWORLDIO_H
#define LODESTONE_MCREGIONWORLDIO_H

#include <Lodestone.Minecraft.Common/conversion/registry/Registries.h>

#include <Lodestone.Minecraft.Common/Identifiers.h>

#include <Lodestone.Conversion/registry/RegistryRelations.h>

#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/conversion/mcregion/McRegionChunkIo.h"
#include "Lodestone.Minecraft.Java/conversion/mcregion/McRegionPlayerIo.h"
#include "Lodestone.Minecraft.Java/conversion/mcregion/McRegionRegionIo.h"

#include <filesystem>

namespace lodestone::minecraft::java::mcregion::world {
    class McRegionWorldIo
        : public conversion::io::WorldIO<&identifiers::MCREGION_WORLD_IO, const common::conversion::io::options::OptionPresets::CommonFilesystemOptions, const common::conversion::io::options::OptionPresets::CommonFilesystemOptions>,
    public conversion::registry::RegistryIdentifierRelations< // allows us to do getByRelation<&identifiers::NBT_CHUNK_IO>() to get McRegionNbtChunkIO
        conversion::registry::RegistryIdentifierRelation<&identifiers::NBT_PLAYER_IO, const player::McRegionNbtPlayerIO, &identifiers::MCREGION_NBT_PLAYER_IO, conversion::registry::PlayerIORegistry>, // TODO we don't have a jungle anvil player type yet
        conversion::registry::RegistryIdentifierRelation<&identifiers::NBT_CHUNK_IO, const chunk::McRegionNbtChunkIO, &identifiers::MCREGION_NBT_CHUNK_IO, conversion::registry::ChunkIORegistry>,
        conversion::registry::RegistryIdentifierRelation<&lodestone::conversion::identifiers::CHUNK_IO, const chunk::McRegionChunkIO, &identifiers::MCREGION_CHUNK_IO, conversion::registry::ChunkIORegistry>,
        conversion::registry::RegistryIdentifierRelation<&lodestone::minecraft::common::identifiers::io::REGION_IO, const region::McRegionRegionIO, &identifiers::MCREGION_REGION_IO, conversion::registry::RegionIORegistry>
    > {
      public:
        std::unique_ptr<lodestone::level::world::World>
        read(const common::conversion::io::options::OptionPresets::CommonFilesystemOptions &options) const override;
        void write(lodestone::level::world::World *w, const common::conversion::io::options::OptionPresets::CommonFilesystemOptions &options) const override;
    };
} // namespace lodestone::minecraft::java::mcregion::world

#endif // LODESTONE_MCREGIONWORLDIO_H
