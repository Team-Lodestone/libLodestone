//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_MCREGIONPLAYERIO_H
#define LODESTONE_MCREGIONPLAYERIO_H
#include <libnbt++/tag_compound.h>
#include <Lodestone.Conversion/player/PlayerIO.h>

#include <Lodestone.Level/world/World.h>

namespace lodestone::java::mcr::player {
    class McRegionPlayerIO : public lodestone::conversion::player::PlayerIO {
    public:
        std::unique_ptr<level::entity::Player> read(const std::filesystem::path &filename, uint8_t *data, size_t size, int version) const override;

        std::unique_ptr<level::entity::Player> read(const std::filesystem::path &filename, nbt::tag_compound &player, int version) const;

        uint8_t *write(level::entity::Player *c, int version) const override;

        nbt::tag_compound write(level::entity::Player &c) const;

        size_t getSize(level::entity::Player *c, int version) const override;

        void write(lodestone::level::entity::Player *p, uint8_t *out, int version) const override;
    };
}

#endif //LODESTONE_MCREGIONPLAYERIO_H
