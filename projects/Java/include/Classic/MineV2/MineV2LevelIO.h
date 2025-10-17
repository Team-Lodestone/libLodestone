//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_MINEV2LEVELIO_H
#define LODESTONE_MINEV2LEVELIO_H
#include <Conversion/Level/LevelIO.h>

namespace lodestone::java::classic::minev2 {
    class MineV2LevelIO : public level::conversion::level::LevelIO {
    public:
        level::Level * read(uint8_t *data) const override;

        uint8_t * write(level::Level *l) const override;

        size_t getSize(level::Level* l) const override;
    };
}

#endif //LODESTONE_MINEV2LEVELIO_H
