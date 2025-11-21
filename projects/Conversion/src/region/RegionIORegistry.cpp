//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Lodestone.Conversion/region/RegionIORegistry.h"

#include <iostream>

#include <Lodestone.Common/registry/Identifier.h>

#include <Lodestone.Common/Logging.h>

namespace lodestone::conversion::region {
    RegionIORegistry &RegionIORegistry::getInstance() {
        static RegionIORegistry sInstance;
        return sInstance;
    }

    void RegionIORegistry::registerRegionIO(
        const lodestone::common::registry::Identifier &id,
        std::unique_ptr<const RegionIO> io) {
        if (mRegisteredRegionIOs.contains(id))
            throw std::runtime_error(
                std::format("RegionIO '{}' is already registered", id));

        mRegisteredRegionIOs[id] = std::move(io);

        LOG_DEBUG("Registered RegionIO '" << id << "'");
    }

    const RegionIO *RegionIORegistry::getRegionIO(
        const lodestone::common::registry::Identifier &id) const {
        if (const auto it = mRegisteredRegionIOs.find(id);
            it != mRegisteredRegionIOs.end())
            return it->second.get();

        return nullptr;
    }
} // namespace lodestone::conversion::region