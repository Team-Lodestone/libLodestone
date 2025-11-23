//
// Created by DexrnZacAttack on 10/17/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKS_H
#define LODESTONE_BLOCKS_H

#include <Lodestone.Common/registry/Identifier.h>

namespace lodestone::level::block {
    struct Blocks {
#define ADD_BLOCK(name, id)                                                    \
    static constexpr const lodestone::common::registry::Identifier name =      \
        lodestone::common::registry::Identifier {                              \
        "lodestone", id                                                        \
    }

        ADD_BLOCK(AIR, "air");
    };
} // namespace lodestone::level::block

#endif // LODESTONE_BLOCKS_H