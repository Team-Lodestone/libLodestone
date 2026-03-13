//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/mcregion/McRegionWorld.h"

#include "Lodestone.Minecraft.Java/Identifiers.h"
#include <Lodestone.Common/util/Math.h>

namespace lodestone::minecraft::java::mcregion::world {
    McRegionWorld::McRegionWorld(const std::string &name)
        : MinecraftWorld(name, data::McRegionLevelData(0, 0, 0, false, false, 24000, false, 36000)) {}
} // namespace lodestone::minecraft::java::mcregion::world
