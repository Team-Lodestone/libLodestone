//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#ifndef LODESTONE_MINEV2WORLDIO_H
#define LODESTONE_MINEV2WORLDIO_H
#include "Lodestone.Level/conversion/level/LevelIO.h"
#include "Lodestone.Level/conversion/world/FileWorldIo.h"
#include "Lodestone.Level/conversion/world/WorldIO.h"

namespace lodestone::java::classic::minev2 {
    class MineV2WorldIO : public level::conversion::world::FileWorldIO {
    public:
        static constexpr uint32_t SIGNATURE = 0x271BB788;

        level::world::World *read(uint8_t *data, int version) const override;

        uint8_t *write(level::world::World *w, int version) const override;

        size_t getSize(level::world::World *w, int version) const override;

        const lodestone::level::conversion::level::LevelIO *getLevelIO(int version) const override;
    };
}

#endif //LODESTONE_MINEV2WORLDIO_H
