//
// Created by DexrnZacAttack on 11/14/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/conversion/mcregion/McRegionPlayerIo.h"

#include <Lodestone.Common/io/DataBuffer.h>
#include <libnbt++/io/stream_reader.h>
#include <libnbt++/tag_primitive.h>

#include "Lodestone.Minecraft.Java/mcregion/McRegionPlayer.h"
#include <libnbt++/tag_list.h>

namespace lodestone::minecraft::java::mcregion::player {
    std::unique_ptr<level::entity::Player>
    McRegionNbtPlayerIO::read(const common::conversion::io::options::OptionPresets::CommonNbtFilesystemReadOptions &options) const {
        // FOR LATER
        // I was accidentally reading from Project Poseidon player files which
        // included some UUID long uuidLeast =
        // player["UUIDLeast"].get().as<nbt::tag_long>(); long uuidMost =
        // player["UUIDMost"].get().as<nbt::tag_long>();
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

        std::unique_ptr<McRegionPlayer> p =
            std::make_unique<McRegionPlayer>(options.path.stem().string());

        const nbt::tag_list pos = options.input["Pos"].as<nbt::tag_list>();
        p->position = level::types::Vec3d{static_cast<double>(pos[0]),
                                           static_cast<double>(pos[1]),
                                           static_cast<double>(pos[2])};

        const nbt::tag_list rot = options.input["Rotation"].as<nbt::tag_list>();
        p->rotation = level::types::Vec2f{
            static_cast<float>(rot[0]),
            static_cast<float>(rot[1]),
        };

        const nbt::tag_list motion = options.input["Motion"].as<nbt::tag_list>();
        p->setMotion(level::types::Vec3d{static_cast<double>(motion[0]),
                                         static_cast<double>(motion[1]),
                                         static_cast<double>(motion[2])});

        p->setHealth(static_cast<short>(options.input["Health"]));
        p->setSleepTimer(options.input["SleepTimer"].as<nbt::tag_short>());
        p->setBreathingTime(options.input["Air"].as<nbt::tag_short>());
        p->setDeathTime(options.input["DeathTime"].as<nbt::tag_short>());
        p->setFireTime(options.input["Fire"].as<nbt::tag_short>());
        p->setHurtTime(options.input["HurtTime"].as<nbt::tag_short>());
        p->setAttackTime(options.input["AttackTime"].as<nbt::tag_short>());
        p->setDimension(McRegionPlayer::dimensionIdToIdentifier(
            options.input["Dimension"].as<nbt::tag_int>()));
        p->setSleeping(options.input["Sleeping"].as<nbt::tag_byte>());
        p->setFallDistance(options.input["FallDistance"].as<nbt::tag_float>());

        // TODO inventory

        return p;
    }

    void McRegionNbtPlayerIO::write(level::entity::Player *c,
       const common::conversion::io::options::OptionPresets::NbtOutputWriteOptions<
        const conversion::io::options::EmptyOptions> &options) const {
    }

    std::unique_ptr<lodestone::level::entity::Player>
    McRegionPlayerIO::read(const common::conversion::io::options::OptionPresets::CommonPlayerReadOptions &options) const {
        nbt::io::stream_reader streamReader(options.input, endian::big);
        auto root = streamReader.read_compound();

        const McRegionNbtPlayerIO *io = this->getAsByRelation<const McRegionNbtPlayerIO, &identifiers::NBT_PLAYER_IO>();
        return io->read(common::conversion::io::options::OptionPresets::CommonNbtFilesystemReadOptions {
            common::conversion::io::options::OptionPresets::CommonNbtReadOptions {
                common::conversion::io::options::NbtReaderOptions {
                    *root.second
                },
                conversion::io::options::versioned::VersionedOptions {
                    options.version
                }
            },
            conversion::io::options::fs::FilesystemPathOptions {
                options.path
            }
        });
    }

    void McRegionPlayerIO::write(lodestone::level::entity::Player *p,
        const lodestone::minecraft::common::conversion::io::options::
        OptionPresets::CommonWriteOptions &options) const {
    }

} // namespace lodestone::minecraft::java::mcregion::player
