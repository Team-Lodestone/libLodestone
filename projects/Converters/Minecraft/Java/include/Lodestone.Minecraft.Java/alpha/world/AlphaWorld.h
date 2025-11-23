//
// Created by Zero on 11/20/25.
//

#ifndef LODESTONE_JAVA_ALPHAWORLD_H
#define LODESTONE_JAVA_ALPHAWORLD_H
#include <Lodestone.Level/world/World.h>

namespace lodestone::minecraft::java::alpha::world {

    class AlphaWorld final : public level::world::World {
      public:
        explicit AlphaWorld(const std::string &name);

        int64_t getSeed() const;
        void setSeed(int64_t seed);

        int64_t getLastPlayed() const;
        void setLastPlayed(int64_t lastPlayed);

        int64_t getTime() const;
        void setTime(int64_t time);

      private:
        bool mSnowCovered = false;

        int64_t mSeed = 0;
        int64_t mLastPlayed = 0;
        int64_t mTime = 0;
    };

} // namespace lodestone::minecraft::java::alpha::world

#endif // LODESTONE_JAVA_ALPHAWORLD_H
