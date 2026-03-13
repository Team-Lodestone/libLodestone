//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/conversion/alpha/AlphaPlayerIo.h"

#include <Lodestone.Level/world/World.h>

#include <libnbt++/io/stream_reader.h>

#include "Lodestone.Minecraft.Java/alpha/AlphaPlayer.h"
#include <libnbt++/nbt_tags.h>

#include <Lodestone.Conversion/registry/Registries.h>
#include "Lodestone.Minecraft.Java/mcregion/McRegionPlayer.h"

namespace lodestone::minecraft::java::alpha::player {
    std::unique_ptr<level::entity::Player>
    AlphaNbtPlayerIO::read(const common::conversion::io::options::OptionPresets::CommonNbtFilesystemReadOptions &options) const {
        std::unique_ptr<AlphaPlayer> p =
            std::make_unique<AlphaPlayer>(options.path.stem().string());

        nbt::tag_compound &player = options.input;

        const nbt::tag_list pos = player["Pos"].as<nbt::tag_list>();
        p->position = level::types::Vec3d{static_cast<double>(pos[0]),
                                           static_cast<double>(pos[1]),
                                           static_cast<double>(pos[2])};

        const nbt::tag_list rot = player["Rotation"].as<nbt::tag_list>();
        p->rotation = level::types::Vec2f{
            static_cast<float>(rot[0]),
            static_cast<float>(rot[1]),
        };

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

    void AlphaNbtPlayerIO::write(level::entity::Player *plr,const common::conversion::io::options::OptionPresets::NbtOutputWriteOptions<const conversion::io::options::versioned::VersionedOptions> &options) const {
        const level::types::Vec3d &pos =
            plr->position;
        options.output["Pos"] = nbt::tag_list({pos.x, pos.y, pos.z});

        const level::types::Vec2f &rot = plr->rotation;
        options.output["Rotation"] = nbt::tag_list({rot.x, rot.y});

        const level::types::Vec3d &motion = plr->getMotion();
        options.output["Motion"] = nbt::tag_list({motion.x, motion.y, motion.z});

        options.output["Health"] = plr->getHealth();

        auto air = plr->getProperty("breathingTime");
        options.output["Air"] =
            air ? air->as<level::properties::TemplatedProperty<short>>()
                      ->getValue()
                : static_cast<short>(300);

        auto deathTime = plr->getProperty("deathTime");
        options.output["DeathTime"] =
            deathTime
                ? deathTime->as<level::properties::TemplatedProperty<short>>()
                      ->getValue()
                : static_cast<short>(0);

        auto fire = plr->getProperty("fireTime");
        options.output["Fire"] =
            fire ? fire->as<level::properties::TemplatedProperty<short>>()
                       ->getValue()
                 : static_cast<short>(-20);

        auto hurtTime = plr->getProperty("hurtTime");
        options.output["HurtTime"] =
            hurtTime
                ? hurtTime->as<level::properties::TemplatedProperty<short>>()
                      ->getValue()
                : static_cast<short>(0);

        auto attackTime = plr->getProperty("attackTime");
        options.output["AttackTime"] =
            attackTime
                ? attackTime
                      ->as<level::properties::TemplatedProperty<short>>()
                      ->getValue()
                : static_cast<short>(0);

        auto dimension = plr->getProperty("dimension");
        options.output["Dimension"] =
            mcregion::player::McRegionPlayer::identifierToDimensionId(
                dimension
                    ? dimension
                          ->as<level::properties::TemplatedProperty<
                              lodestone::common::registry::Identifier>>()
                          ->getValue()
                    : level::world::World::Dimension::OVERWORLD);

        auto fallDistance = plr->getProperty("fallDistance");
        options.output["FallDistance"] =
            fallDistance
                ? fallDistance
                      ->as<level::properties::TemplatedProperty<short>>()
                      ->getValue()
                : static_cast<short>(0);

        options.output["OnGround"] = plr->isOnGround();
    }

    std::unique_ptr<level::entity::Player>
    AlphaPlayerIO::read(const common::conversion::io::options::OptionPresets::CommonPlayerReadOptions &options) const {
        auto streamReader = nbt::io::stream_reader(options.input, endian::big);

        auto [key, value] = streamReader.read_compound();

        const AlphaNbtPlayerIO *io = this->getAsByRelation<const AlphaNbtPlayerIO, &identifiers::NBT_PLAYER_IO>();
        return io->read(common::conversion::io::options::OptionPresets::CommonNbtFilesystemReadOptions {
            common::conversion::io::options::OptionPresets::CommonNbtReadOptions {
                common::conversion::io::options::NbtReaderOptions {
                    *value
                },
                conversion::io::options::versioned::VersionedOptions {
                    options.version,
                }
            },
            conversion::io::options::fs::FilesystemPathOptions {
                options.path
            }
        });
    }

    void AlphaPlayerIO::write(level::entity::Player *p, const common::conversion::io::options::OptionPresets::CommonWriteOptions &options) const {
        nbt::io::stream_writer w = nbt::io::stream_writer(options.output, endian::big);

        const AlphaNbtPlayerIO *io = this->getAsByRelation<const AlphaNbtPlayerIO, &identifiers::NBT_PLAYER_IO>();
        io->writeToNbtStreamWriter(p, "", w, conversion::io::options::versioned::VersionedOptions {
            options.version
        });
    }
} // namespace lodestone::minecraft::java::alpha::player
