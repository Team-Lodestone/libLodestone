//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_ALPHALEVELDATA_H
#define LODESTONE_ALPHALEVELDATA_H
#include <Lodestone.Minecraft.Common/world/data/LevelData.h>

namespace lodestone::minecraft::java::alpha::world::data {
    struct AlphaLevelData : common::world::data::LevelData {
        std::unique_ptr<level::properties::AbstractProperty>
        getProperty(const std::string &name) override;

        explicit AlphaLevelData(const int64_t seed = 0, const int64_t lastPlayed = 0,
                        const int64_t time = 0, const bool snowCovered = false)
    : LevelData(seed, lastPlayed, time),
      snowCovered(snowCovered) {
        }

        bool snowCovered = false;
    };
}

#endif // LODESTONE_ALPHALEVELDATA_H
