//
// Created by Zero on 11/26/25.
//

#ifndef LODESTONE_JUNGLEANVILWORLD_H
#define LODESTONE_JUNGLEANVILWORLD_H
#include "Lodestone.Minecraft.Java/mcregion/McRegionWorld.h"

#include "Lodestone.Minecraft.Java/internal/Exports.h"

namespace lodestone::minecraft::java::anvil::jungle::world {
    class LODESTONE_MINECRAFT_JAVA_API JungleAnvilWorld : public mcregion::world::McRegionWorld {
      public:
        explicit JungleAnvilWorld(const std::string &name);
    };
} // namespace lodestone::minecraft::java::anvil::jungle::world

#endif // LODESTONE_JUNGLEANVILWORLD_H
