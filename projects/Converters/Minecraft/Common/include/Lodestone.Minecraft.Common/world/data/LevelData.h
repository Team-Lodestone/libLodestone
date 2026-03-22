//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_LEVELDATA_H
#define LODESTONE_LEVELDATA_H
#include "Lodestone.Level/properties/ReflectiveProperties.h"
#include "Lodestone.Minecraft.Common/internal/Exports.h"

namespace lodestone::minecraft::common::world::data {
    struct LODESTONE_MINECRAFT_COMMON_API LevelData : level::properties::ReflectiveProperties  {
        std::unique_ptr<level::properties::AbstractProperty>
        getProperty(const std::string &name) override;

        int64_t seed;
        int64_t lastPlayed;
        int64_t time;

        LevelData(const int64_t seed = 0, const int64_t lastPlayed = 0, const int64_t time = 0) : seed(seed), lastPlayed(lastPlayed), time(time) {}
    };
}

#endif // LODESTONE_LEVELDATA_H
