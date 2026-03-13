//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#ifndef LODESTONE_JAVA_ALPHAPLAYER_H
#define LODESTONE_JAVA_ALPHAPLAYER_H
#include <Lodestone.Level/container/ItemContainer.h>
#include <Lodestone.Level/entity/Player.h>

#include <Lodestone.Minecraft.Common/player/MinecraftPlayer.h>

namespace lodestone::minecraft::java::alpha::player {
    class AlphaPlayer final : public common::player::MinecraftPlayer {
      public:
        explicit AlphaPlayer(const std::string &name);
    };
} // namespace lodestone::minecraft::java::alpha::player

#endif // LODESTONE_JAVA_ALPHAPLAYER_H
