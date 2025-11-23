//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_REGIONIOFACTORY_H
#define LODESTONE_REGIONIOFACTORY_H
#include <memory>
#include <string>

#include "Lodestone.Conversion/region/RegionIO.h"

namespace lodestone::conversion::region {
    /** Creates regions based on registered region IO classes */
    class LODESTONE_API RegionIORegistry {
      protected:
        RegionIORegistry() = default;

      public:
        static RegionIORegistry &getInstance();

        void registerRegionIO(const lodestone::common::registry::Identifier &id,
                              std::unique_ptr<const RegionIO> io);

        const RegionIO *
        getRegionIO(const lodestone::common::registry::Identifier &id) const;

      private:
        map_t<lodestone::common::registry::Identifier,
              std::unique_ptr<const RegionIO>, IdentifierHasher,
              IdentifierComparator>
            mRegisteredRegionIOs = {};
    };
} // namespace lodestone::conversion::region

#endif // LODESTONE_REGIONIOFACTORY_H