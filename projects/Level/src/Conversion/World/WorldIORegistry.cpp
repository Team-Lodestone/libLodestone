//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#include "Conversion/World/WorldIORegistry.h"

namespace lodestone::level::conversion::world {
    WorldIORegistry *WorldIORegistry::sInstance = new WorldIORegistry();

    void WorldIORegistry::registerWorldIO(const std::string &id, const WorldIO* io) {
        if (mRegisteredWorldIOs.count(id))
            throw std::runtime_error("WorldIO already exists");

        mRegisteredWorldIOs[id] = std::move(io);
    }

    const WorldIO * WorldIORegistry::getWorldIO(const std::string &id) const {
        if (!mRegisteredWorldIOs.count(id))
            return nullptr;

        return mRegisteredWorldIOs.at(id);
    }
}
