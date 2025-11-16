//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_LEVELIO_H
#define LODESTONE_LEVELIO_H

#include "Lodestone.Level/Level.h"

namespace lodestone::conversion::level {
    class LODESTONE_API PlayerIO {
    public:
        virtual ~PlayerIO() = default;

        /** Reads data into a new Level */
        virtual std::unique_ptr<lodestone::level::Level> read(std::istream &in, int version) const = 0;

        /** Writes a level to data */
        virtual void write(lodestone::level::Level *l, int version, std::ostream &out) const = 0;

        /** Gets the size of the level in bytes */
        virtual size_t getSize(lodestone::level::Level *l, int version) const = 0;
    };
}

#endif //LODESTONE_LEVELIO_H