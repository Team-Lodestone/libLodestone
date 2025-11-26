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

    std::shared_ptr<level::properties::AbstractProperty>
    MinecraftPlayer::getProperty(const std::string &name) {
        switch (lodestone::common::util::Math::fnv1a64(name.data(),
                                                       name.length())) {
            ADD_PROPERTY("name", mName, std::string &);
            ADD_PROPERTY("spawnPos", mSpawnPos, level::types::Vec3i &);
            ADD_PROPERTY("deathTime", mDeathTime, short &);
            ADD_PROPERTY("hurtTime", mHurtTime, short &);
            ADD_PROPERTY("attackTime", mAttackTime, short &);
            ADD_PROPERTY("fireTime", mFireTime, short &);
            ADD_PROPERTY("breathingTime", mBreathingTime, short &);
            ADD_PROPERTY("dimension", mDimension,
                         lodestone::common::registry::Identifier &);
            ADD_PROPERTY("fallDistance", mFallDistance, float &);
            ADD_PROPERTY("inventory", mInventory,
                         level::container::ItemContainer &);
            ADD_PROPERTY("armor", mArmor, level::container::ItemContainer &);
        default:
            return Player::getProperty(name);
        }
    }

} // namespace lodestone::minecraft::common::player
