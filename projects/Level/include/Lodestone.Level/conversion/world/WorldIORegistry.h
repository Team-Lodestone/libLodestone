//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_WORLDIOREGISTRY_H
#define LODESTONE_WORLDIOREGISTRY_H
#include "Lodestone.Level/conversion/world/WorldIO.h"

namespace lodestone::level::conversion::world {
    /** Creates worlds based on registered world IO classes */
    class LODESTONE_API WorldIORegistry {
    protected:
        WorldIORegistry() = default;

    public:
        static WorldIORegistry sInstance;

        void registerWorldIO(const lodestone::common::registry::NamespacedString &id,
                             std::unique_ptr<const WorldIO> io);

        const WorldIO *getWorldIO(const lodestone::common::registry::NamespacedString &id) const;

    private:
        gtl::flat_hash_map<lodestone::common::registry::NamespacedString, std::unique_ptr<const WorldIO>,
            NamespacedStringHasher, NamespacedStringComparator> mRegisteredWorldIOs = {};
    };
}

#endif //LODESTONE_WORLDIOREGISTRY_H
