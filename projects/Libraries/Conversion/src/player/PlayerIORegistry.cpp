//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Lodestone.Conversion/player/PlayerIORegistry.h"

#include <iostream>

#include <Lodestone.Common/util/Logging.h>

namespace lodestone::conversion::player {

    PlayerIORegistry &PlayerIORegistry::getInstance() {
        static PlayerIORegistry sInstance;
        return sInstance;
    }

    void PlayerIORegistry::registerPlayerIO(
        const lodestone::common::registry::Identifier &id,
        std::unique_ptr<const PlayerIO> io) {
        if (mRegisteredPlayerIOs.contains(id))
            throw std::runtime_error(
                std::format("PlayerIO '{}' is already registered", id));

        mRegisteredPlayerIOs[id] = std::move(io);

        LOG_DEBUG("Registered PlayerIO '" << id << "'");
    }

    const PlayerIO *PlayerIORegistry::getPlayerIO(
        const lodestone::common::registry::Identifier &id) const {
        if (const auto it = mRegisteredPlayerIOs.find(id);
            it != mRegisteredPlayerIOs.end())
            return it->second.get();

        return nullptr;
    }
} // namespace lodestone::conversion::player
