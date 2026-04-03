//
// Created by DexrnZacAttack on 11/21/25 using zPc-i2.
//
#ifndef LODESTONE_MINECRAFT_COMMON_NAMESPACES_H
#define LODESTONE_MINECRAFT_COMMON_NAMESPACES_H
#include "Lodestone.Common/registry/Identifier.h"

namespace lodestone::minecraft::common::identifiers {
    namespace registry {
        inline constexpr const lodestone::common::registry::Identifier LEVEL_DATA_IO_REGISTRY = {
            "lodestone.minecraft.common", "registry/level_data_io"};

        inline constexpr const lodestone::common::registry::Identifier REGION_IO_REGISTRY = {
            "lodestone", "registry/region_io"};
    }

    namespace io {
        inline constexpr const lodestone::common::registry::Identifier REGION_IO = {
            "lodestone", "io/region"};

        inline constexpr const lodestone::common::registry::Identifier NBT_IO = {
            "lodestone.minecraft.common", "io/nbt_io"};
    }

    namespace entity {
        inline constexpr const lodestone::common::registry::Identifier MINECRAFT_PLAYER = {
            "lodestone.minecraft.common", "entity/player"};
    }
} // namespace lodestone::minecraft::common::identifiers

#endif // LODESTONE_MINECRAFT_COMMON_NAMESPACES_H
