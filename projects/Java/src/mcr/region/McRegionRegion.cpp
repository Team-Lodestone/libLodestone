//
// Created by DexrnZacAttack on 11/11/25 using zPc-i2.
//
#include "Lodestone.Java/mcr/region/McRegionRegion.h"

namespace lodestone::java::mcr::region {
    std::string McRegionRegion::getFilename() const {
        return std::format("r.{}.{}.mcr", this->mCoords.x, this->mCoords.z);
    }

    level::types::Vec2i McRegionRegion::getCoordsFromFilename(const std::string &name) {
        std::stringstream ss(name);
        std::string p;
        constexpr char d = '.';

        level::types::Vec2i coords{0,0};

        std::getline(ss, p, d);

        std::getline(ss, p, d);
        coords.x = std::stoi(p);

        std::getline(ss, p, d);
        coords.z = std::stoi(p);

        return coords;
    }
}
