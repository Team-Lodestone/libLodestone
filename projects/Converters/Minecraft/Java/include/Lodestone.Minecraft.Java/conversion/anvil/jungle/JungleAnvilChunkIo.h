//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_JUNGLEANVILCHUNKIO_H
#define LODESTONE_JUNGLEANVILCHUNKIO_H
#include <Lodestone.Conversion/registry/Registries.h>
#include <Lodestone.Conversion/registry/RegistryRelations.h>

#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Minecraft.Common/conversion/io/ObjectIOs.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"

#include <libnbt++/tag_compound.h>
#include "Lodestone.Minecraft.Java/internal/Exports.h"

namespace lodestone::minecraft::java::anvil::jungle::chunk {
    class JungleAnvilNbtChunkIO;

    // 1.2.1+
    class LODESTONE_MINECRAFT_JAVA_API JungleAnvilChunkIO : public conversion::io::ChunkIO<&identifiers::ANVIL_JUNGLE_CHUNK_IO, const common::conversion::io::options::OptionPresets::CommonReadOptions, const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions>,
    conversion::registry::RegistryIdentifierRelations<
        conversion::registry::RegistryIdentifierRelation<&identifiers::NBT_CHUNK_IO, const chunk::JungleAnvilNbtChunkIO, &identifiers::ANVIL_JUNGLE_NBT_CHUNK_IO, conversion::registry::ChunkIORegistry>
    > {
      public:
        static constexpr int CHUNK_WIDTH = 16;
        static constexpr int CHUNK_DEPTH = 16;
        static constexpr int SECTION_HEIGHT = 16;

        std::unique_ptr<level::chunk::Chunk> read(const common::conversion::io::options::OptionPresets::CommonReadOptions &options) const override;
        void write(level::chunk::Chunk *chunk, const common::conversion::io::options::OptionPresets::CommonChunkWriteOptions &options) const override;
    };

    class LODESTONE_MINECRAFT_JAVA_API JungleAnvilNbtChunkIO : public common::conversion::io::NbtChunkIO<&identifiers::ANVIL_JUNGLE_NBT_CHUNK_IO, const common::conversion::io::options::OptionPresets::CommonNbtReadOptions, const common::conversion::io::options::OptionPresets::CommonChunkOptions>,
    conversion::registry::RegistryIdentifierRelations<
    conversion::registry::RegistryIdentifierRelation<&lodestone::conversion::identifiers::CHUNK_IO, const chunk::JungleAnvilChunkIO, &identifiers::ANVIL_JUNGLE_CHUNK_IO, conversion::registry::ChunkIORegistry>
> {
    public:
        std::unique_ptr<level::chunk::Chunk> read(const common::conversion::io::options::OptionPresets::CommonNbtReadOptions &options) const override;
        void write(level::chunk::Chunk *chunk,const common::conversion::io::options::OptionPresets::NbtOutputWriteOptions<const common::conversion::io::options::OptionPresets::CommonChunkOptions> &options) const override;
    };
} // namespace lodestone::minecraft::java::anvil::jungle::chunk

#endif // LODESTONE_JUNGLEANVILCHUNKIO_H
