//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#include "Lodestone.Minecraft.Common/world/data/LevelData.h"

namespace lodestone::minecraft::common::world::data {
    std::unique_ptr<level::properties::AbstractProperty>
    LevelData::getProperty(const std::string &name) {
        SWITCH_STRING (name) {
            ADD_FIELD_PROPERTY("seed", seed);
            ADD_FIELD_PROPERTY("lastPlayed", lastPlayed);
            ADD_FIELD_PROPERTY("time", time);
            default:
            return nullptr;
        }
    }
}
