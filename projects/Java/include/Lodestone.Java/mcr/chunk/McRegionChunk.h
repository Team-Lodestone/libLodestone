//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONCHUNK_H
#define LODESTONE_MCREGIONCHUNK_H
#include "Lodestone.Level/chunk/LevelChunk.h"

namespace lodestone::java::mcr::chunk {
    class McRegionChunk final : public level::chunk::LevelChunk {
    public:
        explicit McRegionChunk(const int64_t lastUpdate = 0, const bool terrainPopulated = true) : LevelChunk(128), mLastUpdate(lastUpdate), mPopulated(terrainPopulated) {}
        explicit McRegionChunk(const level::types::Vec2i &coords, const int64_t lastUpdate = 0, const bool terrainPopulated = true) : LevelChunk(128, coords), mLastUpdate(lastUpdate), mPopulated(terrainPopulated) {}
        McRegionChunk(level::chunk::ChunkContainer *container, const level::types::Vec2i &coords, const int64_t lastUpdate = 0, const bool terrainPopulated = true) : LevelChunk(128, container, coords), mLastUpdate(lastUpdate), mPopulated(terrainPopulated) {}

        std::string toString() const override {
            if (this->mCoords.has_value())
                return std::format("McRegionChunk[coords={},lastUpdate={},populated={}]", mCoords->toString(), mLastUpdate, mPopulated);

            return std::format("McRegionChunk");
        };

    private:
        int64_t mLastUpdate = 0;
        bool mPopulated = false;
    };
}

#endif //LODESTONE_MCREGIONCHUNK_H
