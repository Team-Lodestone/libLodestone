//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONPLAYER_H
#define LODESTONE_MCREGIONPLAYER_H
#include <Lodestone.Level/container/ItemContainer.h>
#include <Lodestone.Level/entity/Player.h>

#include <Lodestone.Minecraft.Common/player/MinecraftPlayer.h>

namespace lodestone::minecraft::java::mcr::player {
    // TODO make minecraft project that has common player data
    class McRegionPlayer final : public common::player::MinecraftPlayer {
      public:
        explicit McRegionPlayer(const std::string &name);

        short getSleepTimer() const;

        void setSleepTimer(const short sleepTimer);

        bool isSleeping() const;

        void setSleeping(const bool isSleeping);

        static const lodestone::common::registry::Identifier &
        dimensionIdToIdentifier(int id);
        static int
        identifierToDimensionId(const lodestone::common::registry::Identifier &str);

        const lodestone::common::registry::Identifier *getType() const override;
      private:
        bool mIsSleeping;
        short mSleepTimer;
    };
} // namespace lodestone::minecraft::java::mcr::player

#endif // LODESTONE_MCREGIONPLAYER_H
