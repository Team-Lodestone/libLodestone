//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_LEVELIOFACTORY_H
#define LODESTONE_LEVELIOFACTORY_H
#include <string>

#include "Lodestone.Level/conversion/level/LevelIO.h"

namespace lodestone::level::conversion::level {
    /** Creates chunks based on registered chunk IO classes */
    class LODESTONE_API LevelIORegistry {
    protected:
        LevelIORegistry() = default;

    public:
        static LevelIORegistry sInstance;

        void registerLevelIO(const lodestone::common::registry::NamespacedString &id,
                             std::unique_ptr<const LevelIO> io);

        const LevelIO *getLevelIO(const lodestone::common::registry::NamespacedString &id) const;

    private:
        gtl::flat_hash_map<lodestone::common::registry::NamespacedString, std::unique_ptr<const LevelIO>,
            NamespacedStringHasher, NamespacedStringComparator> mRegisteredLevelIOs;
    };
}

#endif //LODESTONE_LEVELIOFACTORY_H