//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/mcregion/McRegionPlayer.h"

#include "Lodestone.Minecraft.Java/Identifiers.h"
#include <Lodestone.Level/world/World.h>

#include <Lodestone.Common/util/Math.h>

namespace lodestone::minecraft::java::mcregion::player {
    McRegionPlayer::McRegionPlayer(const std::string &name)
        : MinecraftPlayer(name), m_isSleeping(false), m_sleepTimer(0) {}

    short McRegionPlayer::getSleepTimer() const { return m_sleepTimer; }

    void McRegionPlayer::setSleepTimer(const short sleepTimer) {
        m_sleepTimer = sleepTimer;
    }

    bool McRegionPlayer::isSleeping() const { return m_isSleeping; }

    void McRegionPlayer::setSleeping(const bool isSleeping) {
        m_isSleeping = isSleeping;
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
        return &identifiers::MCREGION_CHUNK_IO;
    }

    std::unique_ptr<level::properties::AbstractProperty>
    McRegionPlayer::getProperty(const std::string &name) {
        switch (lodestone::common::util::Math::fnv1a64(name.data(),
                                                       name.length())) {
            ADD_FIELD_PROPERTY("sleepTimer", m_sleepTimer);
            ADD_FIELD_PROPERTY("sleeping", m_isSleeping);
        default:
            return MinecraftPlayer::getProperty(name);
        }
    }
} // namespace lodestone::minecraft::java::mcregion::player
