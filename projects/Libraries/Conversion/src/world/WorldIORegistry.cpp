//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#include "Lodestone.Conversion/world/WorldIORegistry.h"

#include <iostream>

#include <Lodestone.Common/util/Logging.h>

namespace lodestone::conversion::world {
    WorldIORegistry &WorldIORegistry::getInstance() {
        static WorldIORegistry sInstance;
        return sInstance;
    }

    void WorldIORegistry::registerWorldIO(
        const lodestone::common::registry::Identifier &id,
        std::unique_ptr<const WorldIO> io) {
        if (mRegisteredWorldIOs.contains(id))
            throw std::runtime_error(
                std::format("WorldIO '{}' is already registered", id));

        mRegisteredWorldIOs[id] = std::move(io);

        LOG_DEBUG("Registered WorldIO '" << id << "'");
    }

    const WorldIO *WorldIORegistry::getWorldIO(
        const lodestone::common::registry::Identifier &id) const {
        if (const auto it = mRegisteredWorldIOs.find(id);
            it != mRegisteredWorldIOs.end())
            return it->second.get();

        return nullptr;
    }
} // namespace lodestone::conversion::world
