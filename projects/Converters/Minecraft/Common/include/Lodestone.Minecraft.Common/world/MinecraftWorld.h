//
// Created by DexrnZacAttack on 11/22/25 using zPc-i2.
//
#ifndef LODESTONE_MINECRAFTWORLD_H
#define LODESTONE_MINECRAFTWORLD_H
#include <Lodestone.Level/world/World.h>

#include "Lodestone.Minecraft.Common/world/data/LevelData.h"

namespace lodestone::minecraft::common::world {
    template <typename LD = data::LevelData>
    requires std::is_base_of_v<data::LevelData, LD>
    class MinecraftWorld : public level::world::World {
      public:
        explicit MinecraftWorld(const std::string &name, LD levelData) : World(name), m_levelData(levelData) {}

      protected:
        LD m_levelData;
    };
} // namespace lodestone::minecraft::common::world

#endif // LODESTONE_MINECRAFTWORLD_H
