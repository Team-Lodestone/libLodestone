//
// Created by Zero on 11/26/25.
//

#ifndef LODESTONE_JUNGLEANVILWORLDIO_H
#define LODESTONE_JUNGLEANVILWORLDIO_H
#include <Lodestone.Conversion/world/DirectoryWorldIo.h>
#include <Lodestone.Conversion/world/WorldIO.h>

#include <filesystem>

namespace lodestone::minecraft::java::anvil::jungle::world {

    class JungleAnvilWorldIo : public conversion::world::DirectoryWorldIO {
      public:
        const conversion::level::LevelIO *
        getLevelIO(int version) const override;

        std::unique_ptr<level::world::World>
        read(const std::filesystem::path &path, int version,
             const conversion::world::options::AbstractWorldReadOptions
                 &options) const override;

        void write(const std::filesystem::path &path, level::world::World *w,
                   int version,
                   const conversion::world::options::AbstractWorldWriteOptions
                       &options) const override;

        const conversion::chunk::ChunkIO *
        getChunkIO(int version) const override;

        const conversion::region::RegionIO *
        getRegionIO(int version) const override;

        const conversion::player::PlayerIO *
        getPlayerIO(int version) const override;
    };

} // namespace lodestone::minecraft::java::anvil::jungle::world

#endif // LODESTONE_JUNGLEANVILWORLDIO_H
