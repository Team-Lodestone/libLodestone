//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_CHUNKIOFACTORY_H
#define LODESTONE_CHUNKIOFACTORY_H
#include <string>
#include <memory>

#include "Lodestone.Level/Conversion/Chunk/ChunkIO.h"

namespace lodestone::level::conversion::chunk {
    /** Creates chunks based on registered chunk IO classes */
    class LODESTONE_API ChunkIORegistry {
    protected:
        ChunkIORegistry() = default;
    public:
        static ChunkIORegistry sInstance;

        void registerChunkIO(const std::string &id, std::unique_ptr<const ChunkIO> io);

        const ChunkIO *getChunkIO(const std::string &id) const;
    private:
        std::unordered_map<std::string, std::unique_ptr<const ChunkIO>> mRegisteredChunkIOs = {};
    };
}

#endif //LODESTONE_CHUNKIOFACTORY_H
