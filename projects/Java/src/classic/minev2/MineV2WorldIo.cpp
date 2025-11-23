//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#include "Lodestone.Java/classic/minev2/MineV2WorldIo.h"

#include "Lodestone.Java/Identifiers.h"
#include "Lodestone.Java/Version.h"
#include "Lodestone.Java/classic/minev2/MineV2LevelIO.h"
#include "Lodestone.Java/classic/minev2/MineV2World.h"
#include <BinaryIO/BinaryBuffer.h>
#include <Lodestone.Conversion/level/LevelIORegistry.h>

#include <BinaryIO/stream/BinaryInputStream.h>
#include <BinaryIO/stream/BinaryOutputStream.h>

#include "Lodestone.Java/classic/minev2/MineV2LevelIO.h"
#include "Lodestone.Java/classic/minev2/options/MineV2WorldWriteOptions.h"

namespace lodestone::java::classic::minev2 {
    size_t MineV2WorldIO::getSize(level::world::World *w,
                                  const int version) const {
        size_t s = sizeof(uint32_t) // signature
                   + sizeof(char) + sizeof(uint16_t) + w->getName().length() +
                   sizeof(uint16_t);

        if (MineV2World *mv2 = dynamic_cast<MineV2World *>(w))
            s += mv2->getAuthor().length();
        else
            s += strlen("Player");

        s += sizeof(uint64_t);

        const MineV2LevelIO *lio =
            dynamic_cast<const MineV2LevelIO *>(getLevelIO(version));
        s += lio->getSize(w->getDefaultLevel(), version);

        return s;
    }

    const lodestone::conversion::level::PlayerIO *
    MineV2WorldIO::getLevelIO(int version) const {
        return lodestone::conversion::level::LevelIoRegistry::getInstance()
            .getLevelIO(identifiers::MINEV2);
    }

    std::unique_ptr<lodestone::level::world::World> MineV2WorldIO::read(
        std::istream &in, int version,
        const conversion::world::options::AbstractWorldReadOptions &options)
        const {
        bio::stream::BinaryInputStream bis(in);

        const uint32_t sig = bis.readBE<uint32_t>();
        if (sig != SIGNATURE) {
            throw std::runtime_error(
                "Signature does not match expected 0x271BB788");
        }

        char ver = bis.readSignedByte();
        const std::string name = bis.readString(bis.readBE<uint16_t>());
        const std::string author = bis.readString(bis.readBE<uint16_t>());
        uint64_t creationTime = bis.readBE<uint64_t>(); // todo use

        const MineV2LevelIO *lio =
            dynamic_cast<const MineV2LevelIO *>(getLevelIO(version));

        std::unique_ptr<level::Level> unique =
            lio->read(bis.getStream(), version); // todo: proper version!!!!

        return std::make_unique<MineV2World>(std::move(unique), name, author);
    }

    void MineV2WorldIO::write(
        lodestone::level::world::World *w, int version, std::ostream &out,
        const conversion::world::options::AbstractWorldWriteOptions &options)
        const {
        const options::MineV2WorldWriteOptions *writeOptions = dynamic_cast<
            const java::classic::minev2::options::MineV2WorldWriteOptions *>(
            &options);

        options::MineV2WorldWriteOptions def{};
        if (!writeOptions)
            writeOptions = &def;

        bio::stream::BinaryOutputStream bos(out);

        bos.writeBE<uint32_t>(SIGNATURE);
        bos.writeByte(1);

        bos.writeBE<uint16_t>(w->getName().length());
        bos.writeString(w->getName(), false);

        if (MineV2World *mv2 = dynamic_cast<MineV2World *>(w)) {
            bos.writeBE<uint16_t>(mv2->getAuthor().length());
            bos.writeString(mv2->getAuthor(), false);

            bos.writeBE<uint64_t>(mv2->getCreationTime());
        } else {
            bos.writeBE<uint16_t>(strlen("Player"));
            bos.writeString("Player", false);

            bos.writeBE<uint64_t>(common::getCurrentTimeMillis());
        }

        const MineV2LevelIO *lio =
            dynamic_cast<const MineV2LevelIO *>(getLevelIO(version));
        lio->write(w->getLevel(writeOptions->level), version, bos.getStream());
        // todo: VERSION STUFF
    }
} // namespace lodestone::java::classic::minev2
