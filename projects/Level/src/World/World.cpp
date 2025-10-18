//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "World/World.h"

namespace lodestone::level::world {
    void World::addDimension(const std::string &id, Level *level) {

        if (hasDimension(id)) throw std::runtime_error(std::format("Dimension '{}' already exists in world '{}'", id, mName));

        mDimensions[id] = std::move(level);
    }

    Level *World::getDimension(const std::string &id) const {
        if (!hasDimension(id)) return nullptr;

        return mDimensions.at(id);
    }

    void World::removeDimension(const std::string &id) {
        if (!hasDimension(id)) throw std::runtime_error(std::format("Cannot remove nonexistent dimension '{}' in world '{}'", id, mName));

        mDimensions.erase(id);
    }

    bool World::hasDimension(const std::string &id) const {
        return mDimensions.count(id);
    }
}
