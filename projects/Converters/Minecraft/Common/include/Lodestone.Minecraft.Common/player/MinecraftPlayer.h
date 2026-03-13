//
// Created by DexrnZacAttack on 11/21/25 using zPc-i2.
//
#ifndef LODESTONE_MINECRAFTPLAYER_H
#define LODESTONE_MINECRAFTPLAYER_H
#include <Lodestone.Level/container/ItemContainer.h>
#include <Lodestone.Level/entity/Player.h>

#include "Lodestone.Minecraft.Common/player/Abilities.h"

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

        const Abilities &getAbilities() const;

        void setAbilities(const Abilities &abilities);
         std::unique_ptr<level::properties::AbstractProperty>
        getProperty(const std::string &name) override;

      private:
        /** The player's name
         *
         * @prop name
         */
        std::string m_name;

        /** The player's respawn position
         *
         * @prop spawnPos
         */
        level::types::Vec3i m_spawnPos{0, 0, 0};

        /**
         * @prop deathTime
         */
        short m_deathTime;
        /**
         * @prop hurtTime
         */
        short m_hurtTime;
        /**
         * @prop attackTime
         */
        short m_attackTime;
        /**
         * @prop fireTime
         */
        short m_fireTime;
        /**
         * @prop breathingTime
         */
        short m_breathingTime;

        /** The ID of the dimension the player is currently in
         * @prop dimension
         */
        lodestone::common::registry::Identifier m_dimension;

        /** How far the player has fallen
         *
         * @prop fallDistance
         */
        float m_fallDistance;

        /** The player's abilities */
        Abilities m_abilities;

        /** The player's inventory
         *
         * @prop inventory
         */
        level::container::ItemContainer m_inventory =
            level::container::ItemContainer(35);
        /** The player's armor slots
         *
         * @prop armor
         */
        level::container::ItemContainer m_armor =
            level::container::ItemContainer(4);
    };
} // namespace lodestone::minecraft::common::player

#endif // LODESTONE_MINECRAFTPLAYER_H
