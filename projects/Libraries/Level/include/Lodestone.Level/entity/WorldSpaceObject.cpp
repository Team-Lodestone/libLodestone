//
// Created by DexrnZacAttack on 1/29/26 using zPc-i2.
//
#include "Lodestone.Level/entity/WorldSpaceObject.h"

namespace lodestone::level::entity {
    WorldSpaceObject::WorldSpaceObject() {
    }

    types::Vec3f WorldSpaceObject::getFront() const {
        return (getDirection() - static_cast<types::Vec3f>(this->position)).normalize();
    }

    types::Vec3f WorldSpaceObject::getDirection() const {
        return types::Vec3f(
            std::cosf(rotation.y) * std::cosf(rotation.x),
            std::sinf(rotation.y),
            std::cosf(rotation.y) * std::sinf(rotation.x)
        );
    }

    types::Vec3d WorldSpaceObject::getTarget() const {
        return position + static_cast<types::Vec3d>(getDirection());
    }
}
