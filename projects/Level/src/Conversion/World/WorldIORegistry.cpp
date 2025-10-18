//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#include "Conversion/World/WorldIORegistry.h"

#include <iostream>

namespace lodestone::level::conversion::world {
    WorldIORegistry WorldIORegistry::sInstance = WorldIORegistry();

    void WorldIORegistry::registerWorldIO(const std::string &id, std::unique_ptr<const WorldIO> io) {
        if (mRegisteredWorldIOs.contains(id))
            throw std::runtime_error(std::format("WorldIO '{}' is already registered", id));

        mRegisteredWorldIOs[id] = std::move(io);

#if CMAKE_BUILD_DEBUG
        std::cout << "Registered WorldIO '" << id << "'" << std::endl;
#endif
    }

    const WorldIO * WorldIORegistry::getWorldIO(const std::string &id) const {
        if (const auto it = mRegisteredWorldIOs.find(id); it != mRegisteredWorldIOs.end())
            return it->second.get();

        return nullptr;
    }
}
