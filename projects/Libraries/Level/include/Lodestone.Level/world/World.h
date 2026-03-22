//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_WORLD_H
#define LODESTONE_WORLD_H
#include <Lodestone.Common/util/Util.h>

#include <unordered_map>

#include <Lodestone.Common/string/StringSerializable.h>

#include "Lodestone.Level/Level.h"
#include "Lodestone.Level/entity/Player.h"
#include "Lodestone.Level/properties/ReflectiveProperties.h"

namespace lodestone::conversion::world {
    class WorldIO;
}

namespace lodestone::level::world {
    class World : public common::string::StringSerializable,
                  public properties::ReflectiveProperties {
      public:
        class Dimension {
            // just a class full of constants for now
          public:
            static constexpr const common::registry::Identifier
                OVERWORLD = {"lodestone", "overworld"};
            static constexpr const common::registry::Identifier
                NETHER = {"lodestone", "nether"};
            static constexpr const common::registry::Identifier END =
                {"lodestone", "end"};
            static constexpr const common::registry::Identifier
                UNKNOWN = {"lodestone",
                           "unknown"}; // todo we can make level type registry
        };

        explicit World(const std::string &name = "New World") : m_name(name) {}

        World(std::unique_ptr<Level> overworldLevel,
              const std::string &name = "New World")
            : World(name) {
            this->addLevel(Dimension::OVERWORLD, std::move(overworldLevel));
        }

        World(const std::string &name,
              map_t<common::registry::Identifier,
                    std::unique_ptr<Level>> &&levels)
            : m_name(std::move(name)), m_levels(std::move(levels)) {}

        // TODO world constructor with abstract generator class that provides level

        const map_t<common::registry::Identifier,
                    std::unique_ptr<Level>> &
        getLevels() const;

        Level *addLevel(const common::registry::Identifier &id,
                        std::unique_ptr<Level> level);
        Level *
        getLevel(const common::registry::Identifier &id) const;
        void removeLevel(const common::registry::Identifier &id);
        bool hasLevel(const common::registry::Identifier &id) const;

        std::string toString() const override {
            return std::format("World[name={}]", this->getName());
        };

        std::string getName() const;
        void setName(const std::string &n);

        virtual Level *getDefaultLevel() const;

        const map_t<std::string, std::unique_ptr<entity::Player>> &
        getPlayers() const;
        size_t getPlayerCount() const;

        entity::Player *addPlayer(std::unique_ptr<entity::Player> player,
                                  bool resetCoords = true);
        entity::Player *getPlayer(const std::string &id) const;
        std::unique_ptr<entity::Player> removePlayer(const std::string &id);
        bool hasPlayer(const std::string &id) const;


        void movePlayerToLevel(const std::string &id,
                               const common::registry::Identifier &level,
                               const bool resetCoords = true) {
            const auto it = m_players.find(id);
            if (it == m_players.end())
                throw std::runtime_error(std::format(
                    "Attempted to move nonexistent player '{}' to level '{}'",
                    id, level));

            entity::Player &plr = *it->second;

            Level *lvl = getLevel(level);
            if (!lvl)
                throw std::runtime_error(std::format(
                    "Tried to move player '{}' to nonexistent level '{}'",
                    plr.getId(), level));

            plr.setLevel(lvl, resetCoords);
        }

        void movePlayerToWorld(const std::string &id, World *target) {
            std::unique_ptr<entity::Player> plr = removePlayer(id);
            if (!plr)
                throw std::runtime_error(std::format(
                        "Attempted to move nonexistent player '{}' to world '{}'",
                        id, target->toString()));

            target->addPlayer(std::move(plr));
        }

        /** Gets the creation time of the world, which would be the earliest level's creation time. */
        uint64_t getCreationTime();

        std::unique_ptr<properties::AbstractProperty>
        getProperty(const std::string &name) override;
    protected:
        /** World name */
        std::string m_name;

        /** Levels
         *
         * @tparam ID The level ID
         * @tparam Level The level
         */
        map_t<common::registry::Identifier, std::unique_ptr<Level>>
            m_levels;

        map_t<std::string, std::unique_ptr<entity::Player>> m_players;
    };
} // namespace lodestone::level::world

#endif // LODESTONE_WORLD_H