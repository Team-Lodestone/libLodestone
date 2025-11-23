//
// Created by Zero on 11/20/25.
//

#include "Lodestone.Minecraft.Java/alpha/world/AlphaWorld.h"

namespace lodestone::minecraft::java::alpha::world {
    AlphaWorld::AlphaWorld(const std::string &name) : World(name) {}

    int64_t AlphaWorld::getSeed() const { return this->mSeed; }

    void AlphaWorld::setSeed(const int64_t seed) { this->mSeed = seed; }

    int64_t AlphaWorld::getLastPlayed() const { return this->mLastPlayed; }

    void AlphaWorld::setLastPlayed(const int64_t lastPlayed) {
        this->mLastPlayed = lastPlayed;
    }

    int64_t AlphaWorld::getTime() const { return this->mTime; }

    void AlphaWorld::setTime(const int64_t time) { this->mTime = time; }
} // namespace lodestone::minecraft::java::alpha::world