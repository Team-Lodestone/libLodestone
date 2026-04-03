/** @file InfdevChunk.h
*
* @author Zero_DSRS_VX
* @date 3/29/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#ifndef LODESTONE_INFDEVCHUNK_H
#define LODESTONE_INFDEVCHUNK_H
#include "Lodestone.Level/chunk/LevelChunk.h"

namespace lodestone::minecraft::java::infdev::chunk {

    class InfdevChunk final : public level::chunk::LevelChunk {
    public:
        explicit InfdevChunk(const int64_t lastUpdate = 0)
            : LevelChunk(128), m_lastUpdate(lastUpdate) {}

        explicit InfdevChunk(const level::types::Vec2i &coords,
                               const int64_t lastUpdate = 0)
            : LevelChunk(128, coords), m_lastUpdate(lastUpdate) {}

        InfdevChunk(level::chunk::ChunkContainer *container,
                      const level::types::Vec2i &coords,
                      const int64_t lastUpdate = 0)
            : LevelChunk(128, container, coords), m_lastUpdate(lastUpdate) {}

        std::string toString() const override {
            if (this->m_coords.has_value())
                return std::format("InfdevChunk[coords={},lastUpdate={}]",
                                   m_coords->toString(), m_lastUpdate);

            return std::format("InfdevChunk");
        };

    private:
        int64_t m_lastUpdate = 0;
    };

}

#endif //LODESTONE_INFDEVCHUNK_H
