//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#ifndef LODESTONE_LEVELENTITY_H
#define LODESTONE_LEVELENTITY_H
#include "Lodestone.Level/entity/Entity.h"

// An entity stored in a chunk (as the player is stored in world instead)
namespace lodestone::level::entity {
    class ChunkEntity : public Entity {};
} // namespace lodestone::level::entity

#endif // LODESTONE_LEVELENTITY_H
