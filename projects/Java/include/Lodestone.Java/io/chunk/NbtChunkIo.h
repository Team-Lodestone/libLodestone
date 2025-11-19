//
// Created by DexrnZacAttack on 11/16/25 using zPc-i2.
//
#ifndef LODESTONE_NBTCHUNKIO_H
#define LODESTONE_NBTCHUNKIO_H
#include <Lodestone.Conversion/chunk/ChunkIO.h>

namespace nbt {
    class tag_compound;
}

namespace lodestone::java::io::chunk {
    // TODO once I make common mc project this can be moved
    class NbtChunkIO : public conversion::chunk::ChunkIO {
        virtual std::unique_ptr<level::chunk::Chunk> read(nbt::tag_compound &chunk, int version) const = 0;

        virtual nbt::tag_compound write(level::chunk::Chunk *c, const level::types::Vec2i &coords, int version) const = 0;
    };
}

#endif //LODESTONE_NBTCHUNKIO_H
