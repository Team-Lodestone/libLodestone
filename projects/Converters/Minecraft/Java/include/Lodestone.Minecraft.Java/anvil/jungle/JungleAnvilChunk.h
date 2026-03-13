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
            : LevelChunk(256), m_lastUpdate(lastUpdate) {}

        explicit JungleAnvilChunk(const level::types::Vec2i &coords,
                                  const int64_t lastUpdate = 0)
            : LevelChunk(256, coords), m_lastUpdate(lastUpdate) {}

        JungleAnvilChunk(level::chunk::ChunkContainer *container,
                         const level::types::Vec2i &coords,
                         const int64_t lastUpdate = 0)
            : LevelChunk(256, container, coords), m_lastUpdate(lastUpdate) {}

        std::string toString() const override {
            if (this->m_coords.has_value())
                return std::format("JungleAnvilChunk[coords={},lastUpdate={}]",
                                   m_coords->toString(), m_lastUpdate);

            return std::format("JungleAnvilChunk");
        };

      private:
        // TODO tileticks
        int64_t m_lastUpdate = 0;
    };
} // namespace lodestone::minecraft::java::anvil::jungle::chunk

#endif // LODESTONE_JUNGLEANVILCHUNK_H