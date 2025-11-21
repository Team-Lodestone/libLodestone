//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_WORLDIOREGISTRY_H
#define LODESTONE_WORLDIOREGISTRY_H
#include "Lodestone.Conversion/world/WorldIO.h"

namespace lodestone::conversion::world {
    /** Creates worlds based on registered world IO classes */
    class LODESTONE_API WorldIORegistry {
      protected:
        WorldIORegistry() = default;

      public:
        static WorldIORegistry &getInstance();

        void registerWorldIO(const lodestone::common::registry::Identifier &id,
                             std::unique_ptr<const WorldIO> io);

        const WorldIO *
        getWorldIO(const lodestone::common::registry::Identifier &id) const;

      private:
        map_t<lodestone::common::registry::Identifier,
              std::unique_ptr<const WorldIO>, IdentifierHasher,
              IdentifierComparator>
            mRegisteredWorldIOs = {};
    };
} // namespace lodestone::conversion::world

#endif // LODESTONE_WORLDIOREGISTRY_H
