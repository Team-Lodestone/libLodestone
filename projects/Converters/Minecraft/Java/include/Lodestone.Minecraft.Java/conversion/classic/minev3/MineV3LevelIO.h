/** @file MineV3LevelIO.h
*
* @author Zero_DSRS_VX
* @date 3/22/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/

#ifndef LODESTONE_MINEV3LEVELIO_H
#define LODESTONE_MINEV3LEVELIO_H

#include <Lodestone.Conversion/registry/Registries.h>

#include <Lodestone.Conversion/Identifiers.h>

#include <Lodestone.Conversion/registry/RegistryRelations.h>

#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"

namespace lodestone::minecraft::java::classic::minev3 {
    class MineV3WorldIO;

    class MineV3LevelIO : public conversion::io::LevelIO<
                              &identifiers::MINEV3_LEVEL_IO,
                              const common::conversion::io::options::OptionPresets::CommonReadOptions,
                              const common::conversion::io::options::OptionPresets::CommonWriteOptions>,
                          public conversion::registry::RegistryIdentifierRelations<
                              conversion::registry::RegistryIdentifierRelation<&conversion::identifiers::WORLD_IO, const
                                  MineV3WorldIO, &identifiers::MINEV3_WORLD_IO, conversion::registry::WorldIORegistry>
                          > {
    public:
        std::unique_ptr<level::Level>
        read(const common::conversion::io::options::OptionPresets::CommonReadOptions &options) const override;

        void write(level::Level *l,
                   const common::conversion::io::options::OptionPresets::CommonWriteOptions &options) const override;
    };
} // namespace lodestone::minecraft::java::classic::minev3

#endif //LODESTONE_MINEV3LEVELIO_H
