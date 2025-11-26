//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_ALPHAPLAYERIO_H
#define LODESTONE_ALPHAPLAYERIO_H
#include <Lodestone.Minecraft.Common/io/player/NbtPlayerIo.h>

#include <Lodestone.Conversion/player/PlayerIO.h>
#include <libnbt++/tag_compound.h>

#include <Lodestone.Level/world/World.h>

namespace lodestone::minecraft::java::alpha::player {
    class AlphaPlayerIO : public common::io::player::NbtPlayerIO {
      public:
        std::unique_ptr<level::entity::Player>
        read(const std::filesystem::path &filename, nbt::tag_compound &player,
             int version) const override;

        nbt::tag_compound write(level::entity::Player *p,
                                int version) const override;

        std::unique_ptr<lodestone::level::entity::Player>
        read(const std::filesystem::path &filename, std::istream &in,
             int version) const override;

        void write(lodestone::level::entity::Player *p, int version,
                   std::ostream &out) const override;
    };
} // namespace lodestone::minecraft::java::alpha::player

#endif // LODESTONE_ALPHAPLAYERIO_H
