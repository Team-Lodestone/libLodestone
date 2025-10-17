//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_MINEV2WORLD_H
#define LODESTONE_MINEV2WORLD_H
#include <Lodestone.Level/World/World.h>

namespace lodestone::java::classic::minev2 {
    class MineV2World : public level::world::World {
    public:
        MineV2World(const std::string &name = "New World", const std::string &author = "Player");
        MineV2World(const std::unordered_map<std::string, level::Level*> &levels, const std::string &name = "New World", const std::string &author = "Player");

        // TODO: figure out single dimension support
        // probably via just a derived class
        const std::string &getAuthor() const;
        std::string &getAuthor();
        void setAuthor(const std::string &author);

        uint64_t getCreationTime() const;
        void setCreationTime(const uint64_t time);
    protected:
        std::string mAuthor;
        std::uint64_t mCreationTime;
    };
}

#endif //LODESTONE_MINEV2WORLD_H
