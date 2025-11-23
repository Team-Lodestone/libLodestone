//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/alpha/player/AlphaPlayerIo.h"

#include <Lodestone.Common/io/DataBuffer.h>
#include <libnbt++/io/stream_reader.h>
#include <libnbt++/tag_primitive.h>

#include "Lodestone.Minecraft.Java/alpha/player/AlphaPlayer.h"
#include <libnbt++/tag_list.h>

#include "Lodestone.Minecraft.Java/mcr/player/McRegionPlayer.h"

namespace lodestone::minecraft::java::alpha::player {
    std::unique_ptr<level::entity::Player>
    AlphaPlayerIO::read(const std::filesystem::path &filename,
                        nbt::tag_compound &player, const int version) const {
        std::unique_ptr<AlphaPlayer> p =
            std::make_unique<AlphaPlayer>(filename.stem().string());

        const nbt::tag_list pos = player["Pos"].as<nbt::tag_list>();
        p->setPosition(level::types::Vec3d{static_cast<double>(pos[0]),
                                           static_cast<double>(pos[1]),
                                           static_cast<double>(pos[2])});

        const nbt::tag_list rot = player["Rotation"].as<nbt::tag_list>();
        p->setRotation(level::types::Vec2f{
            static_cast<float>(rot[0]),
            static_cast<float>(rot[1]),
        });

        const nbt::tag_list motion = player["Motion"].as<nbt::tag_list>();
        p->setMotion(level::types::Vec3d{static_cast<double>(motion[0]),
                                         static_cast<double>(motion[1]),
                                         static_cast<double>(motion[2])});

        p->setHealth(static_cast<short>(player["Health"]));
        p->setBreathingTime(player["Air"]);
        p->setDeathTime(player["DeathTime"]);
        p->setFireTime(player["Fire"]);
        p->setHurtTime(player["HurtTime"]);
        p->setAttackTime(player["AttackTime"]);
        p->setDimension(mcr::player::McRegionPlayer::dimensionIdToIdentifier(
            player["Dimension"]));
        p->setFallDistance(player["FallDistance"]);

        // TODO inventory

        return p;
    }

    nbt::tag_compound AlphaPlayerIO::write(level::entity::Player &c) const {}

    size_t AlphaPlayerIO::getSize(level::entity::Player *c, int version) const {
    }

    std::unique_ptr<lodestone::level::entity::Player>
    AlphaPlayerIO::read(const std::filesystem::path &filename, std::istream &in,
                        int version) const {
        nbt::io::stream_reader streamReader =
            nbt::io::stream_reader(in, endian::big);

        auto root = streamReader.read_compound();
        return read(filename, *root.second, version);
    }

    void AlphaPlayerIO::write(lodestone::level::entity::Player *p, int version,
                              std::ostream &out) const {}

} // namespace lodestone::minecraft::java::alpha::player
