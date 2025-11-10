//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Lodestone.Level/world/World.h"

namespace lodestone::level::world {
    void World::addDimension(const lodestone::common::registry::NamespacedString &id, std::unique_ptr<Level> level) {
        if (hasDimension(id)) throw std::runtime_error(
            std::format("Dimension '{}' already exists in world '{}'", id, mName));

        mDimensions[id] = std::move(level);
    }

    Level *World::getDimension(const lodestone::common::registry::NamespacedString &id) const {
        if (!hasDimension(id)) return nullptr;

        return mDimensions.at(id).get();
    }

    void World::removeDimension(const lodestone::common::registry::NamespacedString &id) {
        if (!hasDimension(id)) throw std::runtime_error(
            std::format("Cannot remove nonexistent dimension '{}' in world '{}'", id, mName));

        mDimensions.erase(id);
    }

    bool World::hasDimension(const lodestone::common::registry::NamespacedString &id) const {
        return mDimensions.contains(id);
    }
}
