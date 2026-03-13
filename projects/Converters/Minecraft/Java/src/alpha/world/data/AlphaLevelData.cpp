//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/alpha/AlphaLevelData.h"

namespace lodestone::minecraft::java::alpha::world::data {
    std::unique_ptr<level::properties::AbstractProperty> AlphaLevelData::getProperty(const std::string &name) {
        switch (lodestone::common::util::Math::fnv1a64(name.data(),
                                               name.length())) {
            ADD_FIELD_PROPERTY("snowCovered", snowCovered);
            default:
            return LevelData::getProperty(name);
                                               }
    }
}
