//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#include "Conversion/World/WorldIoRegistry.h"

namespace lodestone::level::conversion::world {
    WorldIoRegistry *WorldIoRegistry::sInstance = new WorldIoRegistry();

    void WorldIoRegistry::registerWorldIO(const std::string &id, const WorldIo* io) {
        if (mRegisteredWorldIOs.count(id))
            throw std::runtime_error("WorldIO already exists");

        mRegisteredWorldIOs[id] = std::move(io);
    }
}
