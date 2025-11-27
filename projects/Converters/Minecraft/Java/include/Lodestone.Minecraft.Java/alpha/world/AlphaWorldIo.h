//
// Created by Zero on 11/20/25.
//

#ifndef LODESTONE_JAVA_ALPHAWORLDIO_H
#define LODESTONE_JAVA_ALPHAWORLDIO_H
#include <Lodestone.Conversion/world/DirectoryWorldIo.h>

namespace lodestone::minecraft::java::alpha::world {

    class AlphaWorldIo : public conversion::world::DirectoryWorldIO {
      public:
        const lodestone::conversion::level::LevelIO *
        getLevelIO(int version) const override;

        std::unique_ptr<lodestone::level::world::World>
        read(const std::filesystem::path &path, int version,
             const conversion::world::options::AbstractWorldReadOptions
                 &options) const override;

        void write(const std::filesystem::path &path,
                   lodestone::level::world::World *w, int version,
                   const conversion::world::options::AbstractWorldWriteOptions
                       &options) const override;

        const lodestone::conversion::chunk::ChunkIO *
        getChunkIO(int version) const override;

        const lodestone::conversion::region::RegionIO *
        getRegionIO(int version) const override;

        const lodestone::conversion::player::PlayerIO *
        getPlayerIO(int version) const override;
    };

} // namespace lodestone::minecraft::java::alpha::world

#endif // LODESTONE_JAVA_ALPHAWORLDIO_H
