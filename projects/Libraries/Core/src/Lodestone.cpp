//
// Created by DexrnZacAttack on 11/19/25 using zPc-i2.
//
#include "Lodestone.Core/Lodestone.h"

#include <iostream>

#include <Lodestone.Common/util/Logging.h>

namespace lodestone::core {
    Lodestone *Lodestone::getInstance() {
        static Lodestone s_instance;
        return &s_instance;
    }

    void Lodestone::registerExtension(LodestoneExtension *ext) {
        common::registry::Identifier id = ext->getIdentifier();
        if (hasExtension(id))
            throw std::runtime_error(
                "Tried to register extension with id that already exists.");

        m_extensions.emplace(id, ext);
    }

    bool Lodestone::hasExtension(const common::registry::Identifier &id) const {
        return m_extensions.contains(id);
    }

    LodestoneExtension *
    Lodestone::getExtension(const common::registry::Identifier &id) {
        if (const auto it = m_extensions.find(id); it != m_extensions.end())
            return it->second;

        return nullptr;
    }

    const map_t<common::registry::Identifier, LodestoneExtension *> &
    Lodestone::getExtensions() {
        return m_extensions;
    }
} // namespace lodestone::core
