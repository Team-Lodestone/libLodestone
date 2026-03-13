//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_IDENTIFIABLE_H
#define LODESTONE_IDENTIFIABLE_H
#include "Lodestone.Common/registry/Identifier.h"

namespace lodestone::common::registry {
    struct IIdentifiable {};

    template <const Identifier *I>
    class Identifiable : public IIdentifiable {
    public:
        static constexpr const Identifier *getIdentifier() {
            return I;
        }
    };
}

#endif // LODESTONE_IDENTIFIABLE_H
