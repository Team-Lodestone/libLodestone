//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Lodestone.Conversion/chunk/ChunkIORegistry.h"

#include <iostream>

#include <Lodestone.Common/util/Logging.h>

namespace lodestone::conversion::chunk {
    ChunkIORegistry &ChunkIORegistry::getInstance() {
        static ChunkIORegistry sInstance;
        return sInstance;
    }

    void ChunkIORegistry::registerChunkIO(
        const lodestone::common::registry::Identifier &id,
        std::unique_ptr<const ChunkIO> io) {
        if (mRegisteredChunkIOs.contains(id))
            throw std::runtime_error(
                std::format("ChunkIO '{}' is already registered", id));

        mRegisteredChunkIOs[id] = std::move(io);
        LOG_DEBUG("Registered ChunkIO '" << id << "'");
    }

    const ChunkIO *ChunkIORegistry::getChunkIO(
        const lodestone::common::registry::Identifier &id) const {
        if (const auto it = mRegisteredChunkIOs.find(id);
            it != mRegisteredChunkIOs.end())
            return it->second.get();

        return nullptr;
    }
} // namespace lodestone::conversion::chunk
