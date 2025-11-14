//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_WORLDIO_H
#define LODESTONE_WORLDIO_H
#include <Lodestone.Level/world/World.h>
#include "Lodestone.Conversion/level/LevelIO.h"

namespace lodestone::conversion::world {
    class LODESTONE_API WorldIO {
    public:
        virtual ~WorldIO() = default;

        /** Gets the corresponding LevelIO */
        virtual const lodestone::conversion::level::LevelIO *getLevelIO(int version) const = 0;
    };
}

#endif //LODESTONE_WORLDIO_H