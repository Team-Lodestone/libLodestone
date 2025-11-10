//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "world/World.h"

namespace lodestone::level::world {
    void World::addDimension(const registry::NamespacedString &id, std::unique_ptr<Level> level) {

        if (hasDimension(id)) throw std::runtime_error(std::format("Dimension '{}' already exists in world '{}'", id, mName));

        mDimensions[id] = std::move(level);
    }

    Level *World::getDimension(const registry::NamespacedString &id) const {
        if (!hasDimension(id)) return nullptr;

        return mDimensions.at(id).get();
    }

    void World::removeDimension(const registry::NamespacedString &id) {
        if (!hasDimension(id)) throw std::runtime_error(std::format("Cannot remove nonexistent dimension '{}' in world '{}'", id, mName));

        mDimensions.erase(id);
    }

    bool World::hasDimension(const registry::NamespacedString &id) const {
        return mDimensions.contains(id);
    }
}
