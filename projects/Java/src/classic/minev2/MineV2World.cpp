//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#include "classic/minev2/MineV2World.h"

#include <Lodestone.Common/Lodestone.h>

#include "Identifiers.h"
#include "classic/minev2/MineV2WorldIo.h"
#include "Lodestone.Level/conversion/world/WorldIORegistry.h"

namespace lodestone::java::classic::minev2 {
    MineV2World::MineV2World(const std::string &name, const std::string &author) : World(name), mAuthor(author), mCreationTime(getCurrentTimeMillis()) {}

    MineV2World::MineV2World(std::unique_ptr<level::Level> &&overworld, const std::string &name,
        const std::string &author) : World(std::move(overworld), name), mAuthor(author), mCreationTime(getCurrentTimeMillis()) {
    }

    MineV2World::MineV2World(gtl::flat_hash_map<level::registry::NamespacedString, std::unique_ptr<level::Level>, NamespacedStringHasher, NamespacedStringComparator> &&levels, const std::string &name,
                             const std::string &author) : World(name, std::move(levels)), mAuthor(author), mCreationTime(getCurrentTimeMillis()) {}

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

    const lodestone::level::conversion::world::WorldIO * MineV2World::getIO() {
        return level::conversion::world::WorldIORegistry::sInstance.getWorldIO(identifiers::MINEV2);
    }
}
