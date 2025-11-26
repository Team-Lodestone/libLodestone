//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_JUNGLEANVILCHUNKIO_H
#define LODESTONE_JUNGLEANVILCHUNKIO_H
#include <Lodestone.Conversion/chunk/ChunkIO.h>
#include <libnbt++/tag_compound.h>

#include <Lodestone.Minecraft.Common/io/chunk/NbtChunkIo.h>

namespace lodestone::minecraft::java::anvil::jungle::chunk {
    // 1.2.1+
    class JungleAnvilChunkIO : public common::io::chunk::NbtChunkIO {
      public:
        static constexpr int CHUNK_WIDTH = 16;
        static constexpr int CHUNK_DEPTH = 16;

        std::unique_ptr<level::chunk::Chunk> read(nbt::tag_compound &chunk,
                                                  int version) const override;

        nbt::tag_compound write(level::chunk::Chunk *c,
                                const level::types::Vec2i &coords,
                                int version) const override;

        std::unique_ptr<lodestone::level::chunk::Chunk>
        read(std::istream &in, int version) const override;

        void write(lodestone::level::chunk::Chunk *c,
                   const level::types::Vec2i &coords, int version,
                   std::ostream &out) const override;
    };
} // namespace lodestone::minecraft::java::anvil::jungle::chunk

#endif // LODESTONE_JUNGLEANVILCHUNKIO_H
