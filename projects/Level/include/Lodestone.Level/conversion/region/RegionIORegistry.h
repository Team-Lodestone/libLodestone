//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_REGIONIOFACTORY_H
#define LODESTONE_REGIONIOFACTORY_H
#include <string>
#include <memory>

#include "Lodestone.Level/conversion/region/RegionIO.h"

namespace lodestone::level::conversion::region {
    /** Creates regions based on registered region IO classes */
    class LODESTONE_API RegionIORegistry {
    protected:
        RegionIORegistry() = default;
    public:
        static RegionIORegistry sInstance;

        void registerRegionIO(const registry::NamespacedString &id, std::unique_ptr<const RegionIO> io);

        const RegionIO *getRegionIO(const registry::NamespacedString &id) const;
    private:
        gtl::flat_hash_map<registry::NamespacedString, std::unique_ptr<const RegionIO>, NamespacedStringHasher, NamespacedStringComparator> mRegisteredRegionIOs = {};
    };
}

#endif //LODESTONE_REGIONIOFACTORY_H
