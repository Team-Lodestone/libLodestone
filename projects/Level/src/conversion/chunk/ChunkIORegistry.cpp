//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Lodestone.Level/conversion/chunk/ChunkIORegistry.h"

#include <iostream>

namespace lodestone::level::conversion::chunk {
    ChunkIORegistry ChunkIORegistry::sInstance = ChunkIORegistry();

    void ChunkIORegistry::registerChunkIO(const lodestone::common::registry::NamespacedString &id,
                                          std::unique_ptr<const ChunkIO> io) {
        if (mRegisteredChunkIOs.contains(id))
            throw std::runtime_error(std::format("ChunkIO '{}' is already registered", id));

        mRegisteredChunkIOs[id] = std::move(io);

#if CMAKE_BUILD_DEBUG
        std::cout << "Registered ChunkIO '" << id << "'" << std::endl;
#endif
    }

    const ChunkIO *ChunkIORegistry::getChunkIO(const lodestone::common::registry::NamespacedString &id) const {
        if (const auto it = mRegisteredChunkIOs.find(id); it != mRegisteredChunkIOs.end())
            return it->second.get();

        return nullptr;
    }
}
