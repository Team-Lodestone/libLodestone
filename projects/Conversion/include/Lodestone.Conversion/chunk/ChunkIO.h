//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_CHUNKIO_H
#define LODESTONE_CHUNKIO_H
#include <Lodestone.Level/chunk/Chunk.h>

namespace lodestone::conversion::chunk {
    class LODESTONE_API ChunkIO {
    public:
        virtual ~ChunkIO() = default;

        /** Reads data into a new Chunk */
        virtual std::unique_ptr<lodestone::level::chunk::Chunk> read(std::istream &in, int version) const = 0;

        /** Writes a chunk to data */
        virtual void write(lodestone::level::chunk::Chunk *c, const lodestone::level::types::Vec2i &coords, int version, std::ostream &out) const = 0;

        /** Gets the size of the chunk in bytes */ // todo needed???
        virtual size_t getSize(lodestone::level::chunk::Chunk *c, int version) const = 0;
    };
}

#endif //LODESTONE_CHUNKIO_H