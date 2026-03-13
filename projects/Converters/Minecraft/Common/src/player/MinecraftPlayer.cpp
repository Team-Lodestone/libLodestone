//
// Created by DexrnZacAttack on 11/21/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Common/player/MinecraftPlayer.h"

#include "Lodestone.Minecraft.Common/Identifiers.h"
#include <Lodestone.Level/world/World.h>

#include "Lodestone.Common/util/Math.h"

namespace lodestone::minecraft::common::player {
    MinecraftPlayer::MinecraftPlayer(const std::string &name)
        : m_name(name), m_deathTime(0), m_hurtTime(0), m_attackTime(0),
          m_fireTime(0), m_breathingTime(0),
          m_dimension(level::world::World::Dimension::OVERWORLD),
          m_fallDistance(0) {}

    const std::string &MinecraftPlayer::getId() const { return m_name; }

    const level::types::Vec3i &MinecraftPlayer::getSpawnPos() const {
        return m_spawnPos;
    }

    void MinecraftPlayer::setSpawnPos(const level::types::Vec3i &spawnPos) {
        m_spawnPos = spawnPos;
    }

    short MinecraftPlayer::getDeathTime() const { return m_deathTime; }

    void MinecraftPlayer::setDeathTime(const short deathTime) {
        m_deathTime = deathTime;
    }

    short MinecraftPlayer::getHurtTime() const { return m_hurtTime; }

    void MinecraftPlayer::setHurtTime(const short hurtTime) {
        m_hurtTime = hurtTime;
    }

    short MinecraftPlayer::getAttackTime() const { return m_attackTime; }

    void MinecraftPlayer::setAttackTime(const short attackTime) {
        m_attackTime = attackTime;
    }

    short MinecraftPlayer::getFireTime() const { return m_fireTime; }

    void MinecraftPlayer::setFireTime(const short fireTime) {
        m_fireTime = fireTime;
    }

    short MinecraftPlayer::getBreathingTime() const { return m_breathingTime; }

    void MinecraftPlayer::setBreathingTime(const short breathingTime) {
        m_breathingTime = breathingTime;
    }

    const lodestone::common::registry::Identifier &
    MinecraftPlayer::getDimension() const {
        return m_dimension;
    }

    std::string MinecraftPlayer::getWorldName() const {
        const level::world::World *wld = getWorld();
        if (!wld)
            return "";

        return wld->getName();
    }

    void MinecraftPlayer::setDimension(
        const lodestone::common::registry::Identifier &dimension) {
        this->m_dimension = dimension;
    }

    float MinecraftPlayer::getFallDistance() const { return m_fallDistance; }

    void MinecraftPlayer::setFallDistance(const float fallDistance) {
        this->m_fallDistance = fallDistance;
    }

    const level::container::ItemContainer &
    MinecraftPlayer::getInventory() const {
        return m_inventory;
    }

    const level::container::ItemContainer &MinecraftPlayer::getArmor() const {
        return m_armor;
    }

    const lodestone::common::registry::Identifier *
    MinecraftPlayer::getType() const {
        return &identifiers::MINECRAFT_PLAYER;
    }

    const Abilities &MinecraftPlayer::getAbilities() const {
        return m_abilities;
    }

    void MinecraftPlayer::setAbilities(const Abilities &abilities) {
        m_abilities = abilities;
    }

    std::unique_ptr<level::properties::AbstractProperty>
    MinecraftPlayer::getProperty(const std::string &name) {
        switch (lodestone::common::util::Math::fnv1a64(name.data(),
                                                       name.length())) {
            ADD_FIELD_PROPERTY("name", m_name);
            ADD_FIELD_PROPERTY("spawnPos", m_spawnPos);
            ADD_FIELD_PROPERTY("deathTime", m_deathTime);
            ADD_FIELD_PROPERTY("hurtTime", m_hurtTime);
            ADD_FIELD_PROPERTY("attackTime", m_attackTime);
            ADD_FIELD_PROPERTY("fireTime", m_fireTime);
            ADD_FIELD_PROPERTY("breathingTime", m_breathingTime);
            ADD_FIELD_PROPERTY("dimension", m_dimension);
            ADD_FIELD_PROPERTY("fallDistance", m_fallDistance);
            ADD_FIELD_PROPERTY("inventory", m_inventory);
            ADD_FIELD_PROPERTY("armor", m_armor);
            ADD_FIELD_PROPERTY("abilities", m_abilities);
        default:
            return Player::getProperty(name);
        }
    }

} // namespace lodestone::minecraft::common::player
