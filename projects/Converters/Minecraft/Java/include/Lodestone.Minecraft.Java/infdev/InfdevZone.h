/** @file InfdevZone.h
*
* @author Zero_DSRS_VX
* @date 3/29/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/
#ifndef LODESTONE_INFDEVZONE_H
#define LODESTONE_INFDEVZONE_H
#include "Lodestone.Level/region/Region.h"
#include "Lodestone.Level/types/Vec2.h"

namespace lodestone::minecraft::java::infdev::zone {
    class InfdevZone : public level::Level {
    public:
        explicit InfdevZone(const level::types::Vec2i &coords) : m_coords(coords) {}

        std::string getFilename() const;
        static level::types::Vec2i
        getCoordsFromFilename(const std::string &name);
    private:
        const level::types::Vec2i m_coords;
    };
}

#endif //LODESTONE_INFDEVZONE_H
