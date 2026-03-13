//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#include "Lodestone.Level/entity/Player.h"

#include "Lodestone.Level/entity/Entities.h"
#include "Lodestone.Level/world/World.h"

namespace lodestone::level::entity {
    world::World *Player::getWorld() const { return m_world; }

    bool Player::isInWorld() const { return getWorld(); }

    void Player::setLevel(level::Level *level, const bool resetCoords) {
        if (!level)
            throw std::runtime_error(
                "Attempted to move player into null level");

        if (this->m_currentLevel != level) {
            this->m_currentLevel = level;

            this->m_world = level->getWorld();

            if (resetCoords) {
                this->resetCoords();
            }
        }
    }

    void Player::setWorld(world::World *world, const bool resetCoords) {
        if (!world)
            throw std::runtime_error(
                "Attempted to move player into null world");

        this->m_world = world;

        if (!(this->m_currentLevel &&
              this->m_currentLevel->getWorld() == world)) {
            this->m_currentLevel = world->getDefaultLevel();
            if (resetCoords) {
                this->resetCoords();
            }
        }
    }

    const common::registry::Identifier *Player::getType() const {
        return &PLAYER;
    }

    Level *Player::getLevel() const { return m_currentLevel; }

    bool Player::isInLevel() const { return getLevel(); }

    void Player::respawn(const bool inDefaultLevel) {
        this->resetCoords();

        if (const world::World *wld = getWorld();
            inDefaultLevel && wld && wld->getDefaultLevel()) {
            this->position =
                static_cast<types::Vec3d>(wld->getDefaultLevel()->getSpawnPos());
        } else if (const Level *lvl = this->getLevel(); lvl != nullptr) {
            this->position = static_cast<types::Vec3d>(lvl->getSpawnPos());
        } else {
            this->position = {0, 64, 0};
        }

        this->m_health = getMaxHealth();
    }

    bool Player::isOnGround() const {
        const Level *lvl = this->getLevel();
        if (lvl == nullptr)
            return false;

        double t;
        // if there's no fraction then we know the player is standing ON the
        // block This however will NOT work with blocks that have alt AABBs, as
        // the fraction most definitely won't be 0. but it should suffice for
        // most cases.
        //
        // Additionally, we don't check for collision, but this *probably* won't
        // be an issue as the game will reset it afterward anyway.
        if (std::modf(this->position.y, &t) == 0 &&
            lvl->getBlock(this->position.x, this->position.y - 1,
                          this->position.z)
                    .getBlock()->hasCollision())
            return true;

        return false;
    }

    std::unique_ptr<level::properties::AbstractProperty>
    Player::getProperty(const std::string &name) {
        return nullptr;
    }
} // namespace lodestone::level::entity
