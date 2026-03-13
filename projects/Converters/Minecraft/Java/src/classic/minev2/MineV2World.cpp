//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/classic/minev2/MineV2World.h"

#include <Lodestone.Common/util/Util.h>

#include <Lodestone.Common/LodestoneCommon.h>

#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/conversion/classic/minev2/MineV2WorldIo.h"
namespace lodestone::minecraft::java::classic::minev2 {
    MineV2World::MineV2World(const std::string &name, const std::string &author)
        : World(name), m_author(author) {}

    MineV2World::MineV2World(std::unique_ptr<level::Level> &&overworld,
                             const std::string &name, const std::string &author)
        : World(std::move(overworld), name), m_author(author) {}

    MineV2World::MineV2World(
        map_t<lodestone::common::registry::Identifier,
              std::unique_ptr<level::Level>> &&levels,
        const std::string &name, const std::string &author)
        : World(name, std::move(levels)), m_author(author) {}

    const std::string &MineV2World::getAuthor() const { return m_author; }

    std::string &MineV2World::getAuthor() { return m_author; }

    void MineV2World::setAuthor(const std::string &author) {
        this->m_author = author;
    }
} // namespace lodestone::minecraft::java::classic::minev2