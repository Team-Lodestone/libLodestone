/** @file InfdevLevelData.h
*
* @author Zero_DSRS_VX
* @date 3/29/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#ifndef LODESTONE_INFDEVLEVELDATA_H
#define LODESTONE_INFDEVLEVELDATA_H

#include <Lodestone.Minecraft.Common/world/data/LevelData.h>

namespace lodestone::minecraft::java::infdev::world::data {
    struct InfdevLevelData : common::world::data::LevelData {
        std::unique_ptr<level::properties::AbstractProperty>
getProperty(const std::string &name) override;

        explicit InfdevLevelData() {
            // TODO: Review
        }
    };
}

#endif //LODESTONE_INFDEVLEVELDATA_H
