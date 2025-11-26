//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONCHUNKIO_H
#define LODESTONE_MCREGIONCHUNKIO_H
#include <Lodestone.Conversion/chunk/ChunkIO.h>
#include <libnbt++/tag_compound.h>

#include <Lodestone.Minecraft.Common/io/chunk/NbtChunkIo.h>

namespace lodestone::minecraft::java::mcregion::chunk {
    // TODO we can probably make all of these take an Options class and read
    // that
    class McRegionChunkIO : public common::io::chunk::NbtChunkIO {
      public:
        static constexpr int CHUNK_WIDTH = 16;
        static constexpr int CHUNK_DEPTH = 16;
        static constexpr int CHUNK_HEIGHT = 128;

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
} // namespace lodestone::minecraft::java::mcregion::chunk

#endif // LODESTONE_MCREGIONCHUNKIO_H
