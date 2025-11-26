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
        /** Creates a new World from data in the all files inside the given path */
        virtual std::unique_ptr<lodestone::level::world::World>
        read(const std::filesystem::path &path, int version,
             const options::AbstractWorldReadOptions &options) const = 0;

        /** Writes a World to the given path */
        virtual void
        write(const std::filesystem::path &path,
              lodestone::level::world::World *w, int version,
              const options::AbstractWorldWriteOptions &options) const = 0;

        // TODO: this *should* allow for reading/writing to a VFS, for all things, but I need to figure out my own lib for that
    };
} // namespace lodestone::conversion::world

#endif // LODESTONE_DIRECTORYWORLDIO_H