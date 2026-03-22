//
// Created by DexrnZacAttack on 11/19/25 using zPc-i2.
//
#ifndef LODESTONE_CORE_LODESTONE_H
#define LODESTONE_CORE_LODESTONE_H
#include "Lodestone.Core/LodestoneExtension.h"
#include <Lodestone.Common/internal/Defines.h>
#include <Lodestone.Common/registry/Identifier.h>
#include "Lodestone.Core/internal/Exports.h"

namespace lodestone::core {
    /** The core Lodestone class, used for registering other plugin libs. */
    class LODESTONE_CORE_API Lodestone {
      public:
        static Lodestone *getInstance();

        void registerExtension(LodestoneExtension *ext);
        bool hasExtension(const common::registry::Identifier &id) const;
        LodestoneExtension *
        getExtension(const common::registry::Identifier &id);
        const map_t<common::registry::Identifier, LodestoneExtension *> &
        getExtensions();

      private:
        map_t<common::registry::Identifier, LodestoneExtension *>
            m_extensions;
    };
} // namespace lodestone::core

#endif // LODESTONE_CORE_LODESTONE_H
