//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Conversion/Level/LevelIORegistry.h"

namespace lodestone::level::conversion::level {
    LevelIORegistry *LevelIORegistry::sInstance = new LevelIORegistry();

    LevelIORegistry::LevelIORegistry() {
    }

    void LevelIORegistry::registerLevelIO(const std::string &id, const LevelIO* io) {
        if (mRegisteredLevelIOs.count(id))
            throw std::runtime_error("LevelIO already exists");

        mRegisteredLevelIOs[id] = std::move(io);
    }
}
