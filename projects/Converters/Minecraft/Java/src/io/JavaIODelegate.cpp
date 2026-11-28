//
// Created by zero on 11/27/26.
//

#include "Lodestone.Minecraft.Java/io/JavaIODelegate.h"

#include <Lodestone.Conversion/io/options/fs/FilesystemPathOptions.h>
#include <Lodestone.Conversion/io/options/versioned/VersionedOptions.h>
#include <Lodestone.Conversion/registry/Registries.h>
#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>
#include "Lodestone.Minecraft.Java/io/JavaIOVersionResolver.h"

// TODO: Make these detect version and return false if unsupported.
bool lodestone::minecraft::java::io::JavaIODelegate::canReadWorld(const std::filesystem::path &path) {
    return true;
}

bool lodestone::minecraft::java::io::JavaIODelegate::canReadLevel(const std::filesystem::path &path) {
    return true;
}

std::unique_ptr<lodestone::level::world::World>
lodestone::minecraft::java::io::JavaIODelegate::readWorld(
    const conversion::io::options::fs::FilesystemPathOptions &filesystem,
    const conversion::io::options::versioned::VersionedOptions &version
) const {
    const auto worldVersion = static_cast<Version>(version.version);

    const auto &worldIo = resolveWorldIo(worldVersion);

    const options::JavaReadOptions readOptions = {
        .path = filesystem.path,
        .version = worldVersion,
    };

    if (!worldIo || !worldIo->read)
        throw std::runtime_error("No readable world format for version");

    return worldIo->read(readOptions);
}

void lodestone::minecraft::java::io::JavaIODelegate::writeWorld(
    const conversion::io::options::fs::FilesystemPathOptions &filesystem,
    const conversion::io::options::versioned::VersionedOptions &version,
    const std::unique_ptr<level::world::World> &world) const {
    const auto worldVersion = static_cast<Version>(version.version);

    const auto &worldIo = resolveWorldIo(worldVersion);

    const options::JavaWriteOptions writeOptions = {
        .path = filesystem.path,
        .version = worldVersion,
    };

    if (!worldIo || !worldIo->read)
        throw std::runtime_error("No readable world format for version");

    return worldIo->write(writeOptions, *world);
}
