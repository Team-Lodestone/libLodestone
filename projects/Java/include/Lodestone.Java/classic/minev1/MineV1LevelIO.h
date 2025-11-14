//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_MINEV1CHUNKIO_H
#define LODESTONE_MINEV1CHUNKIO_H
#include <Lodestone.Conversion/level/LevelIO.h>

namespace lodestone::java::classic::minev1 {
    class MineV1LevelIO : public lodestone::conversion::level::LevelIO {
    public:
        static constexpr int WIDTH = 256;
        static constexpr int HEIGHT = 64;
        static constexpr int DEPTH = 256;

        std::unique_ptr<level::Level> read(uint8_t *data, int version) const override;

        uint8_t *write(level::Level *l, int version) const override;

        size_t getSize(level::Level *l, int version) const override;

        void write(level::Level *l, uint8_t *out, int version) const override;
    };
}

#endif //LODESTONE_MINEV1CHUNKIO_H