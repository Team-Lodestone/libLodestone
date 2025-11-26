//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/mcregion/player/McRegionPlayer.h"

#include "Lodestone.Minecraft.Java/Identifiers.h"
#include <Lodestone.Level/world/World.h>

#include <Lodestone.Common/util/Math.h>

namespace lodestone::minecraft::java::mcregion::player {
    McRegionPlayer::McRegionPlayer(const std::string &name)
        : MinecraftPlayer(name), mIsSleeping(false), mSleepTimer(0) {}

    short McRegionPlayer::getSleepTimer() const { return mSleepTimer; }

    void McRegionPlayer::setSleepTimer(const short sleepTimer) {
        mSleepTimer = sleepTimer;
    }

    bool McRegionPlayer::isSleeping() const { return mIsSleeping; }

    void McRegionPlayer::setSleeping(const bool isSleeping) {
        mIsSleeping = isSleeping;
    }

    const lodestone::common::registry::Identifier &
    McRegionPlayer::dimensionIdToIdentifier(const int id) {
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
    int McRegionPlayer::identifierToDimensionId(
        const lodestone::common::registry::Identifier &str) {
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

    const lodestone::common::registry::Identifier *
    McRegionPlayer::getType() const {
        return &identifiers::MCREGION;
    }

    std::shared_ptr<level::properties::AbstractProperty>
    McRegionPlayer::getProperty(const std::string &name) {
        switch (lodestone::common::util::Math::fnv1a64(name.data(),
                                                       name.length())) {
            ADD_PROPERTY("sleepTimer", mSleepTimer, short &);
            ADD_PROPERTY("sleeping", mIsSleeping, bool &);
        default:
            return MinecraftPlayer::getProperty(name);
        }
    }
} // namespace lodestone::minecraft::java::mcregion::player
