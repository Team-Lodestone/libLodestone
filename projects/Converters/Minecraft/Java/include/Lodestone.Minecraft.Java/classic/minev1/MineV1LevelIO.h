//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_MINEV1CHUNKIO_H
#define LODESTONE_MINEV1CHUNKIO_H
#include <Lodestone.Conversion/level/LevelIO.h>

namespace lodestone::minecraft::java::classic::minev1 {
    class MineV1LevelIO : public lodestone::conversion::level::PlayerIO {
      public:
        static constexpr int WIDTH = 256;
        static constexpr int HEIGHT = 64;
        static constexpr int DEPTH = 256;

        size_t getSize(level::Level *l, int version) const override;

        std::unique_ptr<lodestone::level::Level>
        read(std::istream &in, int version) const override;

        void write(lodestone::level::Level *l, int version,
                   std::ostream &out) const override;
    };
} // namespace lodestone::minecraft::java::classic::minev1

#endif // LODESTONE_MINEV1CHUNKIO_H