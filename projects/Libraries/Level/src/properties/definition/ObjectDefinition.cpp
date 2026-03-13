//
// Created by DexrnZacAttack on 2/13/26 using zPc-i2.
//
#include "Lodestone.Level/properties/definition/ObjectDefinition.h"

namespace lodestone::level::properties::definition {
    ObjectDefinition::ObjectDefinition(const common::registry::Identifier *identifier,
    const map_t<common::registry::Identifier, properties::AbstractProperty *> &defaultProperties) : identifier(identifier), defaultProperties(defaultProperties) {
    }
}
