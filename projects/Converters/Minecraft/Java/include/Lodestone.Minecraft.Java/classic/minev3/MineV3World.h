/** @file MineV3World.h
*
* @author Zero_DSRS_VX
* @date 3/23/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#ifndef LODESTONE_MINEV3WORLD_H
#define LODESTONE_MINEV3WORLD_H

#include <Lodestone.Level/world/World.h>

namespace lodestone::minecraft::java::classic::minev3 {
    class MineV3World : public level::world::World {
    public:
        MineV3World(const std::string &name = "New World",
                    const std::string &author = "Player");

        MineV3World(std::unique_ptr<level::Level> &&overworld,
                    const std::string &name = "New World",
                    const std::string &author = "Player");

        MineV3World(map_t<lodestone::common::registry::Identifier,
                          std::unique_ptr<level::Level>> &&levels,
                    const std::string &name, const std::string &author);

        const std::string &getAuthor() const;

        std::string &getAuthor();

        void setAuthor(const std::string &author);

    protected:
        std::string m_author;
    };
} // namespace lodestone::minecraft::java::classic::minev3


#endif //LODESTONE_MINEV3WORLD_H