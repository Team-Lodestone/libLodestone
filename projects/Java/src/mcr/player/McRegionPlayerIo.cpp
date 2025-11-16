//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#include "Lodestone.Java/mcr/player/McRegionPlayerIo.h"

#include <libnbt++/tag_primitive.h>
#include <libnbt++/io/stream_reader.h>
#include <Lodestone.Common/io/DataBuffer.h>

#include <libnbt++/tag_list.h>
#include "Lodestone.Java/mcr/player/McRegionPlayer.h"

namespace lodestone::java::mcr::player {
    std::unique_ptr<level::entity::Player> McRegionPlayerIO::read(const std::filesystem::path &filename, uint8_t *data, const size_t size, const int version) const {
        std::istream buf(new common::io::DataBuffer(data, size));
        nbt::io::stream_reader streamReader = nbt::io::stream_reader(buf, endian::big);

        auto root = streamReader.read_compound();
        return read(filename, *root.second, version);
    }

    std::unique_ptr<level::entity::Player> McRegionPlayerIO::read(const std::filesystem::path &filename, nbt::tag_compound &player, const int version) const {
        // FOR LATER
        // I was accidentally reading from Project Poseidon player files which included some UUID
        // long uuidLeast = player["UUIDLeast"].get().as<nbt::tag_long>();
        // long uuidMost = player["UUIDMost"].get().as<nbt::tag_long>();
        //
        // std::uint8_t u[16] = {
        //     static_cast<uint8_t>((uuidMost >> 56) & 0xFF),
        //     static_cast<uint8_t>((uuidMost >> 48) & 0xFF),
        //     static_cast<uint8_t>((uuidMost >> 40) & 0xFF),
        //     static_cast<uint8_t>((uuidMost >> 32) & 0xFF),
        //     static_cast<uint8_t>((uuidMost >> 24) & 0xFF),
        //     static_cast<uint8_t>((uuidMost >> 16) & 0xFF),
        //     static_cast<uint8_t>((uuidMost >> 8) & 0xFF),
        //     static_cast<uint8_t>(uuidMost & 0xFF),
        //
        //     static_cast<uint8_t>((uuidLeast >> 56) & 0xFF),
        //     static_cast<uint8_t>((uuidLeast >> 48) & 0xFF),
        //     static_cast<uint8_t>((uuidLeast >> 40) & 0xFF),
        //     static_cast<uint8_t>((uuidLeast >> 32) & 0xFF),
        //     static_cast<uint8_t>((uuidLeast >> 24) & 0xFF),
        //     static_cast<uint8_t>((uuidLeast >> 16) & 0xFF),
        //     static_cast<uint8_t>((uuidLeast >> 8) & 0xFF),
        //     static_cast<uint8_t>(uuidLeast & 0xFF)
        // };
        // uuids::uuid uuid(u);

        std::unique_ptr<McRegionPlayer> p = std::make_unique<McRegionPlayer>(filename.stem().string());

        const nbt::tag_list pos = player["Pos"].as<nbt::tag_list>();
        p->setPosition(level::types::Vec3d {
            static_cast<double>(pos[0]),
            static_cast<double>(pos[1]),
            static_cast<double>(pos[2])
        });

        const nbt::tag_list rot = player["Rotation"].as<nbt::tag_list>();
        p->setRotation(level::types::Vec2f {
            static_cast<float>(rot[0]),
            static_cast<float>(rot[1]),
        });

        const nbt::tag_list motion = player["Motion"].as<nbt::tag_list>();
        p->setMotion(level::types::Vec3d {
            static_cast<double>(motion[0]),
            static_cast<double>(motion[1]),
            static_cast<double>(motion[2])
        });

        p->setHealth(static_cast<short>(player["Health"]));
        p->setSleepTimer(player["SleepTimer"]);
        p->setBreathingTime(player["Air"]);
        p->setDeathTime(player["DeathTime"]);
        p->setFireTime(player["Fire"]);
        p->setHurtTime(player["HurtTime"]);
        p->setAttackTime(player["AttackTime"]);
        p->setDimension(McRegionPlayer::dimensionIdToIdentifier(player["Dimension"]));
        p->setSleeping(static_cast<int8_t>(player["Sleeping"]));
        p->setFallDistance(player["FallDistance"]);

        // TODO inventory

        return p;
    }

    uint8_t * McRegionPlayerIO::write(level::entity::Player *c, int version) const {
    }

    nbt::tag_compound McRegionPlayerIO::write(level::entity::Player &c) const {
    }

    size_t McRegionPlayerIO::getSize(level::entity::Player *c, int version) const {
    }

    void McRegionPlayerIO::write(lodestone::level::entity::Player *p, uint8_t *out, int version) const {
    }
}
