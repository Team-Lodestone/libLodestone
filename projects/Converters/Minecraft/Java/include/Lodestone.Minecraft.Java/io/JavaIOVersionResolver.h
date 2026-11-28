//
// Created by zero on 11/27/26.
//

#ifndef LODESTONE_JAVA_IO_VERSION_RESOLVER_H
#define LODESTONE_JAVA_IO_VERSION_RESOLVER_H

#include <functional>
#include <memory>
#include <stdexcept>
#include <vector>
#include <filesystem>
#include <fstream>

#include <libnbt++/io/izlibstream.h>
#include <Lodestone.Level/world/World.h>

#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/Version.h"
#include "Lodestone.Minecraft.Java/conversion/alpha/AlphaWorldIo.h"
#include "Lodestone.Minecraft.Java/conversion/classic/minev1/MineV1LevelIo.h"
#include "Lodestone.Minecraft.Java/conversion/classic/minev2/MineV2LevelIo.h"
#include "Lodestone.Minecraft.Java/conversion/indev/McLevelLevelIo.h"
#include "Lodestone.Minecraft.Java/conversion/infdev/InfdevWorldIo.h"
#include "Lodestone.Minecraft.Java/conversion/mcregion/McRegionWorldIo.h"

namespace lodestone::minecraft::java::io {
    namespace options {
        struct JavaReadOptions {
            std::filesystem::path path;
            Version version;
        };

        struct JavaWriteOptions {
            std::filesystem::path path;
            Version version;
        };
    }

    struct VersionRange {
        Version first;
        Version last;

        [[nodiscard]]
        constexpr bool contains(const Version version) const {
            return version >= first && version <= last;
        }
    };

    struct WorldIoDescriptor {
        const lodestone::common::registry::Identifier *identifier;

        std::vector<VersionRange> ranges;

        std::function<
            std::unique_ptr<level::world::World>(
                const options::JavaReadOptions &
            )
        > read;

        std::function<void(
            const options::JavaWriteOptions &,
            level::world::World &
        )> write;

        [[nodiscard]]
        bool supports(const Version version) const {
            for (const auto &range: ranges) {
                if (range.contains(version))
                    return true;
            }

            return false;
        }
    };

    struct LevelIoDescriptor {
        const lodestone::common::registry::Identifier *identifier;

        std::vector<VersionRange> ranges;

        std::function<
            std::unique_ptr<level::Level>(
                const options::JavaReadOptions &
            )
        > read;

        std::function<void(
            const options::JavaWriteOptions &,
            const level::Level &
        )> write;

        [[nodiscard]]
        bool supports(const Version version) const {
            for (const auto &range: ranges) {
                if (range.contains(version))
                    return true;
            }

            return false;
        }
    };

    namespace WorldIOs {
        inline const std::vector<WorldIoDescriptor> DESCRIPTORS = {

            // Infdev 20100607 - 20100618
            {
                .identifier = &identifiers::ALPHA_WORLD_IO,
                .ranges = {
                    {.first = Version::inf20100607, .last = Version::inf20100618},
                    {.first = Version::inf20100625_1917, .last = Version::inf20100629}
                },

                .read = [](const options::JavaReadOptions &options) {
                    const auto *io =
                            conversion::registry::WorldIORegistry::getInstance()
                            .getAs<const alpha::world::AlphaWorldIo>(
                                identifiers::ALPHA_WORLD_IO
                            );

                    if (!io)
                        throw std::runtime_error("Infdev WorldIO unavailable");

                    return io->read(
                        common::conversion::io::options::OptionPresets::CommonFilesystemOptions{
                            conversion::io::options::fs::FilesystemPathOptions{
                                options.path
                            },
                            conversion::io::options::versioned::VersionedOptions{
                                static_cast<int>(options.version)
                            }
                        }
                    );
                },
                .write = [](const options::JavaWriteOptions &options, level::world::World &wld) {
                    const auto *io =
                            conversion::registry::WorldIORegistry::getInstance()
                            .getAs<const alpha::world::AlphaWorldIo>(
                                identifiers::ALPHA_WORLD_IO
                            );

                    if (!io)
                        throw std::runtime_error("Infdev WorldIO unavailable");

                    return io->write(&wld,
                                     common::conversion::io::options::OptionPresets::CommonFilesystemOptions{
                                         conversion::io::options::fs::FilesystemPathOptions{
                                             options.path
                                         },
                                         conversion::io::options::versioned::VersionedOptions{
                                             static_cast<int>(options.version)
                                         }
                                     });
                }
            },

            // Infdev 20100624
            {
                .identifier = &identifiers::INF_624_WORLD_IO,
                .ranges = {
                    {.first = Version::inf20100624, .last = Version::inf20100624}
                },

                .read = [](const options::JavaReadOptions &options) {
                    const auto *io =
                            conversion::registry::WorldIORegistry::getInstance()
                            .getAs<const infdev::world::InfdevWorldIo>(
                                identifiers::INF_624_WORLD_IO
                            );

                    if (!io)
                        throw std::runtime_error("Infdev 20100624 WorldIO unavailable");

                    return io->read(
                        common::conversion::io::options::OptionPresets::CommonFilesystemOptions{
                            conversion::io::options::fs::FilesystemPathOptions{
                                options.path
                            },
                            conversion::io::options::versioned::VersionedOptions{
                                static_cast<int>(options.version)
                            }
                        }
                    );
                },
                .write = [](const options::JavaWriteOptions &options, level::world::World &wld) {
                    const auto *io =
                            conversion::registry::WorldIORegistry::getInstance()
                            .getAs<const infdev::world::InfdevWorldIo>(
                                identifiers::INF_624_WORLD_IO
                            );

                    if (!io)
                        throw std::runtime_error("Infdev 20100624 WorldIO unavailable");

                    return io->write(&wld,
                                     common::conversion::io::options::OptionPresets::CommonFilesystemOptions{
                                         conversion::io::options::fs::FilesystemPathOptions{
                                             options.path
                                         },
                                         conversion::io::options::versioned::VersionedOptions{
                                             static_cast<int>(options.version)
                                         }
                                     });
                }
            },

            // Alpha
            {
                .identifier = &identifiers::ALPHA_WORLD_IO,
                .ranges = {
                    {.first = Version::a1_0_1, .last = Version::a1_2_0}
                },

                .read = [](const options::JavaReadOptions &options) {
                    const auto *io =
                            conversion::registry::WorldIORegistry::getInstance()
                            .getAs<const alpha::world::AlphaWorldIo>(
                                identifiers::ALPHA_WORLD_IO
                            );

                    if (!io)
                        throw std::runtime_error("Alpha WorldIO unavailable");

                    return io->read(
                        common::conversion::io::options::OptionPresets::CommonFilesystemOptions{
                            conversion::io::options::fs::FilesystemPathOptions{
                                options.path
                            },
                            conversion::io::options::versioned::VersionedOptions{
                                static_cast<int>(options.version)
                            }
                        }
                    );
                },

                .write = [](const options::JavaWriteOptions &options, level::world::World &wld) {
                    const auto *io =
                            conversion::registry::WorldIORegistry::getInstance()
                            .getAs<const alpha::world::AlphaWorldIo>(
                                identifiers::ALPHA_WORLD_IO
                            );

                    if (!io)
                        throw std::runtime_error("Alpha WorldIO unavailable");

                    return io->write(&wld,
                                     common::conversion::io::options::OptionPresets::CommonFilesystemOptions{
                                         conversion::io::options::fs::FilesystemPathOptions{
                                             options.path
                                         },
                                         conversion::io::options::versioned::VersionedOptions{
                                             static_cast<int>(options.version)
                                         }
                                     });
                }
            },

            // McRegion
            {
                .identifier = &identifiers::MCREGION_WORLD_IO,
                .ranges = {
                    {.first = Version::b1_3, .last = Version::r1_2_1}
                },

                .read = [](const options::JavaReadOptions &options) {
                    const auto *io =
                            conversion::registry::WorldIORegistry::getInstance()
                            .getAs<const mcregion::world::McRegionWorldIo>(
                                identifiers::MCREGION_WORLD_IO
                            );

                    if (!io)
                        throw std::runtime_error("McRegion WorldIO unavailable");

                    return io->read(
                        common::conversion::io::options::OptionPresets::CommonFilesystemOptions{
                            conversion::io::options::fs::FilesystemPathOptions{
                                options.path
                            },
                            conversion::io::options::versioned::VersionedOptions{
                                static_cast<int>(options.version)
                            }
                        }
                    );
                },

                .write = [](const options::JavaWriteOptions &options, level::world::World &wld) {
                    const auto *io =
                            conversion::registry::WorldIORegistry::getInstance()
                            .getAs<const mcregion::world::McRegionWorldIo>(
                                identifiers::MCREGION_WORLD_IO
                            );

                    if (!io)
                        throw std::runtime_error("McRegion WorldIO unavailable");

                    return io->write(&wld,
                                     common::conversion::io::options::OptionPresets::CommonFilesystemOptions{
                                         conversion::io::options::fs::FilesystemPathOptions{
                                             options.path
                                         },
                                         conversion::io::options::versioned::VersionedOptions{
                                             static_cast<int>(options.version)
                                         }
                                     });
                }
            }
        };

        [[nodiscard]]
        inline const WorldIoDescriptor *resolve(const Version version) {
            for (const auto &descriptor: DESCRIPTORS) {
                if (descriptor.supports(version))
                    return &descriptor;
            }

            return nullptr;
        }
    }

    namespace LevelIOs {
        inline const std::vector<LevelIoDescriptor> DESCRIPTORS = {

            // Mine v1
            {
                .identifier = &identifiers::MINEV1_LEVEL_IO,
                .ranges = {
                    {.first = Version::rd132211, .last = Version::c0_0_12a_03}
                },

                .read = [](const options::JavaReadOptions &options) {
                    const auto *io =
                            conversion::registry::LevelIORegistry::getInstance()
                            .getAs<const classic::minev1::MineV1LevelIo>(
                                identifiers::MINEV1_LEVEL_IO
                            );

                    if (!io)
                        throw std::runtime_error("Mine V1 LevelIO unavailable");

                    std::ifstream strm(options.path, std::ios::binary);
                    zlib::izlibstream zstrm(strm);

                    return io->read(
                        common::conversion::io::options::OptionPresets::CommonReadOptions{
                            conversion::io::options::fs::file::FileReaderOptions{
                                zstrm
                            },
                            conversion::io::options::versioned::VersionedOptions{
                                static_cast<int>(options.version)
                            }
                        }
                    );
                }
            },

            // Mine v2
            {
                .identifier = &identifiers::MINEV2_LEVEL_IO,
                .ranges = {
                    {.first = Version::c0_0_13a, .last = Version::c0_0_13a_03}
                },

                .read = [](const options::JavaReadOptions &options) {
                    const auto *io =
                            conversion::registry::LevelIORegistry::getInstance()
                            .getAs<const classic::minev2::MineV2LevelIo>(
                                identifiers::MINEV2_LEVEL_IO
                            );

                    if (!io)
                        throw std::runtime_error("Mine V2 LevelIO unavailable");

                    std::ifstream strm(options.path, std::ios::binary);
                    zlib::izlibstream zstrm(strm);

                    return io->read(
                        common::conversion::io::options::OptionPresets::CommonReadOptions{
                            conversion::io::options::fs::file::FileReaderOptions{
                                zstrm
                            },
                            conversion::io::options::versioned::VersionedOptions{
                                static_cast<int>(options.version)
                            }
                        }
                    );
                }
            },

            // Mine v3
            // TODO: Enable when Mine v3 support is finalized.
            /*
            {
                .identifier = &identifiers::MINEV3_LEVEL_IO,
                .ranges = {
                    {Version::c0_0_14a, Version::c0_30_CPE}
                }
            },
            */

            // Indev
            {
                .identifier = &identifiers::MCLEVEL_LEVEL_IO,
                .ranges = {
                    {.first = Version::in20091223_1457, .last = Version::in20100219}
                },

                .read = [](const options::JavaReadOptions &options) {
                    const auto *io =
                            conversion::registry::LevelIORegistry::getInstance()
                            .getAs<const indev::McLevelLevelIo>(
                                identifiers::MCLEVEL_LEVEL_IO
                            );

                    if (!io)
                        throw std::runtime_error("McLevel LevelIO unavailable");

                    std::ifstream strm(options.path, std::ios::binary);
                    zlib::izlibstream zstrm(strm);

                    return io->read(
                        common::conversion::io::options::OptionPresets::CommonReadOptions{
                            conversion::io::options::fs::file::FileReaderOptions{
                                zstrm
                            },
                            conversion::io::options::versioned::VersionedOptions{
                                static_cast<int>(options.version)
                            }
                        }
                    );
                }
            }
        };

        [[nodiscard]]
        inline const LevelIoDescriptor *resolve(const Version version) {
            for (const auto &descriptor: DESCRIPTORS) {
                if (descriptor.supports(version))
                    return &descriptor;
            }

            return nullptr;
        }
    }

    [[nodiscard]]
    inline const WorldIoDescriptor *resolveWorldIo(const Version version) {
        return WorldIOs::resolve(version);
    }

    [[nodiscard]]
    inline const LevelIoDescriptor *resolveLevelIo(const Version version) {
        return LevelIOs::resolve(version);
    }
}

#endif // LODESTONE_JAVA_IO_VERSION_RESOLVER_H
