//
// Created by DexrnZacAttack on 11/26/25 using zPc-i2.
//
#ifndef LODESTONE_JUNGLEANVILREGION_H
#define LODESTONE_JUNGLEANVILREGION_H
#include "Lodestone.Minecraft.Java/mcregion/McRegionRegion.h"

#include <Lodestone.Level/types/Vec2.h>
#include "Lodestone.Minecraft.Java/internal/Exports.h"

namespace lodestone::minecraft::java::anvil::jungle::region {
    class LODESTONE_MINECRAFT_JAVA_API JungleAnvilRegion final
        : public lodestone::minecraft::java::mcregion::region::McRegionRegion {
      public:
        explicit JungleAnvilRegion(const level::types::Vec2i &coords);
    };
} // namespace lodestone::minecraft::java::anvil::jungle::region

#endif // LODESTONE_JUNGLEANVILREGION_H
