//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONWORLD_H
#define LODESTONE_MCREGIONWORLD_H
#include <Lodestone.Level/world/World.h>

namespace lodestone::java::mcr::world {
    class McRegionWorld final : public level::world::World {
    public:
        explicit McRegionWorld(const std::string &name);

        const lodestone::level::conversion::world::WorldIO * getIO() override;

        int64_t getSeed() const;
        void setSeed(int64_t seed);

        const level::types::Vec3i & getSpawnPos() const;
        void setSpawnPos(const level::types::Vec3i &spawnPos);

        int64_t getTime() const;
        void setTime(const int64_t time);

        bool isRaining() const;
        void setIsRaining(bool isRaining);

        int getRainTime() const;
        void setRainTime(int rainTime);

        bool isThundering() const;
        void setIsThundering(bool isThundering);

        int getThunderTime() const;
        void setThunderTime(int thunderTime);

        int64_t getLastPlayed() const;
        void setLastPlayed(int64_t lastPlayed);

        int64_t getSize() const;
        void setSize(int64_t size);

        int32_t getVersion() const;
        void setVersion(const int32_t version);

    private:
        int64_t mSeed;
        level::types::Vec3i mSpawnPos;

        int64_t mTime;

        bool mIsRaining;
        int mRainTime;
        bool mIsThundering;
        int mThunderTime;

        int64_t mLastPlayed;
        int64_t mSize; // shouldnt this be dynamic?
        int32_t mVersion;
    };
}

#endif //LODESTONE_MCREGIONWORLD_H
