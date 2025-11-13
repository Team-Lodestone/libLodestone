//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_MCLEVELLEVELIO_H
#define LODESTONE_MCLEVELLEVELIO_H
#include "Lodestone.Level/conversion/level/LevelIO.h"
#include <libnbt++/nbt_tags.h>

namespace lodestone::java::indev {
    class McLevelLevelIO : public level::conversion::level::LevelIO {
    public:
        std::unique_ptr<level::Level> read(uint8_t *data, int version) const override;

        /** Creates a Level from a mclevel Map compound tag */
        std::unique_ptr<level::Level> read(nbt::tag_compound *map) const;

        uint8_t *write(level::Level *l, int version) const override;

        /** Writes a level to an NBT compound tag */
        nbt::tag_compound *write(level::Level &l) const;

        /** Writes a level to a given NBT compound tag */
        void write(level::Level &l, nbt::tag_compound &out) const;

        size_t getSize(level::Level *l, int version) const override;

        void write(level::Level *l, uint8_t *out, int version) const override;
    };
}

#endif //LODESTONE_MCLEVELLEVELIO_H
