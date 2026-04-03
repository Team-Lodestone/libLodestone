/** @file InfdevLevelData.cpp
*
* @author Zero_DSRS_VX
* @date 3/29/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#include "Lodestone.Minecraft.Java/infdev/InfdevLevelData.h"

namespace lodestone::minecraft::java::infdev::world {
    std::unique_ptr<level::properties::AbstractProperty> data::InfdevLevelData::getProperty(const std::string &name) {
        switch (lodestone::common::util::Math::fnv1a64(name.data(), name.length())) {
            default:
                return LevelData::getProperty(name);
        }
    }
}
