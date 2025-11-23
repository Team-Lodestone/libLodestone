//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_LEVELIOFACTORY_H
#define LODESTONE_LEVELIOFACTORY_H
#include <string>

#include "Lodestone.Conversion/level/LevelIO.h"

namespace lodestone::conversion::level {
    // TODO It might be a good idea to require library class instance for
    // registering these IO classes
    /** Creates chunks based on registered chunk IO classes */
    class LODESTONE_API LevelIoRegistry {
      protected:
        LevelIoRegistry() = default;

      public:
        static LevelIoRegistry &getInstance();

        void registerLevelIO(const lodestone::common::registry::Identifier &id,
                             std::unique_ptr<const PlayerIO> io);

        const PlayerIO *
        getLevelIO(const lodestone::common::registry::Identifier &id) const;

      private:
        map_t<lodestone::common::registry::Identifier,
              std::unique_ptr<const PlayerIO>, IdentifierHasher,
              IdentifierComparator>
            mRegisteredLevelIOs;
    };
} // namespace lodestone::conversion::level

#endif // LODESTONE_LEVELIOFACTORY_H