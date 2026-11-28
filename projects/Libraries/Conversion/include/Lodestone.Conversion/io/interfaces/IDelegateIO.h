//
// Created by Zero_DSRS_VX on 11/27/26 using PC.
//
#ifndef LODESTONE_IDELEGATEIO_H
#define LODESTONE_IDELEGATEIO_H
#include <filesystem>

#include "Lodestone.Conversion/io/IObjectIo.h"
#include "Lodestone.Conversion/io/options/versioned/VersionedOptions.h"
#include <Lodestone.Level/world/World.h>

#include "Lodestone.Conversion/io/options/fs/FilesystemPathOptions.h"

namespace lodestone::conversion::io::interfaces {
    class IDelegateIO : virtual public IObjectIO {
    public:
        // TODO: This is weird af
        virtual bool canReadWorld(const std::filesystem::path &path) = 0;

        virtual bool canReadLevel(const std::filesystem::path &path) = 0;

        [[nodiscard]] virtual std::unique_ptr<level::world::World> readWorld(
            const options::fs::FilesystemPathOptions &filesystem,
            const options::versioned::VersionedOptions &version
        ) const = 0;

        // TODO: Replace return type with Result or something
        virtual void writeWorld(const options::fs::FilesystemPathOptions &filesystem,
                                const options::versioned::VersionedOptions &version,
                                const std::unique_ptr<level::world::World> &world) const
        = 0;
    };
}

#endif // LODESTONE_IDELEGATEIO_H
