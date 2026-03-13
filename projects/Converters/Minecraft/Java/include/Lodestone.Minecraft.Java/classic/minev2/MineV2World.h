//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_MINEV2WORLD_H
#define LODESTONE_MINEV2WORLD_H
#include <Lodestone.Level/world/World.h>

namespace lodestone::minecraft::java::classic::minev2 {
    class MineV2World : public level::world::World {
      public:
        MineV2World(const std::string &name = "New World",
                    const std::string &author = "Player");

        MineV2World(std::unique_ptr<level::Level> &&overworld,
                    const std::string &name = "New World",
                    const std::string &author = "Player");

        MineV2World(map_t<lodestone::common::registry::Identifier,
                          std::unique_ptr<level::Level>> &&levels,
                    const std::string &name, const std::string &author);

        const std::string &getAuthor() const;

        std::string &getAuthor();

        void setAuthor(const std::string &author);

      protected:
        std::string m_author;
    };
} // namespace lodestone::minecraft::java::classic::minev2

#endif // LODESTONE_MINEV2WORLD_H