//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#ifndef LODESTONE_ITEMS_H
#define LODESTONE_ITEMS_H

#include <Lodestone.Common/registry/Identifier.h>

namespace lodestone::level::item {
    struct Items {
#define ADD_ITEM(name, id)                                                     \
    static constexpr const lodestone::common::registry::Identifier name =      \
        lodestone::common::registry::Identifier {                              \
        "lodestone", id                                                        \
    }

        ADD_ITEM(NONE, "none");
    };
} // namespace lodestone::level::item

#endif // LODESTONE_ITEMS_H