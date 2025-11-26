//
// Created by DexrnZacAttack on 11/22/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Common/world/MinecraftWorld.h"

#include "Lodestone.Common/util/Math.h"

namespace lodestone::minecraft::common::world {
    MinecraftWorld::MinecraftWorld(const std::string &name)
        : World(name), mSeed(lodestone::common::util::Math::random()),
          mLastPlayed(0), mTime(0) {}

    int64_t MinecraftWorld::getSeed() const { return this->mSeed; }

    void MinecraftWorld::setSeed(const int64_t seed) { this->mSeed = seed; }

    int64_t MinecraftWorld::getLastPlayed() const { return this->mLastPlayed; }

    void MinecraftWorld::setLastPlayed(const int64_t lastPlayed) {
        this->mLastPlayed = lastPlayed;
    }

    int64_t MinecraftWorld::getTime() const { return this->mTime; }

    void MinecraftWorld::setTime(const int64_t time) { this->mTime = time; }

    std::shared_ptr<level::properties::AbstractProperty> MinecraftWorld::getProperty(const std::string &name) {
        switch (lodestone::common::util::Math::fnv1a64(name.data(), name.length())) {
            ADD_PROPERTY("seed", mSeed, int64_t &);
            ADD_PROPERTY("lastPlayed", mLastPlayed, int64_t &);
            ADD_PROPERTY("time", mTime, int64_t &);
            default: return World::getProperty(name);
        }
    }
} // namespace lodestone::minecraft::common::world
