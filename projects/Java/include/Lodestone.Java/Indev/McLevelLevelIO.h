//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_MCLEVELLEVELIO_H
#define LODESTONE_MCLEVELLEVELIO_H
#include <Lodestone.Level/Conversion/Level/LevelIO.h>
#include <nbt_tags.h>

namespace lodestone::java::indev {
    class McLevelLevelIO : public level::conversion::level::LevelIO {
    public:
        level::Level *read(uint8_t *data) const override;
        /** Creates a Level from a mclevel Map compound tag */
        level::Level * read(nbt::tag_compound *map) const;

        uint8_t * write(level::Level *l) const override;
        /** Writes a level to an NBT compound tag */
        nbt::tag_compound *write(level::Level &l) const;

        /** Writes a level to a given NBT compound tag */
        void write(level::Level &l, nbt::tag_compound &out) const;

        size_t getSize(level::Level* l) const override;
    };
}

#endif //LODESTONE_MCLEVELLEVELIO_H
