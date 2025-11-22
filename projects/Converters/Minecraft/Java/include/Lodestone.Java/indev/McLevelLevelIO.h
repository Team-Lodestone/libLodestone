//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_MCLEVELLEVELIO_H
#define LODESTONE_MCLEVELLEVELIO_H
#include <Lodestone.Conversion/level/LevelIO.h>
#include <libnbt++/nbt_tags.h>

namespace lodestone::java::indev {
    class McLevelLevelIO : public lodestone::conversion::level::PlayerIO {
      public:
        /** Creates a Level from a mclevel Map compound tag */
        std::unique_ptr<level::Level> read(nbt::tag_compound *map) const;

        /** Writes a level to an NBT compound tag */
        nbt::tag_compound *write(level::Level &l) const;

        /** Writes a level to a given NBT compound tag */
        void write(level::Level &l, nbt::tag_compound &out) const;

        size_t getSize(level::Level *l, int version) const override;

        std::unique_ptr<lodestone::level::Level>
        read(std::istream &in, int version) const override;

        void write(lodestone::level::Level *l, int version,
                   std::ostream &out) const override;
    };
} // namespace lodestone::java::indev

#endif // LODESTONE_MCLEVELLEVELIO_H
