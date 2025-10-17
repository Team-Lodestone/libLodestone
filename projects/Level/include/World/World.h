//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_WORLD_H
#define LODESTONE_WORLD_H
#include <unordered_map>

#include "Level.h"
#include "String/StringSerializable.h"

namespace lodestone::level::world {
    class World : public StringSerializable {
    public:
        class Dimension { // just a class full of constants for now
            static constexpr const char *OVERWORLD = "lodestone:overworld";
            static constexpr const char *NETHER = "lodestone:nether";
            static constexpr const char *END = "lodestone:end";
        };

        World(const std::string &name = "New World") : mName(name) {}
        World(const std::unordered_map<std::string, Level*> &levels, const std::string &name = "New World") : mName(name), mDimensions(levels) {}

        void addDimension(const std::string &id, Level *level);
        Level *getDimension(const std::string &id) const;
        void removeDimension(const std::string &id);
        bool hasDimension(const std::string &id) const;

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
