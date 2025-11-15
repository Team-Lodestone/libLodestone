//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#include "Lodestone.Java/mcr/player/McRegionPlayer.h"

#include "Lodestone.Java/Identifiers.h"
#include <Lodestone.Level/world/World.h>

namespace lodestone::java::mcr::player {
    McRegionPlayer::McRegionPlayer(const std::string &name) : mName(name), mSleepTimer(0), mIsSleeping(false),
                                                              mDeathTime(0),
                                                              mHurtTime(0), mAttackTime(0),
                                                              mFireTime(0),
                                                              mBreathingTime(0),
                                                              mDimension(level::world::World::Dimension::OVERWORLD),
                                                              mFallDistance(0) {
    }

    const std::string & McRegionPlayer::getId() const {
        return mName;
    }

    const level::types::Vec3i & McRegionPlayer::getSpawnPos() const {
        return mSpawnPos;
    }

    void McRegionPlayer::setSpawnPos(const level::types::Vec3i &spawnPos) {
        mSpawnPos = spawnPos;
    }

    short McRegionPlayer::getSleepTimer() const {
        return mSleepTimer;
    }

    void McRegionPlayer::setSleepTimer(const short sleepTimer) {
        mSleepTimer = sleepTimer;
    }

    short McRegionPlayer::getDeathTime() const {
        return mDeathTime;
    }

    void McRegionPlayer::setDeathTime(const short deathTime) {
        mDeathTime = deathTime;
    }

    short McRegionPlayer::getHurtTime() const {
        return mHurtTime;
    }

    void McRegionPlayer::setHurtTime(const short hurtTime) {
        mHurtTime = hurtTime;
    }

    short McRegionPlayer::getAttackTime() const {
        return mAttackTime;
    }

    void McRegionPlayer::setAttackTime(const short attackTime) {
        mAttackTime = attackTime;
    }

    short McRegionPlayer::getFireTime() const {
        return mFireTime;
    }

    void McRegionPlayer::setFireTime(const short fireTime) {
        mFireTime = fireTime;
    }

    short McRegionPlayer::getBreathingTime() const {
        return mBreathingTime;
    }

    void McRegionPlayer::setBreathingTime(const short breathingTime) {
        mBreathingTime = breathingTime;
    }

    const common::registry::Identifier &McRegionPlayer::getDimension() const {
        return mDimension;
    }

    std::string McRegionPlayer::getWorldName() const {
        const level::world::World *wld = getWorld();
        if (!wld) return "";

        return wld->getName();
    }

    // why can this be const
    void McRegionPlayer::setDimension(const common::registry::Identifier &dimension) {
        this->mDimension = dimension;
    }

    bool McRegionPlayer::isOnGround() const {
        level::Level *lvl = this->getLevel();
        if (lvl == nullptr || !this->mPosition.has_value()) return false;

        double t;
        // if there's no fraction then we know the player is standing ON the block
        // This however will NOT work with blocks that have alt AABBs, as the fraction most definitely won't be 0.
        // but it should suffice for most cases.
        //
        // Additionally, we don't check for collision, but this *probably* won't be an issue as the game will reset it afterward anyway.
        if (std::modf(this->mPosition->y, &t) == 0 && lvl->getBlock(this->mPosition->x, this->mPosition->y - 1, this->mPosition->z)->getBlock() != level::block::BlockRegistry::sDefaultBlock)
            return true;

        return false;
    }

    float McRegionPlayer::getFallDistance() const {
        return mFallDistance;
    }

    void McRegionPlayer::setFallDistance(const float fallDistance) {
        this->mFallDistance = fallDistance;
    }

    const level::container::ItemContainer & McRegionPlayer::getInventory() const {
        return mInventory;
    }

    const level::container::ItemContainer & McRegionPlayer::getArmor() const {
        return mArmor;
    }

    const common::registry::Identifier * McRegionPlayer::getType() const {
        return &identifiers::MCREGION_PLAYER;
    }

    bool McRegionPlayer::isSleeping() const {
        return mIsSleeping;
    }

    void McRegionPlayer::setSleeping(const bool isSleeping) {
        mIsSleeping = isSleeping;
    }

    const common::registry::Identifier &McRegionPlayer::dimensionIdToIdentifier(const int id) {
        switch (id) {
            case -1: return level::world::World::Dimension::NETHER;
            default:
                return level::world::World::Dimension::OVERWORLD;
            case 1: return level::world::World::Dimension::END;
        }
    }

    // FIXME: we could make another id converter but I don't want to right now
    int McRegionPlayer::identifierToDimensionId(const common::registry::Identifier &str) {
        return str == level::world::World::Dimension::NETHER // if nether return -1
                ? -1
                : str == level::world::World::Dimension::END // if end return 1
                ? 1
                : 0; // otherwise overworld (0)
    }
}
