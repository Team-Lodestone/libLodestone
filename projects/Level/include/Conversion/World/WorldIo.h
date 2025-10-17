//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_WORLDIO_H
#define LODESTONE_WORLDIO_H
#include "World/World.h"

namespace lodestone::level::conversion::world {
    class LODESTONE_API WorldIo {
    public:
        virtual ~WorldIo() = default;

        /** Reads data into a new World */
        virtual level::world::World *read(uint8_t *data) const = 0; // TODO: this should read from VFS
        /** Writes a world to data */
        virtual uint8_t *write(level::world::World *w) const = 0; // TODO: this *should* write to a VFS
        /** Gets the size of the level in bytes */
        virtual size_t getSize() const = 0;
    };
}

#endif //LODESTONE_WORLDIO_H
