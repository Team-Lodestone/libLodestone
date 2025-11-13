//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#include "Lodestone.Java/indev/McLevelLevelIO.h"

namespace lodestone::java::indev {
    std::unique_ptr<level::Level> McLevelLevelIO::read(uint8_t *data, int version) const {
    }

    std::unique_ptr<level::Level> McLevelLevelIO::read(nbt::tag_compound *map) const {
    }

    uint8_t *McLevelLevelIO::write(level::Level *l, int version) const {
    }

    nbt::tag_compound *McLevelLevelIO::write(level::Level &l) const {
    }

    void McLevelLevelIO::write(level::Level &l, nbt::tag_compound &out) const {
    }

    size_t McLevelLevelIO::getSize(level::Level *l, int version) const {
    }

    void McLevelLevelIO::write(level::Level *l, uint8_t *out, int version) const {
    }
}