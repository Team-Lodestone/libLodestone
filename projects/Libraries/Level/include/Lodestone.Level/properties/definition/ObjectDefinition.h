//
// Created by DexrnZacAttack on 2/13/26 using zPc-i2.
//
#ifndef LODESTONE_BLOCKDEFINITION_H
#define LODESTONE_BLOCKDEFINITION_H
#include <Lodestone.Common/Defines.h>
#include <Lodestone.Common/registry/Identifier.h>
#include "Lodestone.Level/properties/AbstractProperty.h"

namespace lodestone::level::properties::definition {
    class ObjectDefinition {
    public:
        ObjectDefinition(const common::registry::Identifier *identifier,
            const map_t<common::registry::Identifier, properties::AbstractProperty *> &defaultProperties);

        const common::registry::Identifier *identifier;
        const map_t<common::registry::Identifier, properties::AbstractProperty *> defaultProperties;
    };
}

#endif // LODESTONE_BLOCKDEFINITION_H
