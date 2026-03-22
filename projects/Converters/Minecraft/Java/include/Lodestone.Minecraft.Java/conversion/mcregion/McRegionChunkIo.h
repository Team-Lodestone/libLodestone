//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONCHUNKIO_H
#define LODESTONE_MCREGIONCHUNKIO_H
#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Conversion/registry/RegistryRelations.h>

#include <libnbt++/tag_compound.h>

#include <Lodestone.Conversion/registry/Registries.h>
#include <Lodestone.Minecraft.Common/conversion/io/ObjectIOs.h>
#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/internal/Exports.h"

namespace lodestone::minecraft::java::mcregion::chunk {
    class McRegionNbtChunkIO;

    class LODESTONE_MINECRAFT_JAVA_API McRegionChunkIO : public conversion::io::ChunkIO<&identifiers::MCREGION_CHUNK_IO, const common::conversion::io::options::OptionPresets::CommonReadOptions, const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions>,
    public conversion::registry::RegistryIdentifierRelations<
        conversion::registry::RegistryIdentifierRelation<&identifiers::NBT_CHUNK_IO, const McRegionNbtChunkIO, &identifiers::MCREGION_NBT_CHUNK_IO, conversion::registry::ChunkIORegistry>
    > {
      public:
        static constexpr int CHUNK_WIDTH = 16;
        static constexpr int CHUNK_DEPTH = 16;
        static constexpr int CHUNK_HEIGHT = 128;

        std::unique_ptr<level::chunk::Chunk> read(const common::conversion::io::options::OptionPresets::CommonReadOptions &options) const override;
        void write(level::chunk::Chunk *c, const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions &options) const override;
    };

    class LODESTONE_MINECRAFT_JAVA_API McRegionNbtChunkIO : public common::conversion::io::NbtChunkIO<&identifiers::MCREGION_NBT_CHUNK_IO, const common::conversion::io::options::OptionPresets::CommonNbtReadOptions, const common::conversion::io::options::OptionPresets::CommonChunkOptions>,
    public conversion::registry::RegistryIdentifierRelations<
        conversion::registry::RegistryIdentifierRelation<&conversion::identifiers::CHUNK_IO, const McRegionChunkIO, &identifiers::MCREGION_CHUNK_IO, conversion::registry::ChunkIORegistry>
    > {
    public:
        std::unique_ptr<level::chunk::Chunk> read(const common::conversion::io::options::OptionPresets::CommonNbtReadOptions &options) const override;
        void write(level::chunk::Chunk *c, const common::conversion::io::options::OptionPresets::NbtOutputWriteOptions<const common::conversion::io::options::OptionPresets::CommonChunkOptions> &options) const override;
    };
} // namespace lodestone::minecraft::java::mcregion::chunk

#endif // LODESTONE_MCREGIONCHUNKIO_H
