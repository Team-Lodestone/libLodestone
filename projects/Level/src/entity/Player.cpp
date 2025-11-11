//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#include "Lodestone.Level/entity/Player.h"

#include "Lodestone.Level/entity/Entities.h"
#include "Lodestone.Level/world/World.h"

namespace lodestone::level::entity {
    world::World * Player::getWorld() const {
        return mWorld;
    }

    bool Player::isInWorld() const {
        return getWorld();
    }

    void Player::setLevel(level::Level *level, const bool resetCoords) {
        if (!level) throw std::runtime_error("Attempted to move player into null level");

        if (this->mCurrentLevel != level) {
            this->mCurrentLevel = level;

            this->mWorld = level->getWorld();

            if (resetCoords) this->mPosition.reset();
        }
    }

    void Player::setWorld(world::World *world, const bool resetCoords) {
        if (!world) throw std::runtime_error("Attempted to move player into null world");

        this->mWorld = world;

        if (!(this->mCurrentLevel && this->mCurrentLevel->getWorld() == world)) {
            this->mCurrentLevel = world->getDefaultLevel();
            if (resetCoords) this->mPosition.reset();
        }
    }

    const common::registry::NamespacedString * Player::getType() {
        return &PLAYER;
    }

    Level * Player::getLevel() const {
        return mCurrentLevel;
    }

    bool Player::isInLevel() const {
        return getLevel();
    }
}
