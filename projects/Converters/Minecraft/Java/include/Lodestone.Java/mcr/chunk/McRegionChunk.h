//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONCHUNK_H
#define LODESTONE_MCREGIONCHUNK_H
#include <Lodestone.Level/chunk/LevelChunk.h>

namespace lodestone::java::mcr::chunk {
    class McRegionChunk final : public level::chunk::LevelChunk {
      public:
        explicit McRegionChunk(const int64_t lastUpdate = 0)
            : LevelChunk(128), mLastUpdate(lastUpdate) {}

        explicit McRegionChunk(const level::types::Vec2i &coords,
                               const int64_t lastUpdate = 0)
            : LevelChunk(128, coords), mLastUpdate(lastUpdate) {}

        McRegionChunk(level::chunk::ChunkContainer *container,
                      const level::types::Vec2i &coords,
                      const int64_t lastUpdate = 0)
            : LevelChunk(128, container, coords), mLastUpdate(lastUpdate) {}

        std::string toString() const override {
            if (this->mCoords.has_value())
                return std::format("McRegionChunk[coords={},lastUpdate={}]",
                                   mCoords->toString(), mLastUpdate);

            return std::format("McRegionChunk");
        };

      private:
        int64_t mLastUpdate = 0;
    };
} // namespace lodestone::java::mcr::chunk

#endif // LODESTONE_MCREGIONCHUNK_H