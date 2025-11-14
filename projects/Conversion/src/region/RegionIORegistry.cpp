//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Lodestone.Conversion/region/RegionIORegistry.h"

#include <iostream>

#include <Lodestone.Common/registry/NamespacedString.h>

namespace lodestone::conversion::region {
    RegionIORegistry RegionIORegistry::sInstance = RegionIORegistry();

    void RegionIORegistry::registerRegionIO(const lodestone::common::registry::NamespacedString &id,
                                            std::unique_ptr<const RegionIO> io) {
        if (mRegisteredRegionIOs.contains(id))
            throw std::runtime_error(std::format("RegionIO '{}' is already registered", id));

        mRegisteredRegionIOs[id] = std::move(io);

#if CMAKE_BUILD_DEBUG
        std::cout << "Registered RegionIO '" << id << "'" << std::endl;
#endif
    }

    const RegionIO *RegionIORegistry::getRegionIO(const lodestone::common::registry::NamespacedString &id) const {
        if (const auto it = mRegisteredRegionIOs.find(id); it != mRegisteredRegionIOs.end())
            return it->second.get();

        return nullptr;
    }
}