/** @file MineV3WorldWriteOptions.h
*
* @author Zero_DSRS_VX
* @date 3/23/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#ifndef LODESTONE_MINEV3WORLDWRITEOPTIONS_H
#define LODESTONE_MINEV3WORLDWRITEOPTIONS_H

#include <Lodestone.Common/registry/Identifier.h>
#include <Lodestone.Level/world/World.h>

#include <Lodestone.Conversion/io/options/OptionsBuilder.h>

namespace lodestone::minecraft::java::classic::minev3::options {
    struct MineV3WorldWriteOptions : conversion::io::options::IOptions {
        lodestone::common::registry::Identifier level = level::world::World::Dimension::OVERWORLD;

        explicit MineV3WorldWriteOptions(const lodestone::common::registry::Identifier &level);
    };
} // namespace lodestone::minecraft::java::classic::minev3::options

#endif //LODESTONE_MINEV3WORLDWRITEOPTIONS_H