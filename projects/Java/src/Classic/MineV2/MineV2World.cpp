//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#include "Classic/MineV2/MineV2World.h"

#include <Lodestone.Common/Lodestone.h>

namespace lodestone::java::classic::minev2 {
    MineV2World::MineV2World(const std::string &name, const std::string &author) : World(name), mAuthor(author), mCreationTime(getCurrentTimeMillis()) {}
    MineV2World::MineV2World(const std::unordered_map<std::string, level::Level *> &levels, const std::string &name,
                             const std::string &author) : World(levels, name), mAuthor(author), mCreationTime(getCurrentTimeMillis()) {}

    const std::string & MineV2World::getAuthor() const {
        return mAuthor;
    }

    std::string & MineV2World::getAuthor() {
        return mAuthor;
    }

    void MineV2World::setAuthor(const std::string &author) {
        this->mAuthor = author;
    }

    uint64_t MineV2World::getCreationTime() const {
        return mCreationTime;
    }

    void MineV2World::setCreationTime(const uint64_t time) {
        this->mCreationTime = time;
    }
}
