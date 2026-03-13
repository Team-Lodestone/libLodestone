//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONREGIONIO_H
#define LODESTONE_MCREGIONREGIONIO_H
#include <Lodestone.Conversion/Identifiers.h>
#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Conversion/registry/RegistryRelations.h>
#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/conversion/mcregion/McRegionChunkIo.h"

#include <cstdint>
#include <stddef.h>

#include <Lodestone.Level/region/Region.h>
#include <Lodestone.Level/types/Vec2.h>

namespace lodestone::minecraft::java::mcregion::region {
    class McRegionRegionIO : public conversion::io::RegionIO<&identifiers::MCREGION_REGION_IO, const common::conversion::io::options::OptionPresets::CommonChunkReadOptions, const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions>,
    public conversion::registry::RegistryIdentifierRelations<
        conversion::registry::RegistryIdentifierRelation<&conversion::identifiers::CHUNK_IO, const chunk::McRegionChunkIO, &identifiers::MCREGION_CHUNK_IO, conversion::registry::ChunkIORegistry>,
        conversion::registry::RegistryIdentifierRelation<&identifiers::NBT_CHUNK_IO, const chunk::McRegionNbtChunkIO, &identifiers::MCREGION_NBT_CHUNK_IO, conversion::registry::ChunkIORegistry>
    > {
      public:
        static constexpr int CHUNK_COUNT = 1024;
        static constexpr int SECTOR_SIZE = 4096;

        std::unique_ptr<lodestone::level::region::Region>
        read(const common::conversion::io::options::OptionPresets::CommonChunkReadOptions &options) const override;

        // We take coords here so we don't have to convert our existing Level
        // into a Region. The coords are enough information to correctly write
        // the chunks
        void write(lodestone::level::Level *c, const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions &options) const override;
    };
} // namespace lodestone::minecraft::java::mcregion::region

#endif // LODESTONE_MCREGIONREGIONIO_H