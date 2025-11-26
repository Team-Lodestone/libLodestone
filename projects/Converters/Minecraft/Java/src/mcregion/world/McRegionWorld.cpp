//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/mcregion/world/McRegionWorld.h"

#include "Lodestone.Minecraft.Java/Identifiers.h"
#include <Lodestone.Conversion/world/WorldIORegistry.h>

#include <Lodestone.Common/util/Math.h>

namespace lodestone::minecraft::java::mcregion::world {
    McRegionWorld::McRegionWorld(const std::string &name)
        : MinecraftWorld(name), mIsRaining(false), mRainTime(0),
          mIsThundering(false), mThunderTime(0) {}

    const lodestone::conversion::world::WorldIO *McRegionWorld::getIO() {
        return lodestone::conversion::world::WorldIORegistry::getInstance()
            .getWorldIO(identifiers::MCREGION);
    }

    bool McRegionWorld::isRaining() const { return mIsRaining; }

    void McRegionWorld::setIsRaining(const bool isRaining) {
        mIsRaining = isRaining;
    }

    int McRegionWorld::getRainTime() const { return mRainTime; }

    void McRegionWorld::setRainTime(const int rainTime) {
        mRainTime = rainTime;
    }

    bool McRegionWorld::isThundering() const { return mIsThundering; }

    void McRegionWorld::setIsThundering(const bool isThundering) {
        mIsThundering = isThundering;
    }

    int McRegionWorld::getThunderTime() const { return mThunderTime; }

    void McRegionWorld::setThunderTime(const int thunderTime) {
        mThunderTime = thunderTime;
    }

    int32_t McRegionWorld::getVersion() const { return mVersion; }

    void McRegionWorld::setVersion(const int32_t version) {
        mVersion = version;
    }

    std::shared_ptr<level::properties::AbstractProperty>
    McRegionWorld::getProperty(const std::string &name) {
        switch (lodestone::common::util::Math::fnv1a64(name.data(),
                                                       name.length())) {
            ADD_PROPERTY("raining", mIsRaining, bool &);
            ADD_PROPERTY("rainTime", mRainTime, int32_t &);
            ADD_PROPERTY("thundering", mIsThundering, bool &);
            ADD_PROPERTY("thunderTime", mThunderTime, int32_t &);
            ADD_PROPERTY("version", mVersion, int32_t &);
        default:
            return MinecraftWorld::getProperty(name);
        }
    }
} // namespace lodestone::minecraft::java::mcregion::world
