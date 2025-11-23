//
// Created by DexrnZacAttack on 11/21/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Common/player/MinecraftPlayer.h"

#include <Lodestone.Level/world/World.h>
#include "Lodestone.Minecraft.Common/Identifiers.h"

namespace lodestone::minecraft::common::player {
    MinecraftPlayer::MinecraftPlayer(const std::string &name)
        : mName(name), mDeathTime(0),
          mHurtTime(0), mAttackTime(0), mFireTime(0), mBreathingTime(0),
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

    const lodestone::common::registry::Identifier &MinecraftPlayer::getDimension() const {
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

    bool MinecraftPlayer::isOnGround() const {
        level::Level *lvl = this->getLevel();
        if (lvl == nullptr || !this->mPosition.has_value())
            return false;

        double t;
        // if there's no fraction then we know the player is standing ON the
        // block This however will NOT work with blocks that have alt AABBs, as
        // the fraction most definitely won't be 0. but it should suffice for
        // most cases.
        //
        // Additionally, we don't check for collision, but this *probably* won't
        // be an issue as the game will reset it afterward anyway.
        if (std::modf(this->mPosition->y, &t) == 0 &&
            lvl->getBlock(this->mPosition->x, this->mPosition->y - 1,
                          this->mPosition->z)
                    ->getBlock() != level::block::BlockRegistry::sDefaultBlock)
            return true;

        return false;
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

    const lodestone::common::registry::Identifier *MinecraftPlayer::getType() const {
        return &identifiers::MINECRAFT_COMMON;
    }
}
