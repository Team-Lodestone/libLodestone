//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#ifndef LODESTONE_NAMESPACES_H
#define LODESTONE_NAMESPACES_H
#include <Lodestone.Common/registry/Identifier.h>

namespace lodestone::java::identifiers {
    static constexpr lodestone::common::registry::Identifier MINEV1 = {"lodestone", "minev1"};
    static constexpr lodestone::common::registry::Identifier MINEV2 = {"lodestone", "minev2"};
    static constexpr lodestone::common::registry::Identifier MCLEVEL = {"lodestone", "mclevel"};
    static constexpr lodestone::common::registry::Identifier MCREGION = {"lodestone", "mcregion"};

    // TODO can't we just use MCREGION instead of making types like this?
    static constexpr lodestone::common::registry::Identifier MCREGION_PLAYER = {"lodestone", "mcregion_player"};
} // namespace lodestone::java::identifiers

#endif // LODESTONE_NAMESPACES_H
