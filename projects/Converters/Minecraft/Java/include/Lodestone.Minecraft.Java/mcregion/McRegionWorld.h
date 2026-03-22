//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONWORLD_H
#define LODESTONE_MCREGIONWORLD_H
#include "Lodestone.Minecraft.Java/mcregion/McRegionLevelData.h"

#include <Lodestone.Level/world/World.h>
#include "Lodestone.Minecraft.Java/internal/Exports.h"
#include <Lodestone.Minecraft.Common/world/MinecraftWorld.h>

namespace lodestone::minecraft::java::mcregion::world {
    class LODESTONE_MINECRAFT_JAVA_API McRegionWorld : public common::world::MinecraftWorld<data::McRegionLevelData> {
      public:
        explicit McRegionWorld(const std::string &name);

        std::string toString() const override {
            return std::format("McRegionWorld[name={}]",
                               m_name);
        }
    };
} // namespace lodestone::minecraft::java::mcregion::world

#endif // LODESTONE_MCREGIONWORLD_H
