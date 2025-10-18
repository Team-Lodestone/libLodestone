//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Conversion/Level/LevelIORegistry.h"

#include <iostream>

namespace lodestone::level::conversion::level {
    LevelIORegistry LevelIORegistry::sInstance = LevelIORegistry();

    void LevelIORegistry::registerLevelIO(const std::string &id, std::unique_ptr<const LevelIO> io) {
        if (mRegisteredLevelIOs.contains(id))
            throw std::runtime_error(std::format("LevelIO '{}' is already registered", id));

        mRegisteredLevelIOs[id] = std::move(io);

#if CMAKE_BUILD_DEBUG
        std::cout << "Registered LevelIO '" << id << "'" << std::endl;
#endif
    }

    const LevelIO * LevelIORegistry::getLevelIO(const std::string &id) const {
        if (const auto it = mRegisteredLevelIOs.find(id); it != mRegisteredLevelIOs.end())
            return it->second.get();

        return nullptr;
    }
}
