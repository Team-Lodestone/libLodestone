//
// Created by DexrnZacAttack on 11/19/25 using zPc-i2.
//
#ifndef LODESTONE_CORE_LODESTONE_H
#define LODESTONE_CORE_LODESTONE_H
#include "Lodestone.Core/LodestoneExtension.h"
#include <Lodestone.Common/Defines.h>
#include <Lodestone.Common/registry/Identifier.h>

namespace lodestone::core {
    /** The core Lodestone class, used for registering other plugin libs. */
    class Lodestone {
    public:
        static Lodestone *getInstance();

        void registerExtension(LodestoneExtension *ext);
        bool hasExtension(const common::registry::Identifier &id);
        LodestoneExtension *getExtension(const common::registry::Identifier &id);
        const map_t<common::registry::Identifier, LodestoneExtension*, IdentifierHasher, IdentifierComparator> &getExtensions();

    private:
        map_t<common::registry::Identifier, LodestoneExtension*, IdentifierHasher, IdentifierComparator> mExtensions;
    };
}

#endif //LODESTONE_CORE_LODESTONE_H
