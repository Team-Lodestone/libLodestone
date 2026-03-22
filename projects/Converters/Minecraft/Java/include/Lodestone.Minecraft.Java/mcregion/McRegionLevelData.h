//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONLEVELDATA_H
#define LODESTONE_MCREGIONLEVELDATA_H
#include <Lodestone.Minecraft.Common/world/data/LevelData.h>

#include "Lodestone.Minecraft.Java/internal/Exports.h"
#include <memory>

namespace lodestone::minecraft::java::mcregion::world::data {
    struct LODESTONE_MINECRAFT_JAVA_API McRegionLevelData : common::world::data::LevelData {
        static constexpr int DEFAULT_VERSION = 19132;

        McRegionLevelData(const int64_t seed, const int64_t lastPlayed, const int64_t time,
            const bool isHardcore, const bool isRaining, const int rainTime, const bool isThundering,
            const int thunderTime, const int32_t version = DEFAULT_VERSION)
            : LevelData(seed, lastPlayed, time),
              isHardcore(isHardcore),
              isRaining(isRaining),
              rainTime(rainTime),
              isThundering(isThundering),
              thunderTime(thunderTime),
              version(version) {
        }

        std::unique_ptr<level::properties::AbstractProperty>
        getProperty(const std::string &name) override;

        /** Whether the world difficulty has been set to Hardcore
         *
         * @prop hardcore
         */
        bool isHardcore;
        /** Whether it's currently raining in the world
         *
         * @prop raining
         */
        bool isRaining;
        /**
         * @prop rainTime
         */
        int rainTime;
        /** Whether it's currently a thunderstorm in the world
         *
         * @prop thundering
         */
        bool isThundering;
        /**
         * @prop thunderTime
         */
        int thunderTime;

        /** The world version
         *
         * @prop version
         */
        int32_t version = DEFAULT_VERSION;
    };
}

#endif // LODESTONE_MCREGIONLEVELDATA_H
