//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Lodestone.Level/world/World.h"

namespace lodestone::level::world {
    Level *World::addLevel(const lodestone::common::registry::Identifier &id,
                           std::unique_ptr<Level> level) {
        if (hasLevel(id))
            throw std::runtime_error(std::format(
                "Level '{}' already exists in world '{}'", id, m_name));

        Level *l = level.get();
        l->setWorld(this);
        m_levels[id] = std::move(level);

        return l;
    }

    Level *
    World::getLevel(const lodestone::common::registry::Identifier &id) const {
        if (const auto it = m_levels.find(id); it != m_levels.end())
            return it->second.get();

        return nullptr;
    }

    void World::removeLevel(const lodestone::common::registry::Identifier &id) {
        if (!hasLevel(id))
            throw std::runtime_error(std::format(
                "Cannot remove nonexistent level '{}' in world '{}'", id,
                m_name));

        m_levels.erase(id);
    }

    bool
    World::hasLevel(const lodestone::common::registry::Identifier &id) const {
        return m_levels.contains(id);
    }

    std::string World::getName() const { return m_name; }

    void World::setName(const std::string &n) { this->m_name = n; }

    level::Level *World::getDefaultLevel() const {
        return getLevel(Dimension::OVERWORLD);
    }

    size_t World::getPlayerCount() const { return m_players.size(); }

    entity::Player *World::addPlayer(std::unique_ptr<entity::Player> player,
                                     const bool resetCoords) {
        const std::string &id = player->getId();
        if (hasPlayer(id))
            throw std::runtime_error(
                std::format("Attempted to add duplicate player '{}'", id));

        entity::Player *p = player.get();
        this->m_players[id] = std::move(player);
        p->setWorld(this, resetCoords);

        return p; // I think this should work??
    }

    entity::Player *World::getPlayer(const std::string &id) const {
        if (const auto it = m_players.find(id); it != m_players.end())
            return it->second.get();

        return nullptr;
    }

    std::unique_ptr<entity::Player> World::removePlayer(const std::string &id) {
        const auto it = m_players.find(id);
        if (it == m_players.end())
            return nullptr;

        it->second->m_world = nullptr;
        it->second->m_currentLevel = nullptr;

        std::unique_ptr<entity::Player> player = std::move(it->second);
        m_players.erase(it);

        return player;
    }

    bool World::hasPlayer(const std::string &id) const {
        return m_players.contains(id);
    }

    uint64_t World::getCreationTime() {
        const auto m = std::ranges::min_element(this->m_levels, {}, [](const auto &l) -> uint64_t {
            if (!l.second)
                return 0;

            return l.second->getCreationTime();
        });

        if (m != this->m_levels.end() && m->second != nullptr)
            return m->second->getCreationTime();

        return 0;
    }

    std::unique_ptr<level::properties::AbstractProperty>
    World::getProperty(const std::string &name) {
        return nullptr;
    }

    const map_t<std::string, std::unique_ptr<entity::Player>> &
    World::getPlayers() const {
        return m_players;
    }

    const map_t<lodestone::common::registry::Identifier, std::unique_ptr<Level>> &
    World::getLevels() const {
        return m_levels;
    }
} // namespace lodestone::level::world
