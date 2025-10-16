//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_CHUNKIO_H
#define LODESTONE_CHUNKIO_H
#include "Chunk/Chunk.h"

namespace lodestone::level::conversion::chunk {
    class LODESTONE_API ChunkIO {
    public:
        virtual ~ChunkIO() = default;

        /** Reads data into a new Chunk */
        virtual level::chunk::Chunk *read(uint8_t *data) = 0;
        /** Writes a chunk to data */
        virtual uint8_t *write(level::chunk::Chunk *c) = 0;
        /** Gets the size of the chunk in bytes */
        virtual size_t getSize() = 0;
    };
}

#endif //LODESTONE_CHUNKIO_H
