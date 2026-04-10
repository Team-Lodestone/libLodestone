/** @file InfdevZone.cpp
*
* @author Zero_DSRS_VX
* @date 3/29/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#include "Lodestone.Minecraft.Java/infdev/InfdevZone.h"

#include <string>
#include <sstream>

#include <Lodestone.Level/types/Vec2.h>

namespace lodestone::minecraft::java::infdev::zone {
    std::string InfdevZone::getFilename() const {
        auto zoneX36 = lodestone::common::util::Math::encodeBase36(this->m_coords.x);
        auto zoneZ36 = lodestone::common::util::Math::encodeBase36(this->m_coords.y);

        return std::format("zone_{}_{}.dat", zoneX36, zoneZ36);
    }

    level::types::Vec2i
    InfdevZone::getCoordsFromFilename(const std::string &name) {
        std::stringstream ss(name);
        std::string p;
        constexpr char d = '_';

        level::types::Vec2i coords{0, 0};

        std::getline(ss, p, d);

        std::getline(ss, p, d);
        coords.x = lodestone::common::util::Math::decodeBase36(p);

        std::getline(ss, p, d);
        coords.y = lodestone::common::util::Math::decodeBase36(std::string_view(p.data(), p.find(".dat")));

        return coords;
    }
}
