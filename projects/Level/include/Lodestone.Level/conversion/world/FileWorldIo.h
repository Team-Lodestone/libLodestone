//
// Created by DexrnZacAttack on 11/7/25 using zPc-i2.
//
#ifndef LODESTONE_FILEWORLDIO_H
#define LODESTONE_FILEWORLDIO_H
#include "WorldIO.h"

namespace lodestone::level::conversion::world {
    class LODESTONE_API FileWorldIO : public WorldIO {
    public:
        /** Reads data into a new World */
        virtual lodestone::level::world::World *read(uint8_t *data, int version) const = 0; // TODO: this should read from VFS
        /** Writes a world to data */
        virtual uint8_t *write(lodestone::level::world::World *w, int version) const = 0; // TODO: this *should* write to a VFS
    };
}

#endif //LODESTONE_FILEWORLDIO_H
