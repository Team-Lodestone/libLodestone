//
// Created by DexrnZacAttack on 11/27/25 using zPc-i2.
//
#ifndef LODESTONE_GAMEMODE_H
#define LODESTONE_GAMEMODE_H
#include "Lodestone.Common/registry/Identifier.h"

namespace lodestone::minecraft::common::player {
    struct Abilities {
        bool canFly;
        bool invulnerable;
        bool canInstabuild;

        bool operator==(const Abilities &rhs) const {
            return this->canFly == rhs.canFly && this->invulnerable == rhs.invulnerable && this->canInstabuild == rhs.canInstabuild;
        }
    };
}

namespace std {
    template <>
    struct hash<lodestone::minecraft::common::player::Abilities> {
        size_t operator()(
            const lodestone::minecraft::common::player::Abilities &s) const noexcept {
            return std::hash<bool>{}(s.canFly)
                 ^ std::hash<bool>{}(s.invulnerable) << 1
                 ^ std::hash<bool>{}(s.canFly) << 2;
        }
    };
}

#endif // LODESTONE_GAMEMODE_H
