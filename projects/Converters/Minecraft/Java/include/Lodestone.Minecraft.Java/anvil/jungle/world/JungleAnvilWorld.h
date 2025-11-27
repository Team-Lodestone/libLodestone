//
// Created by Zero on 11/26/25.
//

#ifndef LODESTONE_JUNGLEANVILWORLD_H
#define LODESTONE_JUNGLEANVILWORLD_H
#include "Lodestone.Minecraft.Java/mcregion/world/McRegionWorld.h"

#include <Lodestone.Conversion/world/WorldIO.h>

namespace lodestone::minecraft::java::anvil::jungle::world {
    class JungleAnvilWorld : public mcregion::world::McRegionWorld {
      public:
        explicit JungleAnvilWorld(const std::string &name);
    };
} // namespace lodestone::minecraft::java::anvil::jungle::world

#endif // LODESTONE_JUNGLEANVILWORLD_H
