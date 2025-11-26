//
// Created by DexrnZacAttack on 11/21/25 using zPc-i2.
//
#ifndef LODESTONE_MINECRAFTPLAYER_H
#define LODESTONE_MINECRAFTPLAYER_H
#include <Lodestone.Level/container/ItemContainer.h>
#include <Lodestone.Level/entity/Player.h>

namespace lodestone::minecraft::common::player {
    class MinecraftPlayer : public level::entity::Player {
      public:
        explicit MinecraftPlayer(const std::string &name);

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

        const lodestone::common::registry::Identifier &getDimension() const;

        std::string getWorldName() const;

        void
        setDimension(const lodestone::common::registry::Identifier &dimension);

        float getFallDistance() const;

        void setFallDistance(const float fallDistance);

        const level::container::ItemContainer &getInventory() const;

        const level::container::ItemContainer &getArmor() const;

        const lodestone::common::registry::Identifier *getType() const override;

        std::shared_ptr<level::properties::AbstractProperty> getProperty(const std::string &name) override;

      private:
        /** The player's name
         *
         * @prop name
         */
        std::string mName;

        /** The player's respawn position
         *
         * @prop spawnPos
         */
        level::types::Vec3i mSpawnPos{0, 0, 0};

        /**
         * @prop deathTime
         */
        short mDeathTime;
        /**
         * @prop hurtTime
         */
        short mHurtTime;
        /**
         * @prop attackTime
         */
        short mAttackTime;
        /**
         * @prop fireTime
         */
        short mFireTime;
        /**
         * @prop breathingTime
         */
        short mBreathingTime;

        /** The ID of the dimension the player is currently in
         * @prop dimension
         */
        lodestone::common::registry::Identifier mDimension;

        /** How far the player has fallen
         *
         * @prop fallDistance
         */
        float mFallDistance;

        /** The player's inventory
         *
         * @prop inventory
         */
        level::container::ItemContainer mInventory =
            level::container::ItemContainer(35);
        /** The player's armor slots
         *
         * @prop armor
         */
        level::container::ItemContainer mArmor =
            level::container::ItemContainer(4);
    };
} // namespace lodestone::minecraft::common::player

#endif // LODESTONE_MINECRAFTPLAYER_H
