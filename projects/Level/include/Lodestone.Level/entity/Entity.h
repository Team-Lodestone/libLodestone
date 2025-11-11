//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#ifndef LODESTONE_ENTITY_H
#define LODESTONE_ENTITY_H
#include <optional>

#include <Lodestone.Common/registry/NamespacedString.h>
#include "Lodestone.Level/types/Vec3.h"

namespace lodestone::level::world {
    class World;
}

namespace lodestone::level::chunk {
    class Chunk;
}

namespace lodestone::level::entity {
    class Entity {
    public:
        static constexpr int MAX_HEALTH = 20;

        virtual ~Entity() = default;

        int getHealth() const;
        void setHealth(int health);

        virtual int getMaxHealth() const;

        const std::optional<types::Vec3f> &getPosition() const;
        /** Sets the entity's position
         *
         * This works without the player being in a world
         */
        virtual void setPosition(const types::Vec3f &pos);
        void setPosition(float x, float y, float z);

        virtual const common::registry::NamespacedString *getType();

    protected:
        std::optional<types::Vec3f> mPosition;
        int mHealth = MAX_HEALTH;

        friend class lodestone::level::world::World;
        friend class lodestone::level::chunk::Chunk;
    };
}

#endif //LODESTONE_ENTITY_H
