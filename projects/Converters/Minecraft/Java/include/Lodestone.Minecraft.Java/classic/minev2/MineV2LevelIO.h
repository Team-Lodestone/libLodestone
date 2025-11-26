//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_MINEV2LEVELIO_H
#define LODESTONE_MINEV2LEVELIO_H
#include <Lodestone.Conversion/level/LevelIO.h>

namespace lodestone::minecraft::java::classic::minev2 {
    class MineV2LevelIO : public lodestone::conversion::level::LevelIO {
      public:
        std::unique_ptr<lodestone::level::Level>
        read(std::istream &in, int version) const override;

        void write(lodestone::level::Level *l, int version,
                   std::ostream &out) const override;
    };
} // namespace lodestone::minecraft::java::classic::minev2

#endif // LODESTONE_MINEV2LEVELIO_H