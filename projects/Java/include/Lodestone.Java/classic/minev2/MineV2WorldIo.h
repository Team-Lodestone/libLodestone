//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#ifndef LODESTONE_MINEV2WORLDIO_H
#define LODESTONE_MINEV2WORLDIO_H
#include <Lodestone.Conversion/level/LevelIO.h>
#include <Lodestone.Conversion/world/FileWorldIo.h>
#include <Lodestone.Conversion/world/WorldIO.h>

namespace lodestone::java::classic::minev2 {
    class MineV2WorldIO : public lodestone::conversion::world::FileWorldIO {
    public:
        static constexpr uint32_t SIGNATURE = 0x271BB788;

        std::unique_ptr<level::world::World> read(uint8_t *data, int version) const override;

        uint8_t *write(level::world::World *w, int version) const override;

        size_t getSize(level::world::World *w, int version) const override;

        const lodestone::conversion::level::PlayerIO *getLevelIO(int version) const override;
    };
}

#endif //LODESTONE_MINEV2WORLDIO_H