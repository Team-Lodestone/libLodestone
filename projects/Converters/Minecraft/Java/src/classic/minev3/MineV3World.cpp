/** @file MineV3World.cpp
*
* @author Zero_DSRS_VX
* @date 3/23/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/

#include "Lodestone.Minecraft.Java/classic/minev3/MineV3World.h"

#include "Lodestone.Minecraft.Java/classic/minev2/MineV2World.h"

#include <Lodestone.Common/util/Util.h>

#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/conversion/classic/minev3/MineV3WorldIo.h"

namespace lodestone::minecraft::java::classic::minev3 {
    MineV3World::MineV3World(const std::string &name, const std::string &author)
        : World(name), m_author(author) {}

    MineV3World::MineV3World(std::unique_ptr<level::Level> &&overworld,
                             const std::string &name, const std::string &author)
        : World(std::move(overworld), name), m_author(author) {}

    MineV3World::MineV3World(
        map_t<lodestone::common::registry::Identifier,
              std::unique_ptr<level::Level>> &&levels,
        const std::string &name, const std::string &author)
        : World(name, std::move(levels)), m_author(author) {}

    const std::string &MineV3World::getAuthor() const { return m_author; }

    std::string &MineV3World::getAuthor() { return m_author; }

    void MineV3World::setAuthor(const std::string &author) {
        this->m_author = author;
    }
} // namespace lodestone::minecraft::java::classic::minev3