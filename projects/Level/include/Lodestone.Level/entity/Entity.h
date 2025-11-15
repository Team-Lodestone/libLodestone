//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#ifndef LODESTONE_ENTITY_H
#define LODESTONE_ENTITY_H
#include <optional>

#include <Lodestone.Common/registry/Identifier.h>

#include "Lodestone.Level/types/Vec2.h"
#include "Lodestone.Level/types/Vec3.h"

namespace lodestone::level::world {
    class World;
}

namespace lodestone::level::chunk {
    class Chunk;
}

namespace lodestone::level::entity {
    class Entity : public common::string::StringSerializable {
    public:
        static constexpr int MAX_HEALTH = 20;

        Entity() = default;
        ~Entity() override = default;

        int getHealth() const;
        void setHealth(int health);

        bool isDead() const;

        virtual int getMaxHealth() const;

        const std::optional<types::Vec3d> &getPosition() const;
        /** Sets the entity's position
         *
         * This works without the player being in a world
         */
        virtual void setPosition(const types::Vec3d &pos);
        void setPosition(double x, double y, double z);

        const types::Vec2f &getRotation() const;
        /** Sets the entity's rotation */
        virtual void setRotation(const types::Vec2f &rot);
        void setRotation(float yaw, float pitch);

        const types::Vec3d &getMotion() const;
        /** Sets the entity's motion */
        virtual void setMotion(const types::Vec3d &motion);
        void setMotion(double x, double y, double z);

        virtual const common::registry::Identifier *getType() const;

        constexpr std::string toString() const override {
            return std::format("Entity[type={}, health={}, pos={}]", getType()->getString(), mHealth, mPosition.value_or(types::Vec3d{0,0,0}).toString());
        };

    protected:
        /** Where the entity is located in world space */
        std::optional<types::Vec3d> mPosition;
        /** Which way the entity is facing */
        types::Vec2f mRotation{0,0};
        /** The motion that the entity has */
        types::Vec3d mMotion{0,0,0};

        int mHealth = MAX_HEALTH;

        friend class lodestone::level::world::World;
        friend class lodestone::level::chunk::Chunk;
    };
}

#endif //LODESTONE_ENTITY_H
