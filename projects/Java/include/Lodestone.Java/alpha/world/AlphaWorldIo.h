//
// Created by Zero on 11/20/25.
//

#ifndef LODESTONE_JAVA_ALPHAWORLDIO_H
#define LODESTONE_JAVA_ALPHAWORLDIO_H
#include <Lodestone.Conversion/world/DirectoryWorldIo.h>

namespace lodestone::java::alpha::world {

    class AlphaWorldIo final : public conversion::world::DirectoryWorldIO {
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

} // namespace lodestone::java::alpha::world

#endif // LODESTONE_JAVA_ALPHAWORLDIO_H
