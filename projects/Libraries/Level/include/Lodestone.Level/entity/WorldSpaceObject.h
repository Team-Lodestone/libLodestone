//
// Created by DexrnZacAttack on 1/29/26 using zPc-i2.
//
#ifndef LODESTONE_WORLDSPACEOBJECT_H
#define LODESTONE_WORLDSPACEOBJECT_H

#include "Lodestone.Level/types/Vec2.h"
#include "Lodestone.Level/types/Vec3.h"

namespace lodestone::level::entity {
    class WorldSpaceObject {
    public:
        WorldSpaceObject();
        virtual ~WorldSpaceObject() = default;

        types::Vec3f getFront() const;
        types::Vec3f getDirection() const;
        types::Vec3d getTarget() const;

        types::Vec3d position = types::VEC3_ZERO<double>;
        types::Vec2f rotation = types::VEC2_ZERO<float>;
    };
}

#endif // LODESTONE_WORLDSPACEOBJECT_H
