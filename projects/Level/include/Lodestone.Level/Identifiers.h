//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVEL_IDENTIFIERS_H
#define LODESTONE_LEVEL_IDENTIFIERS_H
#include <Lodestone.Common/registry/Identifier.h>

namespace lodestone::level::identifiers {
    // Properties
    namespace properties {
        constexpr common::registry::Identifier ABSTRACT_PROPERTY = {
            "lodestone", "abstract_property"};
        constexpr common::registry::Identifier TEMPLATED_PROPERTY = {
            "lodestone", "templated_property"};
    } // namespace properties
} // namespace lodestone::level::identifiers

#endif // LODESTONE_LEVEL_IDENTIFIERS_H