//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_WORLD_H
#define LODESTONE_WORLD_H
#include <unordered_map>

#include <Lodestone.Common/string/StringSerializable.h>

#include "Lodestone.Level/Level.h"
#include "Lodestone.Level/player/Player.h"

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
            this->mLevels.emplace(Dimension::OVERWORLD, std::move(overworldLevel));
        }

        World(const std::string &name,
              gtl::flat_hash_map<lodestone::common::registry::NamespacedString, std::unique_ptr<Level>,
                  NamespacedStringHasher, NamespacedStringComparator> &&levels) : mName(std::move(name)),
            mLevels(std::move(levels)) {
        }

        const gtl::flat_hash_map<lodestone::common::registry::NamespacedString, std::unique_ptr<Level>, NamespacedStringHasher, NamespacedStringComparator> &getLevels() const;

        Level *addLevel(const lodestone::common::registry::NamespacedString &id, std::unique_ptr<Level> level);
        Level *getLevel(const lodestone::common::registry::NamespacedString &id) const;
        void removeLevel(const lodestone::common::registry::NamespacedString &id);
        bool hasLevel(const lodestone::common::registry::NamespacedString &id) const;

        std::string toString() const override {
            return (new OperatorStringBuilder(typeid(*this)))
                    ->ADD_FIELD(mName)
                    ->toString();
        };

        std::string getName() const { return mName; }

        virtual const lodestone::level::conversion::world::WorldIO *getIO() = 0;

        virtual level::Level *getDefaultLevel() const;

        const gtl::flat_hash_map<std::string, std::unique_ptr<player::Player>> &getPlayers() const;
        size_t getPlayerCount() const;

        player::Player *addPlayer(std::unique_ptr<player::Player> player);
        player::Player *getPlayer(const std::string &id) const;
        void removePlayer(const std::string &id);
        bool hasPlayer(const std::string &id) const;

        void movePlayerToLevel(std::unique_ptr<player::Player> player, const common::registry::NamespacedString &level);
        void movePlayerToLevel(const std::string &id, const common::registry::NamespacedString &level) {
            const auto it = mPlayers.find(id);
            if (it == mPlayers.end()) throw std::runtime_error(std::format("Attempted to move nonexistent player '{}' to level '{}'", id, level));

            movePlayerToLevel(std::move(it->second), level);
        }

        void movePlayerToWorld(std::unique_ptr<player::Player> player, World *world);
        void movePlayerToWorld(const std::string &id, World *world) {
            const auto it = mPlayers.find(id);
            if (it == mPlayers.end()) throw std::runtime_error(std::format("Attempted to move nonexistent player '{}' to world '{}'", id, world->toString()));

            movePlayerToWorld(std::move(it->second), world);
        }


    protected:
        std::string mName;
        /** Levels
         *
         * @tparam ID The level ID
         * @tparam Level The level
         */
        gtl::flat_hash_map<lodestone::common::registry::NamespacedString, std::unique_ptr<Level>, NamespacedStringHasher
            , NamespacedStringComparator> mLevels;

        gtl::flat_hash_map<std::string, std::unique_ptr<player::Player>> mPlayers;
    };
}

#endif //LODESTONE_WORLD_H