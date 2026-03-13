//
// Created by Zero on 11/20/25.
//

#include "Lodestone.Minecraft.Java/alpha/AlphaWorld.h"

namespace lodestone::minecraft::java::alpha::world {
    AlphaWorld::AlphaWorld(const std::string &name, data::AlphaLevelData levelData) : MinecraftWorld(name, levelData) {}

    AlphaWorld::AlphaWorld(const std::string &name) : MinecraftWorld(name, data::AlphaLevelData()) {
    }
} // namespace lodestone::minecraft::java::alpha::world