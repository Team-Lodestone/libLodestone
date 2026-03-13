//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#include "Lodestone.Minecraft.Java/conversion/classic/minev2/MineV2WorldIo.h"

#include <Lodestone.Common/util/Util.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"
#include "Lodestone.Minecraft.Java/Version.h"
#include "Lodestone.Minecraft.Java/conversion/classic/minev2/MineV2LevelIO.h"
#include "Lodestone.Minecraft.Java/classic/minev2/MineV2World.h"
#include <BinaryIO/buffer/BinaryBuffer.h>

#include <BinaryIO/stream/BinaryInputStream.h>
#include <BinaryIO/stream/BinaryOutputStream.h>

namespace lodestone::minecraft::java::classic::minev2 {
    std::unique_ptr<lodestone::level::world::World> MineV2WorldIO::read(const common::conversion::io::options::OptionPresets::CommonReadOptions &options) const {
        bio::stream::BinaryInputStream bis(options.input);

        const uint32_t sig = bis.readBE<uint32_t>();
        if (sig != SIGNATURE) {
            throw std::runtime_error(
                "Signature does not match expected 0x271BB788");
        }

        char ver = bis.readSignedByte();
        const std::string name = bis.readString(bis.readBE<uint16_t>());
        const std::string author = bis.readString(bis.readBE<uint16_t>());
        uint64_t creationTime = bis.readBE<uint64_t>(); // todo use

        const MineV2LevelIO *lio = this->getAsByRelation<const MineV2LevelIO, &lodestone::conversion::identifiers::LEVEL_IO>();

        std::unique_ptr<level::Level> unique =
            lio->read( common::conversion::io::options::OptionPresets::CommonReadOptions {
            conversion::io::options::fs::file::FileReaderOptions {
                bis.getStream()
            },
            conversion::io::options::versioned::VersionedOptions {
                options.version
            }
        }); // todo: proper version!!!!

        return std::make_unique<MineV2World>(std::move(unique), name, author);
    }

    void MineV2WorldIO::write(level::world::World *w, const MineV2WriteOptions &options)
        const {
        bio::stream::BinaryOutputStream bos(options.output);

        bos.writeBE<uint32_t>(SIGNATURE);
        bos.writeByte(1);

        bos.writeBE<uint16_t>(w->getName().length());
        bos.writeString(w->getName(), false);

        if (MineV2World *mv2 = dynamic_cast<MineV2World *>(w)) {
            bos.writeBE<uint16_t>(mv2->getAuthor().length());
            bos.writeString(mv2->getAuthor(), false);
        } else {
            bos.writeBE<uint16_t>(strlen("Player"));
            bos.writeString("Player", false);
        }

        bos.writeBE<uint64_t>(w->getCreationTime());

        const MineV2LevelIO *lio = this->getAsByRelation<const MineV2LevelIO, &lodestone::conversion::identifiers::LEVEL_IO>();
        lio->write(w->getLevel(options.level), common::conversion::io::options::OptionPresets::CommonWriteOptions {
            conversion::io::options::fs::file::FileWriterOptions {
                bos.getStream()
            },
            conversion::io::options::versioned::VersionedOptions {
                options.version
            }
        });         // todo: VERSION STUFF
    }
} // namespace lodestone::minecraft::java::classic::minev2
