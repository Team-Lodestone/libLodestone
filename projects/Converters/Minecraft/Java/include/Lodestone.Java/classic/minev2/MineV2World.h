//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_MINEV2WORLD_H
#define LODESTONE_MINEV2WORLD_H
#include <Lodestone.Level/world/World.h>

#include <Lodestone.Conversion/world/WorldIO.h>

namespace lodestone::java::classic::minev2 {
    class MineV2World : public level::world::World {
      public:
        MineV2World(const std::string &name = "New World",
                    const std::string &author = "Player");

        MineV2World(std::unique_ptr<level::Level> &&overworld,
                    const std::string &name = "New World",
                    const std::string &author = "Player");

        MineV2World(map_t<lodestone::common::registry::Identifier,
                          std::unique_ptr<level::Level>, IdentifierHasher,
                          IdentifierComparator> &&levels,
                    const std::string &name, const std::string &author);

        const std::string &getAuthor() const;

        std::string &getAuthor();

        void setAuthor(const std::string &author);

        uint64_t getCreationTime() const;

        void setCreationTime(const uint64_t time);

        const lodestone::conversion::world::WorldIO *getIO() override;

      protected:
        std::string mAuthor;
        std::uint64_t mCreationTime;
    };
} // namespace lodestone::java::classic::minev2

#endif // LODESTONE_MINEV2WORLD_H