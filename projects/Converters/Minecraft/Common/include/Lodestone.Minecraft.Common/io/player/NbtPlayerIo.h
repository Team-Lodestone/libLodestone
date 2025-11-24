//
// Created by DexrnZacAttack on 11/24/25 using zPc-i2.
//
#ifndef LODESTONE_NBTPLAYERIO_H
#define LODESTONE_NBTPLAYERIO_H
#include <Lodestone.Conversion/player/PlayerIO.h>

namespace nbt {
    class tag_compound;
}

namespace lodestone::minecraft::common::io::player {
    class NbtPlayerIO : public conversion::player::PlayerIO {
        virtual std::unique_ptr<level::entity::Player>
        read(const std::filesystem::path &filename, nbt::tag_compound &player,
             int version) const = 0;

        virtual nbt::tag_compound write(level::entity::Player *c,
                                        int version) const = 0;
    };
} // namespace lodestone::minecraft::common::io::player

#endif // LODESTONE_NBTPLAYERIO_H
