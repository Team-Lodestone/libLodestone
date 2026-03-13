//
// Created by Zero on 11/20/25.
//

#ifndef LODESTONE_JAVA_ALPHAWORLD_H
#define LODESTONE_JAVA_ALPHAWORLD_H
#include "Lodestone.Minecraft.Java/alpha/AlphaLevelData.h"

#include <Lodestone.Level/world/World.h>

#include <Lodestone.Minecraft.Common/world/MinecraftWorld.h>

namespace lodestone::minecraft::java::alpha::world {

    class AlphaWorld final : public common::world::MinecraftWorld<data::AlphaLevelData> {
      public:
        explicit AlphaWorld(const std::string &name, data::AlphaLevelData levelData);
        explicit AlphaWorld(const std::string &name);
    };

} // namespace lodestone::minecraft::java::alpha::world

#endif // LODESTONE_JAVA_ALPHAWORLD_H
