//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONWORLDIO_H
#define LODESTONE_MCREGIONWORLDIO_H
#include <Lodestone.Conversion/world/DirectoryWorldIo.h>
#include <filesystem>

namespace lodestone::minecraft::java::mcr::world {
    class McRegionWorldIo
        : public lodestone::conversion::world::DirectoryWorldIO {
      public:
        const lodestone::conversion::level::PlayerIO *
        getLevelIO(int version) const override;

        std::unique_ptr<lodestone::level::world::World>
        read(const std::filesystem::path &path, int version,
             const conversion::world::options::AbstractWorldReadOptions
                 &options) const override;

        void write(const std::filesystem::path &path,
                   lodestone::level::world::World *w, int version,
                   const conversion::world::options::AbstractWorldWriteOptions
                       &options) const override;
    };
} // namespace lodestone::minecraft::java::mcr::world

#endif // LODESTONE_MCREGIONWORLDIO_H
