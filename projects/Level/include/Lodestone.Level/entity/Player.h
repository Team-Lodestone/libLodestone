//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#ifndef LODESTONE_PLAYER_H
#define LODESTONE_PLAYER_H
#include <string>

#include "Lodestone.Level/entity/Entity.h"
#include "Lodestone.Level/Level.h"

namespace lodestone::level::entity {
    class LODESTONE_API Player : public Entity {
    public:
        /** Can return a UUID, player name, or other depending on the version */
        virtual const std::string &getId() = 0;

        world::World *getWorld() const;
        bool isInWorld() const;

        level::Level *getLevel() const;
        bool isInLevel() const;
    protected:
        /** Sets the player's level
         *
         * NOTE: if the level is contained within a different world, the player will be moved to that world.
         */
        void setLevel(level::Level *level, bool resetCoords = true);

        /** Sets the player's world
         *
         * NOTE: if the current level does not exist within the given world, the player will be moved to the default level.
         */
        void setWorld(world::World *world, bool resetCoords = true);

        const common::registry::NamespacedString *getType() override;
    private:
        world::World *mWorld = nullptr;
        level::Level *mCurrentLevel = nullptr;

        friend class lodestone::level::world::World;
    };
}

#endif //LODESTONE_PLAYER_H
