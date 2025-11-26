//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_WORLD_H
#define LODESTONE_WORLD_H
#include <unordered_map>

#include <Lodestone.Common/string/StringSerializable.h>

#include "Lodestone.Level/Level.h"
#include "Lodestone.Level/entity/Player.h"
#include "Lodestone.Level/properties/ReflectiveProperties.h"

namespace lodestone::conversion::world {
    class WorldIO;
}

namespace lodestone::level::world {
    class World : public lodestone::common::string::StringSerializable, public properties::ReflectiveProperties {
      public:
        class Dimension {
            // just a class full of constants for now
          public:
            static constexpr const lodestone::common::registry::Identifier
                OVERWORLD = {"lodestone", "overworld"};
            static constexpr const lodestone::common::registry::Identifier
                NETHER = {"lodestone", "nether"};
            static constexpr const lodestone::common::registry::Identifier END =
                {"lodestone", "end"};
            static constexpr const lodestone::common::registry::Identifier
                UNKNOWN = {"lodestone",
                           "unknown"}; // todo we can make level type registry
        };

        explicit World(const std::string &name = "New World") : mName(name) {}

        World(std::unique_ptr<Level> overworldLevel,
              const std::string &name = "New World")
            : mName(name) {
            this->addLevel(Dimension::OVERWORLD, std::move(overworldLevel));
        }

        World(const std::string &name,
              map_t<lodestone::common::registry::Identifier,
                    std::unique_ptr<Level>, IdentifierHasher,
                    IdentifierComparator> &&levels)
            : mName(std::move(name)), mLevels(std::move(levels)) {}

        const map_t<lodestone::common::registry::Identifier,
                    std::unique_ptr<Level>, IdentifierHasher,
                    IdentifierComparator> &
        getLevels() const;

        Level *addLevel(const lodestone::common::registry::Identifier &id,
                        std::unique_ptr<Level> level);
        Level *
        getLevel(const lodestone::common::registry::Identifier &id) const;
        void removeLevel(const lodestone::common::registry::Identifier &id);
        bool hasLevel(const lodestone::common::registry::Identifier &id) const;

        std::string toString() const override {
            return (common::string::OperatorStringBuilder(typeid(*this)))
                .addField("name", getName())
                ->toString();
        };

        std::string getName() const;
        void setName(const std::string &n);

        virtual const lodestone::conversion::world::WorldIO *getIO();

        virtual level::Level *getDefaultLevel() const;

        const map_t<std::string, std::unique_ptr<entity::Player>> &
        getPlayers() const;
        size_t getPlayerCount() const;

        entity::Player *addPlayer(std::unique_ptr<entity::Player> player,
                                  bool resetCoords = true);
        entity::Player *getPlayer(const std::string &id) const;
        void removePlayer(const std::string &id);
        bool hasPlayer(const std::string &id) const;

        void movePlayerToLevel(std::unique_ptr<entity::Player> player,
                               const common::registry::Identifier &level,
                               bool resetCoords = true);
        void movePlayerToLevel(const std::string &id,
                               const common::registry::Identifier &level,
                               const bool resetCoords = true) {
            const auto it = mPlayers.find(id);
            if (it == mPlayers.end())
                throw std::runtime_error(std::format(
                    "Attempted to move nonexistent player '{}' to level '{}'",
                    id, level));

            movePlayerToLevel(std::move(it->second), level, resetCoords);
        }

        void movePlayerToWorld(std::unique_ptr<entity::Player> player,
                               World *world);
        void movePlayerToWorld(const std::string &id, World *world) {
            const auto it = mPlayers.find(id);
            if (it == mPlayers.end())
                throw std::runtime_error(std::format(
                    "Attempted to move nonexistent player '{}' to world '{}'",
                    id, world->toString()));

            movePlayerToWorld(std::move(it->second), world);
        }

        std::shared_ptr<level::properties::AbstractProperty> getProperty(const std::string &name) override;

      protected:
        /** World name */
        std::string mName;

        /** Levels
         *
         * @tparam ID The level ID
         * @tparam Level The level
         */
        map_t<lodestone::common::registry::Identifier, std::unique_ptr<Level>,
              IdentifierHasher, IdentifierComparator>
            mLevels;

        map_t<std::string, std::unique_ptr<entity::Player>> mPlayers;
    };
} // namespace lodestone::level::world

#endif // LODESTONE_WORLD_H