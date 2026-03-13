//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#ifndef LODESTONE_CONVERSION_IDENTIFIERS_H
#define LODESTONE_CONVERSION_IDENTIFIERS_H
#include <Lodestone.Common/registry/Identifier.h>

// Misc identifiers
namespace lodestone::conversion::identifiers {
    // Block data
    inline constexpr const common::registry::Identifier ABSTRACT_BLOCK_DATA = {
        "lodestone", "abstract_block_data"};
    inline constexpr const common::registry::Identifier CLASSIC_BLOCK_DATA = {
        "lodestone", "classic_block_data"};
    inline constexpr const common::registry::Identifier NUMERIC_BLOCK_DATA = {
        "lodestone", "numeric_block_data"};
    inline constexpr const common::registry::Identifier EXTENDED_NUMERIC_BLOCK_DATA = {
        "lodestone", "extended_numeric_block_data"};
    inline constexpr const common::registry::Identifier FLATTENED_BLOCK_DATA = {
        "lodestone", "flattened_block_data"};

    // Registries
    inline constexpr const common::registry::Identifier REGION_IO_REGISTRY = {
        "lodestone", "registry/region_io"};
    inline constexpr const common::registry::Identifier PLAYER_IO_REGISTRY = {
        "lodestone", "registry/player_io"};
    inline constexpr const common::registry::Identifier LEVEL_IO_REGISTRY = {
        "lodestone", "registry/level_io"};
    inline constexpr const common::registry::Identifier WORLD_IO_REGISTRY = {
        "lodestone", "registry/world_io"};
    inline constexpr const common::registry::Identifier CHUNK_IO_REGISTRY = {
        "lodestone", "registry/chunk_io"};

    inline constexpr const common::registry::Identifier IO_REGISTRY = {
        "lodestone", "registry/io"};

    // IO
    inline constexpr const common::registry::Identifier PLAYER_IO = {
        "lodestone", "io/player"};

    inline constexpr const common::registry::Identifier REGION_IO = {
        "lodestone", "io/region"};

    inline constexpr const common::registry::Identifier LEVEL_IO = {
        "lodestone", "io/level"};

    inline constexpr const common::registry::Identifier WORLD_IO = {
        "lodestone", "io/world"};

    inline constexpr const common::registry::Identifier CHUNK_IO = {
        "lodestone", "io/chunk"};
} // namespace lodestone::conversion::identifiers

#endif