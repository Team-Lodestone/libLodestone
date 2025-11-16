//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_MINEV2LEVELIO_H
#define LODESTONE_MINEV2LEVELIO_H
#include <Lodestone.Conversion/level/LevelIO.h>

namespace lodestone::java::classic::minev2 {
    class MineV2LevelIO : public lodestone::conversion::level::PlayerIO {
    public:

        size_t getSize(level::Level *l, int version) const override;

        std::unique_ptr<lodestone::level::Level> read(std::istream &in, int version) const override;

        void write(lodestone::level::Level *l, int version, std::ostream &out) const override;
    };
}

#endif //LODESTONE_MINEV2LEVELIO_H