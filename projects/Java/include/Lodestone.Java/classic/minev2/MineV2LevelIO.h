//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_MINEV2LEVELIO_H
#define LODESTONE_MINEV2LEVELIO_H
#include <Lodestone.Level/conversion/level/LevelIO.h>

namespace lodestone::java::classic::minev2 {
    class MineV2LevelIO : public level::conversion::level::LevelIO {
    public:
        level::Level * read(uint8_t *data, int version) const override;

        uint8_t * write(level::Level *l, int version) const override;

        void write(level::Level *l, uint8_t *out, int version) const override;

        size_t getSize(level::Level* l, int version) const override;
    };
}

#endif //LODESTONE_MINEV2LEVELIO_H
