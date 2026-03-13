//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#include "Lodestone.Level/entity/Entity.h"

#include "Lodestone.Level/entity/Entities.h"

namespace lodestone::level::entity {
    int Entity::getHealth() const { return m_health; }

    void Entity::setHealth(const int health) {
        this->m_health = std::min(health, getMaxHealth());
    }

    bool Entity::isDead() const { return m_health <= 0; }

    int Entity::getMaxHealth() const {
        return MAX_HEALTH; // todo modifiers and such
    }

    const types::Vec3d &Entity::getMotion() const { return m_motion; }

    void Entity::setMotion(const types::Vec3d &motion) {
        this->m_motion = motion;
    }

    void Entity::setMotion(double x, double y, double z) {
        setMotion({x, y, z});
    }

    void Entity::resetCoords() {
        this->position = types::VEC3_ZERO<double>;
        this->rotation = types::VEC2_ZERO<float>;
        this->setMotion(types::VEC3_ZERO<double>);
    }

    const common::registry::Identifier *Entity::getType() const {
        return &ENTITY;
    }
} // namespace lodestone::level::entity
