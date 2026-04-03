//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#ifndef LODESTONE_NAMESPACES_H
#define LODESTONE_NAMESPACES_H
#include <Lodestone.Common/registry/Identifier.h>

namespace lodestone::minecraft::java::identifiers {
    inline static constexpr lodestone::common::registry::Identifier MINEV1_LEVEL_IO = {
        "lodestone", "minecraft/java/io/level/minev1"};
    inline static constexpr lodestone::common::registry::Identifier MINEV2_LEVEL_IO = {
        "lodestone", "minecraft/java/io/level/minev2"};
    inline static constexpr lodestone::common::registry::Identifier MINEV2_WORLD_IO = {
        "lodestone", "minecraft/java/io/world/minev2"};

    inline static constexpr lodestone::common::registry::Identifier MCLEVEL_LEVEL_IO = {
        "lodestone", "minecraft/java/io/level/mclevel"};
    inline static constexpr lodestone::common::registry::Identifier MCLEVEL_NBT_LEVEL_IO = {
        "lodestone", "minecraft/java/io/nbt/level/mclevel"};

    inline static constexpr lodestone::common::registry::Identifier INF_624_CHUNK_IO = {
        "lodestone", "minecraft/java/io/chunk/inf_624"};
    inline static constexpr lodestone::common::registry::Identifier INF_624_NBT_CHUNK_IO = {
        "lodestone", "minecraft/java/io/nbt/chunk/inf_624"};
    inline static constexpr lodestone::common::registry::Identifier INF_624_ZONE_IO = {
        "lodestone", "minecraft/java/io/zone/inf_624"};
    inline static constexpr lodestone::common::registry::Identifier INF_624_LEVEL_IO = {
        "lodestone", "minecraft/java/io/level/inf_624"};
    inline static constexpr lodestone::common::registry::Identifier INF_624_WORLD_IO = {
        "lodestone", "minecraft/java/io/world/inf_624"};

    inline static constexpr lodestone::common::registry::Identifier ALPHA_PLAYER_IO = {
        "lodestone", "minecraft/java/io/player/alpha"};
    inline static constexpr lodestone::common::registry::Identifier ALPHA_NBT_PLAYER_IO = {
        "lodestone", "minecraft/java/io/nbt/player/alpha"};
    inline static constexpr lodestone::common::registry::Identifier ALPHA_WORLD_IO = {
        "lodestone", "minecraft/java/io/world/alpha"};

    inline static constexpr lodestone::common::registry::Identifier MCREGION_PLAYER_IO = {
        "lodestone", "minecraft/java/io/player/mcregion"};
    inline static constexpr lodestone::common::registry::Identifier MCREGION_NBT_PLAYER_IO = {
        "lodestone", "minecraft/java/io/nbt/player/mcregion"};
    inline static constexpr lodestone::common::registry::Identifier MCREGION_CHUNK_IO = {
        "lodestone", "minecraft/java/io/chunk/mcregion"};
    inline static constexpr lodestone::common::registry::Identifier MCREGION_NBT_CHUNK_IO = {
        "lodestone", "minecraft/java/io/nbt/chunk/mcregion"};
    inline static constexpr lodestone::common::registry::Identifier MCREGION_REGION_IO = {
        "lodestone", "minecraft/java/io/region/mcregion"};
    inline static constexpr lodestone::common::registry::Identifier MCREGION_WORLD_IO = {
        "lodestone", "minecraft/java/io/world/mcregion"};
    inline static constexpr lodestone::common::registry::Identifier MCREGION_LEVEL_DATA_IO = {
        "lodestone", "minecraft/java/io/level_data/mcregion"};
    inline static constexpr lodestone::common::registry::Identifier MCREGION_NBT_LEVEL_DATA_IO = {
        "lodestone", "minecraft/java/io/nbt/level_data/mcregion"};

    inline static constexpr lodestone::common::registry::Identifier ANVIL_JUNGLE_CHUNK_IO = {
        "lodestone", "minecraft/java/io/chunk/anvil_jungle"};
    inline static constexpr lodestone::common::registry::Identifier ANVIL_JUNGLE_NBT_CHUNK_IO = {
        "lodestone", "minecraft/java/io/nbt/chunk/anvil_jungle"};
    inline static constexpr lodestone::common::registry::Identifier ANVIL_JUNGLE_REGION_IO = {
        "lodestone", "minecraft/java/io/region/anvil_jungle"};
    inline static constexpr lodestone::common::registry::Identifier ANVIL_JUNGLE_WORLD_IO = {
        "lodestone", "minecraft/java/io/world/anvil_jungle"};

    inline static constexpr lodestone::common::registry::Identifier LEVEL_DATA_IO = {
        "lodestone", "minecraft/java/io/level_data"};

    inline static constexpr lodestone::common::registry::Identifier NBT_LEVEL_DATA_IO = {
        "lodestone", "minecraft/java/io/nbt/level_data"};
    inline static constexpr lodestone::common::registry::Identifier NBT_CHUNK_IO = {
        "lodestone", "minecraft/java/io/nbt/chunk"};
    inline static constexpr lodestone::common::registry::Identifier NBT_REGION_IO = {
        "lodestone", "minecraft/java/io/nbt/region"};
    inline static constexpr lodestone::common::registry::Identifier NBT_LEVEL_IO = {
        "lodestone", "minecraft/java/io/nbt/level"};
    inline static constexpr lodestone::common::registry::Identifier NBT_PLAYER_IO = {
        "lodestone", "minecraft/java/io/nbt/player"};
} // namespace lodestone::minecraft::java::identifiers

#endif // LODESTONE_NAMESPACES_H
