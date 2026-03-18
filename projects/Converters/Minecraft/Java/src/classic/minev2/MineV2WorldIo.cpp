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
        const std::string name = bis.readStringWithLength<char>(bio::util::ByteOrder::BIG, bio::util::string::StringLengthEncoding::LENGTH_PREFIX);
        const std::string author = bis.readStringWithLength<char>(bio::util::ByteOrder::BIG, bio::util::string::StringLengthEncoding::LENGTH_PREFIX);
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

        bos.writeString<char>(w->getName(), bio::util::ByteOrder::BIG, bio::util::string::StringLengthEncoding::LENGTH_PREFIX);

        if (MineV2World *mv2 = dynamic_cast<MineV2World *>(w)) {
            bos.writeString<char>(mv2->getAuthor(), bio::util::ByteOrder::BIG, bio::util::string::StringLengthEncoding::LENGTH_PREFIX);
        } else {
            bos.writeString<char>("Player", bio::util::ByteOrder::BIG, bio::util::string::StringLengthEncoding::LENGTH_PREFIX);
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
