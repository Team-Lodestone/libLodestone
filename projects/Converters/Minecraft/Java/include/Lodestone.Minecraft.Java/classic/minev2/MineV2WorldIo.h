//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#ifndef LODESTONE_MINEV2WORLDIO_H
#define LODESTONE_MINEV2WORLDIO_H
#include <Lodestone.Conversion/level/LevelIO.h>
#include <Lodestone.Conversion/world/FileWorldIo.h>
#include <Lodestone.Conversion/world/WorldIO.h>

namespace lodestone::minecraft::java::classic::minev2 {
    class MineV2WorldIO : public lodestone::conversion::world::FileWorldIO {
      public:
        static constexpr uint32_t SIGNATURE = 0x271BB788;

        size_t getSize(level::world::World *w, int version) const override;

        const lodestone::conversion::level::PlayerIO *
        getLevelIO(int version) const override;

        std::unique_ptr<lodestone::level::world::World>
        read(std::istream &in, int version,
             const conversion::world::options::AbstractWorldReadOptions
                 &options) const override;

        void write(lodestone::level::world::World *w, int version,
                   std::ostream &out,
                   const conversion::world::options::AbstractWorldWriteOptions
                       &options) const override;
    };
} // namespace lodestone::minecraft::java::classic::minev2

#endif // LODESTONE_MINEV2WORLDIO_H