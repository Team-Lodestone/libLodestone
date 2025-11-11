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
        this->mHealth = health;
    }

    int Entity::getMaxHealth() const {
        return MAX_HEALTH; // todo modifiers and such
    }

    const std::optional<types::Vec3f> & Entity::getPosition() const {
        return mPosition;
    }

    void Entity::setPosition(const types::Vec3f &pos) {
        // TODO we need to move entity to different chunk too
        this->mPosition = pos;
    }

    void Entity::setPosition(float x, float y, float z) {
        setPosition({x, y, z});
    }

    const common::registry::NamespacedString *Entity::getType() {
        return &ENTITY;
    }
}
