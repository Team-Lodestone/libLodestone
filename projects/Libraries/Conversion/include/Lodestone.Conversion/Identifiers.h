//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#ifndef LODESTONE_CONVERSION_IDENTIFIERS_H
#define LODESTONE_CONVERSION_IDENTIFIERS_H
#include <Lodestone.Common/registry/Identifier.h>

// Misc identifiers
namespace lodestone::conversion::identifiers {
    // Block data
    constexpr const common::registry::Identifier ABSTRACT_BLOCK_DATA = {
        "lodestone", "abstract_block_data"};
    constexpr const common::registry::Identifier CLASSIC_BLOCK_DATA = {
        "lodestone", "classic_block_data"};
    constexpr const common::registry::Identifier NUMERIC_BLOCK_DATA = {
        "lodestone", "numeric_block_data"};
    constexpr const common::registry::Identifier EXTENDED_NUMERIC_BLOCK_DATA = {
        "lodestone", "extended_numeric_block_data"};
    constexpr const common::registry::Identifier FLATTENED_BLOCK_DATA = {
        "lodestone", "flattened_block_data"};
} // namespace lodestone::conversion::identifiers

#endif