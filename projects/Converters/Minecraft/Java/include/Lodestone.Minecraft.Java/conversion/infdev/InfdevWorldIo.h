/** @file InfdevWorldIo.h
*
* @author Zero_DSRS_VX
* @date 3/29/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#ifndef LODESTONE_INFDEVWORLDIO_H
#define LODESTONE_INFDEVWORLDIO_H

#include <Lodestone.Conversion/Identifiers.h>
#include <Lodestone.Conversion/io/ObjectIOs.h>
#include <Lodestone.Conversion/registry/RegistryRelations.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/conversion/infdev/InfdevZoneIo.h"

namespace lodestone::minecraft::java::infdev::world {
    class InfdevWorldIo :  public conversion::io::WorldIO<&identifiers::INF_624_WORLD_IO, const common::conversion::io::options::OptionPresets::CommonFilesystemOptions, const common::conversion::io::options::OptionPresets::CommonFilesystemOptions>,
    public conversion::registry::RegistryIdentifierRelations<
        conversion::registry::RegistryIdentifierRelation<&conversion::identifiers::LEVEL_IO, const zone::InfdevZoneIo, &identifiers::INF_624_ZONE_IO, conversion::registry::LevelIORegistry>
    > {
    public:
        std::unique_ptr<level::world::World> read(const common::conversion::io::options::OptionPresets::CommonFilesystemOptions &options) const override;
        void write(level::world::World *w, const common::conversion::io::options::OptionPresets::CommonFilesystemOptions &options) const override;
    };

}

#endif //LODESTONE_INFDEVWORLDIO_H
