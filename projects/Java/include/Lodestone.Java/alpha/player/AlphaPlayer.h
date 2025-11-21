//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#ifndef LODESTONE_JAVA_ALPHAPLAYER_H
#define LODESTONE_JAVA_ALPHAPLAYER_H
#include <Lodestone.Level/container/ItemContainer.h>
#include <Lodestone.Level/entity/Player.h>

namespace lodestone::java::alpha::player {
    // TODO make minecraft project that has common player data
    class AlphaPlayer final : public level::entity::Player {
      public:
        explicit AlphaPlayer(const std::string &name);

        const std::string &getId() const override;

        const level::types::Vec3i &getSpawnPos() const;

        void setSpawnPos(const level::types::Vec3i &spawnPos);

        short getDeathTime() const;

        void setDeathTime(const short deathTime);

        short getHurtTime() const;

        void setHurtTime(const short hurtTime);

        short getAttackTime() const;

        void setAttackTime(const short attackTime);

        short getFireTime() const;

        void setFireTime(const short fireTime);

        short getBreathingTime() const;

        void setBreathingTime(const short breathingTime);

        const common::registry::Identifier &getDimension() const;

        std::string getWorldName() const;

        void setDimension(const common::registry::Identifier &dimension);

        bool isOnGround() const;

        float getFallDistance() const;

        void setFallDistance(const float fallDistance);

        const level::container::ItemContainer &getInventory() const;

        const level::container::ItemContainer &getArmor() const;

        const common::registry::Identifier *getType() const override;

        bool isSleeping() const;

        void setSleeping(const bool isSleeping);

        static const common::registry::Identifier &
        dimensionIdToIdentifier(int id);
        static int
        identifierToDimensionId(const common::registry::Identifier &str);

      private:
        std::string mName;
        level::types::Vec3i mSpawnPos{0, 0, 0};

        // todo ?
        short mDeathTime;
        short mHurtTime;
        short mAttackTime;
        short mFireTime;

        short mBreathingTime;

        common::registry::Identifier mDimension;

        /** How far the player has fallen */
        float mFallDistance;

        level::container::ItemContainer mInventory =
            level::container::ItemContainer(35);
        level::container::ItemContainer mArmor =
            level::container::ItemContainer(4);
    };
} // namespace lodestone::java::alpha::player

#endif // LODESTONE_JAVA_ALPHAPLAYER_H
