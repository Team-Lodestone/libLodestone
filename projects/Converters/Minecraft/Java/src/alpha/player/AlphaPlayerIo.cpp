//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/alpha/player/AlphaPlayerIo.h"

#include <libnbt++/io/stream_reader.h>

#include "Lodestone.Minecraft.Java/alpha/player/AlphaPlayer.h"
#include <libnbt++/nbt_tags.h>

#include "Lodestone.Minecraft.Java/mcregion/player/McRegionPlayer.h"

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

        p->setHealth(player["Health"].as<nbt::tag_short>());
        p->setBreathingTime(player["Air"].as<nbt::tag_short>());
        p->setDeathTime(player["DeathTime"].as<nbt::tag_short>());
        p->setFireTime(player["Fire"].as<nbt::tag_short>());
        p->setHurtTime(player["HurtTime"].as<nbt::tag_short>());
        p->setAttackTime(player["AttackTime"].as<nbt::tag_short>());
        p->setDimension(
            mcregion::player::McRegionPlayer::dimensionIdToIdentifier(
                player["Dimension"].as<nbt::tag_int>()));
        p->setFallDistance(player["FallDistance"].as<nbt::tag_int>());

        // TODO inventory

        return p;
    }

    nbt::tag_compound AlphaPlayerIO::write(level::entity::Player *p,
                                           const int version) const {
        nbt::tag_compound out;

        const level::types::Vec3d &pos =
            p->getPosition().value_or(level::types::Vec3d{0.0, 0.0, 0.0});
        out["Pos"] = nbt::tag_list({pos.x, pos.y, pos.z});

        const level::types::Vec2f &rot = p->getRotation();
        out["Rotation"] = nbt::tag_list({rot.x, rot.z});

        const level::types::Vec3d &motion = p->getMotion();
        out["Motion"] = nbt::tag_list({motion.x, motion.y, motion.z});

        out["Health"] = p->getHealth();

        auto air = p->getProperty("breathingTime");
        out["Air"] =
            air ? air->as<level::properties::TemplatedProperty<short &>>()
                      ->getValue()
                : static_cast<short>(300);

        auto deathTime = p->getProperty("deathTime");
        out["DeathTime"] =
            deathTime
                ? deathTime->as<level::properties::TemplatedProperty<short &>>()
                      ->getValue()
                : static_cast<short>(0);

        auto fire = p->getProperty("fireTime");
        out["Fire"] =
            fire ? fire->as<level::properties::TemplatedProperty<short &>>()
                       ->getValue()
                 : static_cast<short>(-20);

        auto hurtTime = p->getProperty("hurtTime");
        out["HurtTime"] =
            hurtTime
                ? hurtTime->as<level::properties::TemplatedProperty<short &>>()
                      ->getValue()
                : static_cast<short>(0);

        auto attackTime = p->getProperty("attackTime");
        out["AttackTime"] =
            attackTime
                ? attackTime
                      ->as<level::properties::TemplatedProperty<short &>>()
                      ->getValue()
                : static_cast<short>(0);

        auto dimension = p->getProperty("dimension");
        out["Dimension"] =
            mcregion::player::McRegionPlayer::identifierToDimensionId(
                dimension
                    ? dimension
                          ->as<level::properties::TemplatedProperty<
                              lodestone::common::registry::Identifier &>>()
                          ->getValue()
                    : level::world::World::Dimension::OVERWORLD);

        auto fallDistance = p->getProperty("fallDistance");
        out["FallDistance"] =
            fallDistance
                ? fallDistance
                      ->as<level::properties::TemplatedProperty<short &>>()
                      ->getValue()
                : static_cast<short>(0);

        out["OnGround"] = p->isOnGround();

        return out;
    }

    std::unique_ptr<level::entity::Player>
    AlphaPlayerIO::read(const std::filesystem::path &filename, std::istream &in,
                        const int version) const {
        auto streamReader = nbt::io::stream_reader(in, endian::big);

        auto root = streamReader.read_compound();
        return read(filename, *root.second, version);
    }

    void AlphaPlayerIO::write(level::entity::Player *p, const int version,
                              std::ostream &out) const {
        nbt::io::stream_writer w = nbt::io::stream_writer(out, endian::big);

        w.write_tag("", write(p, version));
    }

} // namespace lodestone::minecraft::java::alpha::player
