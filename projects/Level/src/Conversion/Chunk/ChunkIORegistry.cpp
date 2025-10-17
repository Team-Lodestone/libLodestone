//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Conversion/Chunk/ChunkIORegistry.h"

namespace lodestone::level::conversion::chunk {
    void ChunkIORegistry::registerChunkIO(const std::string &id, const ChunkIO* io) {
        if (mRegisteredChunkIOs.count(id))
            throw std::runtime_error("ChunkIO already exists");

        mRegisteredChunkIOs[id] = std::move(io);
    }
}
