//
// Created by DexrnZacAttack on 11/23/25 using zPc-i2.
//
#ifndef LODESTONE_JUNGLEANVILCHUNK_H
#define LODESTONE_JUNGLEANVILCHUNK_H
#include <Lodestone.Level/chunk/LevelChunk.h>

namespace lodestone::minecraft::java::anvil::jungle::chunk {
    class JungleAnvilChunk final : public level::chunk::LevelChunk {
      public:
        explicit JungleAnvilChunk(const int64_t lastUpdate = 0)
            : LevelChunk(256), mLastUpdate(lastUpdate) {}

        explicit JungleAnvilChunk(const level::types::Vec2i &coords,
                               const int64_t lastUpdate = 0)
            : LevelChunk(256, coords), mLastUpdate(lastUpdate) {}

        JungleAnvilChunk(level::chunk::ChunkContainer *container,
                      const level::types::Vec2i &coords,
                      const int64_t lastUpdate = 0)
            : LevelChunk(256, container, coords), mLastUpdate(lastUpdate) {}

        std::string toString() const override {
            if (this->mCoords.has_value())
                return std::format("JungleAnvilChunk[coords={},lastUpdate={}]",
                                   mCoords->toString(), mLastUpdate);

            return std::format("JungleAnvilChunk");
        };

      private:
        // TODO tileticks
        int64_t mLastUpdate = 0;
    };
} // namespace lodestone::minecraft::java::mcr::chunk

#endif // LODESTONE_JUNGLEANVILCHUNK_H