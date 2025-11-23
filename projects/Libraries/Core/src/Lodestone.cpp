//
// Created by DexrnZacAttack on 11/19/25 using zPc-i2.
//
#include "Lodestone.Core/Lodestone.h"

#include <iostream>

#include <Lodestone.Common/util/Logging.h>

namespace lodestone::core {
    Lodestone *Lodestone::getInstance() {
        static Lodestone sInstance;
        return &sInstance;
    }

    void Lodestone::registerExtension(LodestoneExtension *ext) {
        common::registry::Identifier id = ext->getIdentifier();
        if (hasExtension(id))
            throw std::runtime_error(
                "Tried to register extension with id that already exists.");

        LOG_DEBUG(std::format("Registered extension '{}' v{}", id.getString(),
                              ext->getVersion()));
        mExtensions.emplace(id, ext);
    }

    bool Lodestone::hasExtension(const common::registry::Identifier &id) {
        return mExtensions.contains(id);
    }

    LodestoneExtension *
    Lodestone::getExtension(const common::registry::Identifier &id) {
        if (const auto it = mExtensions.find(id); it != mExtensions.end())
            return it->second;

        return nullptr;
    }

    const map_t<common::registry::Identifier, LodestoneExtension *,
                IdentifierHasher, IdentifierComparator> &
    Lodestone::getExtensions() {
        return mExtensions;
    }
} // namespace lodestone::core
