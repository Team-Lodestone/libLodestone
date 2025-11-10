//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_CHUNKIO_H
#define LODESTONE_CHUNKIO_H
#include "Lodestone.Level/chunk/Chunk.h"

namespace lodestone::level::conversion::chunk {
    class LODESTONE_API ChunkIO {
    public:
        virtual ~ChunkIO() = default;

        /** Reads data into a new Chunk */
        virtual lodestone::level::chunk::Chunk *read(uint8_t *data, size_t size, int version) const = 0;

        /** Writes a chunk to data */
        virtual uint8_t *write(lodestone::level::chunk::Chunk *c, int version) const = 0;

        /** Gets the size of the chunk in bytes */ // todo needed???
        virtual size_t getSize(lodestone::level::chunk::Chunk *c, int version) const = 0;
    };
}

#endif //LODESTONE_CHUNKIO_H