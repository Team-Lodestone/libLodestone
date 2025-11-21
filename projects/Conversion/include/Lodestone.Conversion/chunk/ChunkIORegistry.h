//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_CHUNKIOFACTORY_H
#define LODESTONE_CHUNKIOFACTORY_H
#include <memory>
#include <string>

#include "Lodestone.Conversion/chunk/ChunkIO.h"

namespace lodestone::conversion::chunk {
    /** Creates chunks based on registered chunk IO classes */
    class LODESTONE_API ChunkIORegistry {
      protected:
        ChunkIORegistry() = default;

      public:
        static ChunkIORegistry sInstance;

        void registerChunkIO(const lodestone::common::registry::Identifier &id,
                             std::unique_ptr<const ChunkIO> io);

        const ChunkIO *
        getChunkIO(const lodestone::common::registry::Identifier &id) const;

      private:
        map_t<lodestone::common::registry::Identifier,
              std::unique_ptr<const ChunkIO>, IdentifierHasher,
              IdentifierComparator>
            mRegisteredChunkIOs = {};
    };
} // namespace lodestone::conversion::chunk

#endif // LODESTONE_CHUNKIOFACTORY_H