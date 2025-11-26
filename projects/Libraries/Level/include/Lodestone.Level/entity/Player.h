//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#ifndef LODESTONE_PLAYER_H
#define LODESTONE_PLAYER_H
#include <string>

#include "Lodestone.Level/Level.h"
#include "Lodestone.Level/entity/Entity.h"
#include "Lodestone.Level/properties/ReflectiveProperties.h"

namespace lodestone::level::entity {
    class LODESTONE_API Player : public Entity,
                                 public properties::ReflectiveProperties {
      public:
        /** Can return a UUID, player name, or other depending on the version */
        virtual const std::string &getId() const = 0;

        std::string toString() const override {
            return (common::string::OperatorStringBuilder(typeid(*this)))
                .addField("id", getId())
                ->addField("health", mHealth)
                ->addField("pos",
                           mPosition.value_or(types::Vec3d{0, 0, 0}).toString())
                ->toString();
        };

        world::World *getWorld() const;
        bool isInWorld() const;

        level::Level *getLevel() const;
        bool isInLevel() const;

        virtual void respawn(bool inDefaultLevel = true);
        bool isOnGround() const;

        std::shared_ptr<level::properties::AbstractProperty>
        getProperty(const std::string &name) override;

      protected:
        /** Sets the player's level
         *
         * NOTE: if the level is contained within a different world, the player
         * will be moved to that world.
         */
        void setLevel(level::Level *level, bool resetCoords = true);

        /** Sets the player's world
         *
         * NOTE: if the current level does not exist within the given world, the
         * player will be moved to the default level.
         */
        void setWorld(world::World *world, bool resetCoords = true);

        const common::registry::Identifier *getType() const override;

      private:
        world::World *mWorld = nullptr;
        level::Level *mCurrentLevel = nullptr;
        // todo should we make player that has inventory

        friend class lodestone::level::world::World;
    };
} // namespace lodestone::level::entity

#endif // LODESTONE_PLAYER_H
