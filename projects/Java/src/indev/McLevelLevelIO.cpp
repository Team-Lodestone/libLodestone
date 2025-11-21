//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#include "Lodestone.Java/indev/McLevelLevelIO.h"

namespace lodestone::java::indev {
    std::unique_ptr<level::Level>
    McLevelLevelIO::read(nbt::tag_compound *map) const {}

    nbt::tag_compound *McLevelLevelIO::write(level::Level &l) const {}

    void McLevelLevelIO::write(level::Level &l, nbt::tag_compound &out) const {}

    size_t McLevelLevelIO::getSize(level::Level *l, int version) const {}

    std::unique_ptr<lodestone::level::Level>
    McLevelLevelIO::read(std::istream &in, int version) const {}

    void McLevelLevelIO::write(lodestone::level::Level *l, int version,
                               std::ostream &out) const {}

} // namespace lodestone::java::indev