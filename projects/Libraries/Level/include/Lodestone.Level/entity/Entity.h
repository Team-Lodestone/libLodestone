//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#ifndef LODESTONE_ENTITY_H
#define LODESTONE_ENTITY_H
#include <optional>

#include <Lodestone.Common/registry/Identifier.h>

#include "Lodestone.Level/entity/WorldSpaceObject.h"
#include "Lodestone.Level/types/Vec2.h"
#include "Lodestone.Level/types/Vec3.h"

namespace lodestone::level::world {
    class World;
}

namespace lodestone::level::chunk {
    class Chunk;
}

namespace lodestone::level::entity {
    class Entity : public WorldSpaceObject, public common::string::StringSerializable {
      public:
        static constexpr int MAX_HEALTH = 20;

        Entity() = default;
        ~Entity() override = default;

        int getHealth() const;
        void setHealth(int health);

        bool isDead() const;

        virtual int getMaxHealth() const;

        const types::Vec3d &getMotion() const;
        /** Sets the entity's motion */
        virtual void setMotion(const types::Vec3d &motion);
        void setMotion(double x, double y, double z);

        void resetCoords();

        virtual const common::registry::Identifier *getType() const;

        std::string toString() const override {
            return std::format(
                "Entity[type={}, health={}, pos={}]", getType()->getString(),
                m_health, position.toString());
        };

      protected:
        /** The motion that the entity has */
        types::Vec3d m_motion{0, 0, 0};

        int m_health = MAX_HEALTH;

        friend class lodestone::level::world::World;
        friend class lodestone::level::chunk::Chunk;
    };
} // namespace lodestone::level::entity

#endif // LODESTONE_ENTITY_H
