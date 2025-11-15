//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#include "Lodestone.Level/entity/Entity.h"

#include "Lodestone.Level/entity/Entities.h"

namespace lodestone::level::entity {
    int Entity::getHealth() const {
        return mHealth;
    }

    void Entity::setHealth(const int health) {
        this->mHealth = std::min(health, getMaxHealth());
    }

    bool Entity::isDead() const {
        return mHealth <= 0;
    }

    int Entity::getMaxHealth() const {
        return MAX_HEALTH; // todo modifiers and such
    }

    const std::optional<types::Vec3d> & Entity::getPosition() const {
        return mPosition;
    }

    void Entity::setPosition(const types::Vec3d &pos) {
        // TODO we need to move entity to different chunk too
        this->mPosition = pos;
    }

    void Entity::setPosition(double x, double y, double z) {
        setPosition({x, y, z});
    }

    const types::Vec2f & Entity::getRotation() const {
        return mRotation;
    }

    void Entity::setRotation(const types::Vec2f &rot) {
        this->mRotation = rot;
    }

    void Entity::setRotation(float yaw, float pitch) {
        setRotation({yaw, pitch});
    }

    const types::Vec3d & Entity::getMotion() const {
        return mMotion;
    }

    void Entity::setMotion(const types::Vec3d &motion) {
        this->mMotion = motion;
    }

    void Entity::setMotion(double x, double y, double z) {
        setMotion({x,y,z});
    }

    const common::registry::Identifier *Entity::getType() const {
        return &ENTITY;
    }
}
