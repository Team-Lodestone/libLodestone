//
// Created by DexrnZacAttack on 11/26/25 using zPc-i2.
//
#ifndef LODESTONE_JUNGLEANVILREGIONIO_H
#define LODESTONE_JUNGLEANVILREGIONIO_H
#include <Lodestone.Conversion/Identifiers.h>
#include <Lodestone.Conversion/registry/Registries.h>
#include <Lodestone.Conversion/registry/RegistryRelations.h>

#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilChunkIo.h"

#include <Lodestone.Minecraft.Common/region/Region.h>
#include <Lodestone.Minecraft.Common/conversion/io/ObjectIOs.h>

namespace lodestone::minecraft::java::anvil::jungle::region {
    class JungleAnvilRegionIO : public common::conversion::io::RegionIO<&identifiers::ANVIL_JUNGLE_REGION_IO, const common::conversion::io::options::OptionPresets::CommonChunkReadOptions, const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions>,
    conversion::registry::RegistryIdentifierRelations<
        conversion::registry::RegistryIdentifierRelation<&lodestone::conversion::identifiers::CHUNK_IO, const chunk::JungleAnvilChunkIO, &identifiers::ANVIL_JUNGLE_CHUNK_IO, conversion::registry::ChunkIORegistry>
        > {
      public:
        static constexpr int CHUNK_COUNT = 1024;
        static constexpr int SECTOR_SIZE = 4096;

        std::unique_ptr<common::region::Region> read(const common::conversion::io::options::OptionPresets::CommonChunkReadOptions &options) const override;

        // We take coords here so we don't have to convert our existing Level
        // into a Region. The coords are enough information to correctly write
        // the chunks
        void write(lodestone::level::Level *c, const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions &options) const override;
    };
} // namespace lodestone::minecraft::java::anvil::jungle::region

#endif // LODESTONE_ANVILREGIONIO_H