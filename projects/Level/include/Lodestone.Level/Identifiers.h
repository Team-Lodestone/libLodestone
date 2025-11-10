//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#ifndef LODESTONE_LEVEL_IDENTIFIERS_H
#define LODESTONE_LEVEL_IDENTIFIERS_H
#include "registry/NamespacedString.h"

// Misc identifiers
namespace lodestone::level::identifiers {
    // Block data
    constexpr const registry::NamespacedString ABSTRACT_BLOCK_DATA = {"lodestone", "abstract_block_data"};
    constexpr const registry::NamespacedString CLASSIC_BLOCK_DATA = {"lodestone", "classic_block_data"};
    constexpr const registry::NamespacedString NUMERIC_BLOCK_DATA = {"lodestone", "numeric_block_data"};
    constexpr const registry::NamespacedString FLATTENED_BLOCK_DATA = {"lodestone", "flattened_block_data"};

}

#endif //LODESTONE_IDENTIFIERS_H