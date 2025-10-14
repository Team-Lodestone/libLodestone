//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_LEVEL_H
#define LODESTONE_LEVEL_H
#include <unordered_map>
#include <Chunk/Chunk.h>
#include <Chunk/ChunkCoords.h>

namespace lodestone::level {
    class Level {
        std::unordered_map<chunk::ChunkCoords, chunk::Chunk> mChunks; // or should it be ordered?
    };
}

#endif //LODESTONE_LEVEL_H
