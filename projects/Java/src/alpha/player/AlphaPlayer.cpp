//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#include "Lodestone.Java/alpha/player/AlphaPlayer.h"

#include "Lodestone.Java/Identifiers.h"
#include <Lodestone.Level/world/World.h>

namespace lodestone::java::alpha::player {
    AlphaPlayer::AlphaPlayer(const std::string &name)
        : mName(name), mDeathTime(0), mHurtTime(0), mAttackTime(0),
          mFireTime(0), mBreathingTime(0),
          mDimension(level::world::World::Dimension::OVERWORLD),
          mFallDistance(0) {}

    const std::string &AlphaPlayer::getId() const { return mName; }

    const level::types::Vec3i &AlphaPlayer::getSpawnPos() const {
        return mSpawnPos;
    }

    void AlphaPlayer::setSpawnPos(const level::types::Vec3i &spawnPos) {
        mSpawnPos = spawnPos;
    }

    short AlphaPlayer::getDeathTime() const { return mDeathTime; }

    void AlphaPlayer::setDeathTime(const short deathTime) {
        mDeathTime = deathTime;
    }

    short AlphaPlayer::getHurtTime() const { return mHurtTime; }

    void AlphaPlayer::setHurtTime(const short hurtTime) {
        mHurtTime = hurtTime;
    }

    short AlphaPlayer::getAttackTime() const { return mAttackTime; }

    void AlphaPlayer::setAttackTime(const short attackTime) {
        mAttackTime = attackTime;
    }

    short AlphaPlayer::getFireTime() const { return mFireTime; }

    void AlphaPlayer::setFireTime(const short fireTime) {
        mFireTime = fireTime;
    }

    short AlphaPlayer::getBreathingTime() const { return mBreathingTime; }

    void AlphaPlayer::setBreathingTime(const short breathingTime) {
        mBreathingTime = breathingTime;
    }

    const common::registry::Identifier &AlphaPlayer::getDimension() const {
        return mDimension;
    }

    std::string AlphaPlayer::getWorldName() const {
        const level::world::World *wld = getWorld();
        if (!wld)
            return "";

        return wld->getName();
    }

    // why can this be const
    void
    AlphaPlayer::setDimension(const common::registry::Identifier &dimension) {
        this->mDimension = dimension;
    }

    bool AlphaPlayer::isOnGround() const {
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

    float AlphaPlayer::getFallDistance() const { return mFallDistance; }

    void AlphaPlayer::setFallDistance(const float fallDistance) {
        this->mFallDistance = fallDistance;
    }

    const level::container::ItemContainer &AlphaPlayer::getInventory() const {
        return mInventory;
    }

    const level::container::ItemContainer &AlphaPlayer::getArmor() const {
        return mArmor;
    }

    const common::registry::Identifier *AlphaPlayer::getType() const {
        return &identifiers::MCREGION_PLAYER;
    }

    const common::registry::Identifier &
    AlphaPlayer::dimensionIdToIdentifier(const int id) {
        switch (id) {
        case -1:
            return level::world::World::Dimension::NETHER;
        case 0:
            return level::world::World::Dimension::OVERWORLD;
        case 1:
            return level::world::World::Dimension::END;
        default:
            return level::world::World::Dimension::UNKNOWN;
        }
    }

    // FIXME: we could make another id converter but I don't want to right now
    int AlphaPlayer::identifierToDimensionId(
        const common::registry::Identifier &str) {
        return str == level::world::World::Dimension::NETHER // if nether return
                                                             // -1
                   ? -1
                   : str == level::world::World::Dimension::END // if end return
                                                                // 1
                         ? 1
                         : str == level::world::World::Dimension::
                                       OVERWORLD // otherwise overworld (0)
                               ? 0
                               : 0x7FFFFFFF;
    }
} // namespace lodestone::java::alpha::player
