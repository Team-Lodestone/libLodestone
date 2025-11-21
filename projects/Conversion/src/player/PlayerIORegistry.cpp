//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Lodestone.Conversion/player/PlayerIORegistry.h"

#include <iostream>

namespace lodestone::conversion::player {
    PlayerIORegistry PlayerIORegistry::sInstance = PlayerIORegistry();

    void PlayerIORegistry::registerPlayerIO(
        const lodestone::common::registry::Identifier &id,
        std::unique_ptr<const PlayerIO> io) {
        if (mRegisteredPlayerIOs.contains(id))
            throw std::runtime_error(
                std::format("PlayerIO '{}' is already registered", id));

        mRegisteredPlayerIOs[id] = std::move(io);

#if CMAKE_BUILD_DEBUG
        std::cout << "Registered PlayerIO '" << id << "'" << std::endl;
#endif
    }

    const PlayerIO *PlayerIORegistry::getPlayerIO(
        const lodestone::common::registry::Identifier &id) const {
        if (const auto it = mRegisteredPlayerIOs.find(id);
            it != mRegisteredPlayerIOs.end())
            return it->second.get();

        return nullptr;
    }
} // namespace lodestone::conversion::player
