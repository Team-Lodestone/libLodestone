//
// Created by Zero on 11/20/25.
//

#ifndef LODESTONE_JAVA_ALPHAWORLD_H
#define LODESTONE_JAVA_ALPHAWORLD_H
#include <Lodestone.Level/world/World.h>

#include <Lodestone.Minecraft.Common/world/MinecraftWorld.h>

namespace lodestone::minecraft::java::alpha::world {

    class AlphaWorld final : public common::world::MinecraftWorld {
      public:
        explicit AlphaWorld(const std::string &name);

      private:
        bool mSnowCovered = false;
    };

} // namespace lodestone::minecraft::java::alpha::world

#endif // LODESTONE_JAVA_ALPHAWORLD_H
