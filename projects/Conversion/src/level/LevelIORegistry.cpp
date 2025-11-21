//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Lodestone.Conversion/level/LevelIORegistry.h"

#include <iostream>

#include <Lodestone.Common/Logging.h>

namespace lodestone::conversion::level {
    LevelIoRegistry &LevelIoRegistry::getInstance() {
        static LevelIoRegistry sInstance;
        return sInstance;
    }

    void LevelIoRegistry::registerLevelIO(const lodestone::common::registry::Identifier &id,
                                          std::unique_ptr<const PlayerIO> io) {
        if (mRegisteredLevelIOs.contains(id))
            throw std::runtime_error(std::format("LevelIO '{}' is already registered", id));

        mRegisteredLevelIOs[id] = std::move(io);

        LOG_DEBUG("Registered LevelIO '" << id << "'");
    }

    const PlayerIO *LevelIoRegistry::getLevelIO(const lodestone::common::registry::Identifier &id) const {
        if (const auto it = mRegisteredLevelIOs.find(id); it != mRegisteredLevelIOs.end())
            return it->second.get();

        return nullptr;
    }
}
