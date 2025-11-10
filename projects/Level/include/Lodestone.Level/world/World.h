//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_WORLD_H
#define LODESTONE_WORLD_H
#include <unordered_map>

#include <Lodestone.Common/string/StringSerializable.h>

#include "Lodestone.Level/Level.h"

namespace lodestone::level::conversion::world {
    class WorldIO;
}

namespace lodestone::level::world {
    class World : public StringSerializable {
    public:
        class Dimension {
            // just a class full of constants for now
        public:
            static constexpr const lodestone::common::registry::NamespacedString OVERWORLD = {"lodestone", "overworld"};
            static constexpr const lodestone::common::registry::NamespacedString NETHER = {"lodestone", "nether"};
            static constexpr const lodestone::common::registry::NamespacedString END = {"lodestone", "end"};
        };

        explicit World(const std::string &name = "New World") : mName(name) {
        }

        World(std::unique_ptr<Level> overworldLevel, const std::string &name = "New World") : mName(name) {
            this->mDimensions.emplace(Dimension::OVERWORLD, std::move(overworldLevel));
        }

        World(const std::string &name,
              gtl::flat_hash_map<lodestone::common::registry::NamespacedString, std::unique_ptr<Level>,
                  NamespacedStringHasher, NamespacedStringComparator> &&levels) : mName(std::move(name)),
            mDimensions(std::move(levels)) {
        }

        void addDimension(const lodestone::common::registry::NamespacedString &id, std::unique_ptr<Level> level);

        Level *getDimension(const lodestone::common::registry::NamespacedString &id) const;

        void removeDimension(const lodestone::common::registry::NamespacedString &id);

        bool hasDimension(const lodestone::common::registry::NamespacedString &id) const;

        std::string toString() const override {
            return (new OperatorStringBuilder(typeid(*this)))
                    ->ADD_FIELD(mName)
                    ->toString();
        };

        std::string getName() const { return mName; }

        virtual const lodestone::level::conversion::world::WorldIO *getIO() = 0;

    protected:
        std::string mName;
        /** Dimensions
         *
         * @tparam ID The dimension ID
         * @tparam Level The level
         */
        gtl::flat_hash_map<lodestone::common::registry::NamespacedString, std::unique_ptr<Level>, NamespacedStringHasher
            , NamespacedStringComparator> mDimensions;
    };
}

#endif //LODESTONE_WORLD_H