//
// Created by DexrnZacAttack on 11/7/25 using zPc-i2.
//
#ifndef LODESTONE_DIRECTORYWORLDIO_H
#define LODESTONE_DIRECTORYWORLDIO_H
#include <filesystem>

#include "Lodestone.Conversion/world/WorldIO.h"
#include "Lodestone.Conversion/world/options/AbstractWorldReadOptions.h"
#include "Lodestone.Conversion/world/options/AbstractWorldWriteOptions.h"

namespace lodestone::conversion::world {
    class LODESTONE_API DirectoryWorldIO : public WorldIO {
      public:
        /** Reads data into a new World */
        virtual std::unique_ptr<lodestone::level::world::World>
        read(const std::filesystem::path &path, int version, const options::AbstractWorldReadOptions &options) const = 0;

        // TODO: this should allow for reading from VFS
        /** Writes a world to data */
        virtual void write(const std::filesystem::path &path,
                           lodestone::level::world::World *w,
                           int version, const options::AbstractWorldWriteOptions &options) const = 0;

        // TODO: this *should* allow for writing to a VFS
    };
} // namespace lodestone::conversion::world

#endif // LODESTONE_DIRECTORYWORLDIO_H