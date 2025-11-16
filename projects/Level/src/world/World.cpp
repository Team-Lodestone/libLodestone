//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Lodestone.Level/world/World.h"

namespace lodestone::level::world {
    Level *World::addLevel(const lodestone::common::registry::Identifier &id, std::unique_ptr<Level> level) {
        if (hasLevel(id)) throw std::runtime_error(
            std::format("Level '{}' already exists in world '{}'", id, mName));

        Level *l = level.get();
        l->setWorld(this);
        mLevels[id] = std::move(level);

        return l;
    }

    Level *World::getLevel(const lodestone::common::registry::Identifier &id) const {
        if (const auto it = mLevels.find(id); it != mLevels.end())
            return it->second.get();

        return nullptr;
    }

    void World::removeLevel(const lodestone::common::registry::Identifier &id) {
        if (!hasLevel(id)) throw std::runtime_error(
            std::format("Cannot remove nonexistent level '{}' in world '{}'", id, mName));

        mLevels.erase(id);
    }

    bool World::hasLevel(const lodestone::common::registry::Identifier &id) const {
        return mLevels.contains(id);
    }

    const lodestone::conversion::world::WorldIO * World::getIO() {
        return nullptr;
    }

    level::Level * World::getDefaultLevel() const {
        return getLevel(Dimension::OVERWORLD);
    }

    size_t World::getPlayerCount() const {
        return mPlayers.size();
    }

    entity::Player *World::addPlayer(std::unique_ptr<entity::Player> player) {
        const std::string &id = player->getId();
        if (hasPlayer(id)) throw std::runtime_error(std::format("Attempted to add duplicate player '{}'", id));

        entity::Player* p = player.get();
        this->mPlayers[id] = std::move(player);
        p->setWorld(this);

        return p; // I think this should work??
    }

    entity::Player * World::getPlayer(const std::string &id) const {
        if (const auto it = mPlayers.find(id); it != mPlayers.end()) return it->second.get();

        return nullptr;
    }

    void World::removePlayer(const std::string &id) {
        const auto it = mPlayers.find(id);
        if (it == mPlayers.end()) return;

        it->second->mPosition.reset();
        it->second->mWorld = nullptr;
        it->second->mCurrentLevel = nullptr;

        mPlayers.erase(it);
    }

    bool World::hasPlayer(const std::string &id) const {
        return mPlayers.contains(id);
    }

    void World::movePlayerToLevel(std::unique_ptr<entity::Player> player, const common::registry::Identifier &level, const bool resetCoords) {
        Level *lvl = getLevel(level);
        if (!lvl) throw std::runtime_error(std::format("Tried to move player '{}' to nonexistent level '{}'", player->getId(), level));

        entity::Player *p = player.get();
        if (player->mWorld != this) {
            if (player->mWorld) player->mWorld->removePlayer(player->getId());
            p = addPlayer(std::move(player));
        }

        p->setLevel(lvl, resetCoords);
    }

    void World::movePlayerToWorld(std::unique_ptr<entity::Player> player, World *world) {
        if (player->mWorld == this) return;

        removePlayer(player->getId());
        world->addPlayer(std::move(player));
    }

    const gtl::flat_hash_map<std::string, std::unique_ptr<entity::Player>> &World::getPlayers() const {
        return mPlayers;
    }

    const gtl::flat_hash_map<lodestone::common::registry::Identifier, std::unique_ptr<Level>,
    IdentifierHasher, IdentifierComparator> & World::getLevels() const {
        return mLevels;
    }
}
