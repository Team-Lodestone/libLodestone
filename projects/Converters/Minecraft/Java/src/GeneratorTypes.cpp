//
// Created by Zero on 11/26/25.
//
#include "Lodestone.Minecraft.Java/GeneratorTypes.h"

#include <Lodestone.Common/util/Math.h>

namespace lodestone::minecraft::java {

    const lodestone::common::registry::Identifier &
    GeneratorTypes::generatorIdToIdentifier(const std::string &id) {
        switch (
            lodestone::common::util::Math::fnv1a64(id.data(), id.length())) {
        default:
        case "default"_hash:
            return GeneratorTypes::DEFAULT;
        case "flat"_hash:
            return GeneratorTypes::FLAT;
        case "largeBiomes"_hash:
            return GeneratorTypes::LARGE_BIOMES;
        }
    }

    std::string GeneratorTypes::identifierToGeneratorId(
        const lodestone::common::registry::Identifier &id, int version) {
        switch (lodestone::common::util::Math::fnv1a64(id)) {
        default:
        case lodestone::common::util::Math::fnv1a64(GeneratorTypes::DEFAULT):
            return "default";
        case lodestone::common::util::Math::fnv1a64(GeneratorTypes::FLAT):
            return "flat";
        case lodestone::common::util::Math::fnv1a64(
            GeneratorTypes::LARGE_BIOMES):
            return "largeBiomes";
        }
    }
} // namespace lodestone::minecraft::java