/** @file InfdevPlayer.h
*
* @author Zero_DSRS_VX
* @date 3/29/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#ifndef LODESTONE_INFDEVPLAYER_H
#define LODESTONE_INFDEVPLAYER_H
#include <Lodestone.Minecraft.Common/player/MinecraftPlayer.h>

namespace lodestone::minecraft::java::infdev::world {
    class InfdevPlayer final : common::player::MinecraftPlayer {
    public:
        explicit InfdevPlayer(const std::string &name)
            : MinecraftPlayer(name) {
        }
    };
}

#endif //LODESTONE_INFDEVPLAYER_H
