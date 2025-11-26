//
// Created by DexrnZacAttack on 11/22/25 using zPc-i2.
//
#ifndef LODESTONE_MINECRAFTWORLD_H
#define LODESTONE_MINECRAFTWORLD_H
#include <Lodestone.Level/world/World.h>

namespace lodestone::minecraft::common::world {
    class MinecraftWorld : public level::world::World {
      public:
        explicit MinecraftWorld(const std::string &name);

        int64_t getSeed() const;
        void setSeed(int64_t seed);

        int64_t getLastPlayed() const;
        void setLastPlayed(int64_t lastPlayed);

        int64_t getTime() const;
        void setTime(int64_t time);

        std::shared_ptr<level::properties::AbstractProperty> getProperty(const std::string &name) override;

      protected:
        int64_t mSeed = 0;
        int64_t mLastPlayed = 0;
        int64_t mTime = 0;
    };
} // namespace lodestone::minecraft::common::world

#endif // LODESTONE_MINECRAFTWORLD_H
