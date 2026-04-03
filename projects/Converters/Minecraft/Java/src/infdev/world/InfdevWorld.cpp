/** @file InfdevWorld.cpp
*
* @author Zero_DSRS_VX
* @date 3/29/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#include "Lodestone.Minecraft.Java/infdev/InfdevWorld.h"

namespace lodestone::minecraft::java::infdev::world {
    /**
     *
     * @param name Name of world
     * @param levelData Level data
     */
    InfdevWorld::InfdevWorld(const std::string &name, const data::InfdevLevelData &levelData) :
        MinecraftWorld(name, levelData) {

    }


    /**
     *
     * @param name Name of world
     */
    InfdevWorld::InfdevWorld(const std::string &name) :
        MinecraftWorld(name, data::InfdevLevelData()) {

    }
}
