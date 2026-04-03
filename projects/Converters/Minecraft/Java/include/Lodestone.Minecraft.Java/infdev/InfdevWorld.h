/** @file InfdevWorld.h
*
* @author Zero_DSRS_VX
* @date 3/29/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#ifndef LODESTONE_INFDEVWORLD_H
#define LODESTONE_INFDEVWORLD_H
#include "Lodestone.Minecraft.Java/infdev/InfdevLevelData.h"
#include "Lodestone.Minecraft.Common/world/MinecraftWorld.h"

namespace lodestone::minecraft::java::infdev::world {
    class InfdevWorld final : public common::world::MinecraftWorld<data::InfdevLevelData> {
    public:
        explicit InfdevWorld(const std::string &name, const data::InfdevLevelData &levelData);
        explicit InfdevWorld(const std::string &name);
    };
}

#endif //LODESTONE_INFDEVWORLD_H
