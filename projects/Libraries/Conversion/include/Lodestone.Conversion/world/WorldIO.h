//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_WORLDIO_H
#define LODESTONE_WORLDIO_H
#include "Lodestone.Conversion/chunk/ChunkIO.h"
#include "Lodestone.Conversion/level/LevelIO.h"
#include "Lodestone.Conversion/player/PlayerIO.h"
#include "Lodestone.Conversion/region/RegionIO.h"

#include <Lodestone.Level/world/World.h>

namespace lodestone::conversion::world {
    class LODESTONE_API WorldIO {
      public:
        virtual ~WorldIO() = default;

        /** Gets the corresponding LevelIO */
        virtual const lodestone::conversion::level::LevelIO *
        getLevelIO(int version) const = 0;

        /** Gets the corresponding ChunkIO */
        virtual const lodestone::conversion::chunk::ChunkIO *
        getChunkIO(int version) const = 0;

        /** Gets the corresponding RegionIO */
        virtual const lodestone::conversion::region::RegionIO *
        getRegionIO(int version) const = 0;

        /** Gets the corresponding PlayerIO */
        virtual const lodestone::conversion::player::PlayerIO *
        getPlayerIO(int version) const = 0;
    };
} // namespace lodestone::conversion::world

#endif // LODESTONE_WORLDIO_H