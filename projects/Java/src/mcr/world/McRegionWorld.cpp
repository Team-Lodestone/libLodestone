//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#include "Lodestone.Java/mcr/world/McRegionWorld.h"

#include "Lodestone.Java/Identifiers.h"
#include <Lodestone.Conversion/world/WorldIORegistry.h>

namespace lodestone::java::mcr::world {
    McRegionWorld::McRegionWorld(const std::string &name) : World(name), mSeed(0),
                                                            mIsRaining(false),
                                                            mRainTime(0),
                                                            mIsThundering(false),
                                                            mThunderTime(0),
                                                            mLastPlayed(0), mSize(0) {
    }

    const lodestone::conversion::world::WorldIO * McRegionWorld::getIO() {
        return lodestone::conversion::world::WorldIORegistry::sInstance.getWorldIO(identifiers::MCREGION);
    }

    int64_t McRegionWorld::getSeed() const {
        return mSeed;
    }

    void McRegionWorld::setSeed(const int64_t seed) {
        mSeed = seed;
    }

    bool McRegionWorld::isRaining() const {
        return mIsRaining;
    }

    void McRegionWorld::setIsRaining(const bool isRaining) {
        mIsRaining = isRaining;
    }

    int McRegionWorld::getRainTime() const {
        return mRainTime;
    }

    void McRegionWorld::setRainTime(const int rainTime) {
        mRainTime = rainTime;
    }

    bool McRegionWorld::isThundering() const {
        return mIsThundering;
    }

    void McRegionWorld::setIsThundering(const bool isThundering) {
        mIsThundering = isThundering;
    }

    int McRegionWorld::getThunderTime() const {
        return mThunderTime;
    }

    void McRegionWorld::setThunderTime(const int thunderTime) {
        mThunderTime = thunderTime;
    }

    int64_t McRegionWorld::getLastPlayed() const {
        return mLastPlayed;
    }

    void McRegionWorld::setLastPlayed(const int64_t lastPlayed) {
        mLastPlayed = lastPlayed;
    }

    int64_t McRegionWorld::getSize() const {
        return mSize;
    }

    void McRegionWorld::setSize(const int64_t size) {
        mSize = size;
    }

    int64_t McRegionWorld::getTime() const {
        return mTime;
    }

    void McRegionWorld::setTime(const int64_t time) {
        mTime = time;
    }

    int32_t McRegionWorld::getVersion() const {
        return mVersion;
    }

    void McRegionWorld::setVersion(const int32_t version) {
        mVersion = version;
    }
}
