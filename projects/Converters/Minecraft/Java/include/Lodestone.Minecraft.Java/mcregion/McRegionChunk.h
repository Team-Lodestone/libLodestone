//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONCHUNK_H
#define LODESTONE_MCREGIONCHUNK_H
#include <Lodestone.Level/chunk/LevelChunk.h>

namespace lodestone::minecraft::java::mcregion::chunk {
    class McRegionChunk final : public level::chunk::LevelChunk {
      public:
        explicit McRegionChunk(const int64_t lastUpdate = 0)
            : LevelChunk(128), m_lastUpdate(lastUpdate) {}

        explicit McRegionChunk(const level::coords::ChunkCoordinates &coords,
                               const int64_t lastUpdate = 0, level::chunk::ChunkContainer *container = nullptr)
            : LevelChunk(128, coords, container), m_lastUpdate(lastUpdate) {}

        std::string toString() const override {
            if (this->m_coords.has_value())
                return std::format("McRegionChunk[coords={},lastUpdate={}]",
                                   m_coords->toString(), m_lastUpdate);

            return std::format("McRegionChunk");
        };

      private:
        int64_t m_lastUpdate = 0;
    };
} // namespace lodestone::minecraft::java::mcregion::chunk

#endif // LODESTONE_MCREGIONCHUNK_H