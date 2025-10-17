//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_CHUNKIO_H
#define LODESTONE_CHUNKIO_H
#include "Level.h"
#include "Chunk/Chunk.h"

namespace lodestone::level::conversion::level {
    class LODESTONE_API LevelIO {
    public:
        virtual ~LevelIO() = default;

        /** Reads data into a new Level */
        virtual Level *read(uint8_t *data) const = 0;
        /** Writes a level to data */
        virtual uint8_t *write(Level *l) const = 0;
        /** Gets the size of the level in bytes */
        virtual size_t getSize(Level *l) const = 0;
    };
}

#endif //LODESTONE_CHUNKIO_H
