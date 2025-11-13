//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONWORLDIO_H
#define LODESTONE_MCREGIONWORLDIO_H
#include <Lodestone.Level/conversion/world/DirectoryWorldIo.h>
#include <filesystem>

namespace lodestone::java::mcr::world {
    class McRegionWorldIo : public level::conversion::world::DirectoryWorldIO {
    public:
        const lodestone::level::conversion::level::LevelIO * getLevelIO(int version) const override;

        std::unique_ptr<lodestone::level::world::World> read(const std::filesystem::path &path, int version) const override;

        void write(const std::filesystem::path &path, lodestone::level::world::World *w, int version) const override;
    };
}

#endif //LODESTONE_MCREGIONWORLDIO_H
