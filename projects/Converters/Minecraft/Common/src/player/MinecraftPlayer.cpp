//
// Created by DexrnZacAttack on 11/21/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Common/player/MinecraftPlayer.h"

#include "Lodestone.Minecraft.Common/Identifiers.h"
#include <Lodestone.Level/world/World.h>

#include "Lodestone.Common/util/Math.h"

namespace lodestone::minecraft::common::player {
    MinecraftPlayer::MinecraftPlayer(const std::string &name)
        : mName(name), mDeathTime(0), mHurtTime(0), mAttackTime(0),
          mFireTime(0), mBreathingTime(0),
          mDimension(level::world::World::Dimension::OVERWORLD),
          mFallDistance(0) {}

    const std::string &MinecraftPlayer::getId() const { return mName; }

    const level::types::Vec3i &MinecraftPlayer::getSpawnPos() const {
        return mSpawnPos;
    }

    void MinecraftPlayer::setSpawnPos(const level::types::Vec3i &spawnPos) {
        mSpawnPos = spawnPos;
    }

    short MinecraftPlayer::getDeathTime() const { return mDeathTime; }

    void MinecraftPlayer::setDeathTime(const short deathTime) {
        mDeathTime = deathTime;
    }

    short MinecraftPlayer::getHurtTime() const { return mHurtTime; }

    void MinecraftPlayer::setHurtTime(const short hurtTime) {
        mHurtTime = hurtTime;
    }

    short MinecraftPlayer::getAttackTime() const { return mAttackTime; }

    void MinecraftPlayer::setAttackTime(const short attackTime) {
        mAttackTime = attackTime;
    }

    short MinecraftPlayer::getFireTime() const { return mFireTime; }

    void MinecraftPlayer::setFireTime(const short fireTime) {
        mFireTime = fireTime;
    }

    short MinecraftPlayer::getBreathingTime() const { return mBreathingTime; }

    void MinecraftPlayer::setBreathingTime(const short breathingTime) {
        mBreathingTime = breathingTime;
    }

    const lodestone::common::registry::Identifier &
    MinecraftPlayer::getDimension() const {
        return mDimension;
    }

    std::string MinecraftPlayer::getWorldName() const {
        const level::world::World *wld = getWorld();
        if (!wld)
            return "";

        return wld->getName();
    }

    void MinecraftPlayer::setDimension(
        const lodestone::common::registry::Identifier &dimension) {
        this->mDimension = dimension;
    }

    float MinecraftPlayer::getFallDistance() const { return mFallDistance; }

    void MinecraftPlayer::setFallDistance(const float fallDistance) {
        this->mFallDistance = fallDistance;
    }

    const level::container::ItemContainer &
    MinecraftPlayer::getInventory() const {
        return mInventory;
    }

    const level::container::ItemContainer &MinecraftPlayer::getArmor() const {
        return mArmor;
    }

    const lodestone::common::registry::Identifier *
    MinecraftPlayer::getType() const {
        return &identifiers::MINECRAFT_COMMON;
    }

    const Abilities &MinecraftPlayer::getAbilities() const {
        return mAbilities;
    }

    void MinecraftPlayer::setAbilities(const Abilities &abilities) {
        mAbilities = abilities;
    }

    std::shared_ptr<level::properties::AbstractProperty>
    MinecraftPlayer::getProperty(const std::string &name) {
        switch (lodestone::common::util::Math::fnv1a64(name.data(),
                                                       name.length())) {
            ADD_FIELD_PROPERTY("name", mName);
            ADD_FIELD_PROPERTY("spawnPos", mSpawnPos);
            ADD_FIELD_PROPERTY("deathTime", mDeathTime);
            ADD_FIELD_PROPERTY("hurtTime", mHurtTime);
            ADD_FIELD_PROPERTY("attackTime", mAttackTime);
            ADD_FIELD_PROPERTY("fireTime", mFireTime);
            ADD_FIELD_PROPERTY("breathingTime", mBreathingTime);
            ADD_FIELD_PROPERTY("dimension", mDimension);
            ADD_FIELD_PROPERTY("fallDistance", mFallDistance);
            ADD_FIELD_PROPERTY("inventory", mInventory);
            ADD_FIELD_PROPERTY("armor", mArmor);
            ADD_FIELD_PROPERTY("abilities", mAbilities);
        default:
            return Player::getProperty(name);
        }
    }

} // namespace lodestone::minecraft::common::player
