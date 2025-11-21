//
// Created by DexrnZacAttack on 11/19/25 using zPc-i2.
//
#ifndef LODESTONE_LODESTONEEXTENSION_H
#define LODESTONE_LODESTONEEXTENSION_H
#include <Lodestone.Common/registry/Identifier.h>

namespace lodestone::core {
    class LodestoneExtension {
    public:
        virtual ~LodestoneExtension() = default;

        virtual common::registry::Identifier getIdentifier() = 0;
    };
}

#endif //LODESTONE_LODESTONEEXTENSION_H
