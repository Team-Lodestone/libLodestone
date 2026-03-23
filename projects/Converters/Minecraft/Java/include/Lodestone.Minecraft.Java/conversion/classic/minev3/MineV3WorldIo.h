/** @file MineV3WorldIo.h
*
* @author Zero_DSRS_VX
* @date 3/23/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#ifndef LODESTONE_MINEV3WORLDIO_H
#define LODESTONE_MINEV3WORLDIO_H

#include <Lodestone.Conversion/registry/RegistryRelations.h>

#include <Lodestone.Conversion/registry/Registries.h>

#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/conversion/classic/minev3/options/MineV3WorldWriteOptions.h"

namespace lodestone::minecraft::java::classic::minev3 {
    class MineV3LevelIO;

    using MineV3WriteOptions = conversion::io::options::OptionsBuilder<
        options::MineV3WorldWriteOptions,
        conversion::io::options::fs::file::FileWriterOptions,
        conversion::io::options::versioned::VersionedOptions
    >;

    class MineV3WorldIO : public conversion::io::WorldIO<&identifiers::MINEV3_WORLD_IO, const common::conversion::io::options::OptionPresets::CommonReadOptions, const MineV3WriteOptions>,
    public conversion::registry::RegistryIdentifierRelations<
        conversion::registry::RegistryIdentifierRelation<&conversion::identifiers::LEVEL_IO, const MineV3LevelIO, &identifiers::MINEV3_LEVEL_IO, conversion::registry::LevelIORegistry>
    > {
    public:
        static constexpr int32_t SIGNATURE = 0x271BB788;

        std::unique_ptr<level::world::World> read(const common::conversion::io::options::OptionPresets::CommonReadOptions &options) const override;
        void write(level::world::World *w, const MineV3WriteOptions &options) const override;

        void write(level::world::World *w, const MineV3WriteOptions &options);
    };
} // namespace lodestone::minecraft::java::classic::minev3

#endif //LODESTONE_MINEV3WORLDIO_H