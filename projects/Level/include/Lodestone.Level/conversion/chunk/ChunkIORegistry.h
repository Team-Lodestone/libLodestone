//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_CHUNKIOFACTORY_H
#define LODESTONE_CHUNKIOFACTORY_H
#include <string>
#include <memory>

#include "Lodestone.Level/conversion/chunk/ChunkIO.h"

namespace lodestone::level::conversion::chunk {
    /** Creates chunks based on registered chunk IO classes */
    class LODESTONE_API ChunkIORegistry {
    protected:
        ChunkIORegistry() = default;

    public:
        static ChunkIORegistry sInstance;

        void registerChunkIO(const lodestone::common::registry::NamespacedString &id,
                             std::unique_ptr<const ChunkIO> io);

        const ChunkIO *getChunkIO(const lodestone::common::registry::NamespacedString &id) const;

    private:
        gtl::flat_hash_map<lodestone::common::registry::NamespacedString, std::unique_ptr<const ChunkIO>,
            NamespacedStringHasher, NamespacedStringComparator> mRegisteredChunkIOs = {};
    };
}

#endif //LODESTONE_CHUNKIOFACTORY_H