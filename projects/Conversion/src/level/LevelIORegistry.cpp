//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Lodestone.Conversion/level/LevelIORegistry.h"

#include <iostream>

namespace lodestone::conversion::level {
    PlayerIORegistry PlayerIORegistry::sInstance = PlayerIORegistry();

    void PlayerIORegistry::registerLevelIO(
        const lodestone::common::registry::Identifier &id,
        std::unique_ptr<const PlayerIO> io) {
        if (mRegisteredLevelIOs.contains(id))
            throw std::runtime_error(
                std::format("LevelIO '{}' is already registered", id));

        mRegisteredLevelIOs[id] = std::move(io);

#if CMAKE_BUILD_DEBUG
        std::cout << "Registered LevelIO '" << id << "'" << std::endl;
#endif
    }

    const PlayerIO *PlayerIORegistry::getLevelIO(
        const lodestone::common::registry::Identifier &id) const {
        if (const auto it = mRegisteredLevelIOs.find(id);
            it != mRegisteredLevelIOs.end())
            return it->second.get();

        return nullptr;
    }
} // namespace lodestone::conversion::level
