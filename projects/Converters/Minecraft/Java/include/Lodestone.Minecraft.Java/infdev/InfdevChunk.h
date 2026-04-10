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
#include <Lodestone.Level/chunk/LevelChunk.h>

namespace lodestone::minecraft::java::infdev::chunk {

    class InfdevChunk final : public level::chunk::LevelChunk {
    public:
        static constexpr int CHUNK_WIDTH = 16;
        static constexpr int CHUNK_DEPTH = 16;
        static constexpr int CHUNK_HEIGHT = 128;

        /** Size of the chunk header in bytes */
        static constexpr int CHUNK_HEADER_SIZE = sizeof(int32_t) // chunk x coord
                                               + sizeof(int32_t) // chunk z coord
                                               + sizeof(int64_t) // inhabited time
                                               + sizeof(int64_t) // properties
                                               + 232;            // extra padding/reserved

        /** Size of the chunk heightmap in bytes */
        static constexpr int CHUNK_HEIGHTMAP_SIZE = CHUNK_WIDTH * CHUNK_DEPTH;
        /** Size of the chunk block array in bytes */
        static constexpr int CHUNK_TOTAL_BLOCKS = CHUNK_WIDTH * CHUNK_DEPTH * CHUNK_HEIGHT;
        /** Size of the chunk layer in bytes (used for metadata, skylight, blocklight) */
        static constexpr int CHUNK_LAYER_SIZE = CHUNK_TOTAL_BLOCKS / 2;

        /** Amount of layers stored in the chunk (DataLayer)
         *
         * - Metadata
         * - Sky light
         * - Block light
         */
        static constexpr int CHUNK_LAYERS = 3;

        /** Incorrect chunk size in bytes, used for getting the zone offset
         *
         * The calculation is incorrect, please use CHUNK_SIZE_BYTES for the actual size in bytes
         */
        static constexpr int CHUNK_SIZE_SLOT_OFFSET = CHUNK_TOTAL_BLOCKS * CHUNK_LAYERS + CHUNK_HEADER_SIZE; // not the true size tho??? I mean technically it works since it will be bigger than the real size...
        /** Chunk size in bytes */
        static constexpr int CHUNK_BYTES = /*header*/CHUNK_HEADER_SIZE + /*block array*/CHUNK_TOTAL_BLOCKS + /*metadata, skylight, blocklight*/(CHUNK_LAYER_SIZE * CHUNK_LAYERS) + /*heightmap*/CHUNK_HEIGHTMAP_SIZE;

        explicit InfdevChunk(const int64_t lastUpdate = 0, const bool isPopulated = true)
            : LevelChunk(128), m_lastUpdate(lastUpdate), m_terrainPopulated(isPopulated) {}

        InfdevChunk(const level::coords::ChunkCoordinates &coords,
                      const int64_t lastUpdate = 0, const bool isPopulated = true, level::chunk::ChunkContainer *container = nullptr)
            : LevelChunk(128, coords, container), m_lastUpdate(lastUpdate), m_terrainPopulated(isPopulated) {}

        std::string toString() const override {
            if (this->m_coords.has_value())
                return std::format("InfdevChunk[coords={},lastUpdate={}]",
                                   m_coords->toString(), m_lastUpdate);

            return std::format("InfdevChunk");
        };
    private:
        int64_t m_lastUpdate = 0;
        bool m_terrainPopulated = true;
    };

}

#endif //LODESTONE_INFDEVCHUNK_H
