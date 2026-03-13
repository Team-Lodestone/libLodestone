//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/mcregion/McRegionLevelData.h"

namespace lodestone::minecraft::java::mcregion::world::data {
    std::unique_ptr<level::properties::AbstractProperty> McRegionLevelData::getProperty(const std::string &name) {
        switch (lodestone::common::util::Math::fnv1a64(name.data(),
                                               name.length())) {
            ADD_FIELD_PROPERTY("raining", isRaining);
            ADD_FIELD_PROPERTY("rainTime", rainTime);
            ADD_FIELD_PROPERTY("thundering", isThundering);
            ADD_FIELD_PROPERTY("thunderTime", thunderTime);
            ADD_FIELD_PROPERTY("version", version);
            ADD_FIELD_PROPERTY("hardcore", isHardcore);
            default:
            return LevelData::getProperty(name);
        }
    }
}
