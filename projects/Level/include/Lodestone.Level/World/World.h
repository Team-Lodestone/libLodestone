//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_WORLD_H
#define LODESTONE_WORLD_H
#include <unordered_map>

#include <Lodestone.Common/String/StringSerializable.h>
#include "Lodestone.Level/Level.h"

namespace lodestone::level::world {
    class World : public StringSerializable {
    public:
        class Dimension { // just a class full of constants for now
            static constexpr const registry::NamespacedString OVERWORLD = { "lodestone", "overworld" };
            static constexpr const registry::NamespacedString NETHER = { "lodestone", "nether" };
            static constexpr const registry::NamespacedString END = { "lodestone", "end" };
        };

        World(const std::string &name = "New World") : mName(name) {}
        World(const std::unordered_map<std::string, Level*> &levels, const std::string &name = "New World") : mName(name), mDimensions(levels) {}

        void addDimension(const registry::NamespacedString &id, Level *level);
        Level *getDimension(const registry::NamespacedString &id) const;
        void removeDimension(const registry::NamespacedString &id);
        bool hasDimension(const registry::NamespacedString &id) const;

        std::string toString() const override {
            return (new OperatorStringBuilder(typeid(*this)))
                ->ADD_FIELD(mName)
                ->toString();
        };

    protected:
        std::string mName;
        std::unordered_map<std::string, Level*> mDimensions;
    };
}

#endif //LODESTONE_WORLD_H
