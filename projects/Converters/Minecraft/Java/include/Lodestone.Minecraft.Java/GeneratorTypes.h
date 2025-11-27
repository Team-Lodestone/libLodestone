//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#ifndef LODESTONE_GENERATORTYPES_H
#define LODESTONE_GENERATORTYPES_H
#include <Lodestone.Common/registry/Identifier.h>

namespace lodestone::minecraft::java {
    struct GeneratorTypes {
        static constexpr lodestone::common::registry::Identifier DEFAULT = {
            "minecraft", "default"};
        static constexpr lodestone::common::registry::Identifier FLAT = {
            "minecraft", "flat"};
        static constexpr lodestone::common::registry::Identifier LARGE_BIOMES =
            {"minecraft", "large_biomes"};

        static const lodestone::common::registry::Identifier &
        generatorIdToIdentifier(const std::string &id);
        static std::string identifierToGeneratorId(
            const lodestone::common::registry::Identifier &id, int version);
    };
} // namespace lodestone::minecraft::java

#endif
