//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONWORLD_H
#define LODESTONE_MCREGIONWORLD_H
#include <Lodestone.Level/world/World.h>

#include <Lodestone.Minecraft.Common/world/MinecraftWorld.h>

namespace lodestone::minecraft::java::mcr::world {
    class McRegionWorld final : public common::world::MinecraftWorld {
      public:
        explicit McRegionWorld(const std::string &name);

        std::string toString() const override {
            return std::format("McRegionWorld[name={}, seed={}, time={}]",
                               mName, mSeed, mTime);
        }

        const lodestone::conversion::world::WorldIO *getIO() override;

        bool isRaining() const;
        void setIsRaining(bool isRaining);

        int getRainTime() const;
        void setRainTime(int rainTime);

        bool isThundering() const;
        void setIsThundering(bool isThundering);

        int getThunderTime() const;
        void setThunderTime(int thunderTime);

        int32_t getVersion() const;
        void setVersion(const int32_t version);

      private:
        bool mIsRaining;
        int mRainTime;
        bool mIsThundering;
        int mThunderTime;

        int32_t mVersion;
    };
} // namespace lodestone::minecraft::java::mcr::world

#endif // LODESTONE_MCREGIONWORLD_H
