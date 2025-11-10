//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_WORLDIO_H
#define LODESTONE_WORLDIO_H
#include "Lodestone.Level/world/World.h"
#include "Lodestone.Level/conversion/level/LevelIO.h"

namespace lodestone::level::conversion::world {
    class LODESTONE_API WorldIO {
    public:
        virtual ~WorldIO() = default;

        /** Gets the size of the level in bytes */
        virtual size_t getSize(lodestone::level::world::World *w, int version) const = 0;

        /** Gets the corresponding LevelIO */
        virtual const lodestone::level::conversion::level::LevelIO *getLevelIO(int version) const = 0;
    };
}

#endif //LODESTONE_WORLDIO_H