//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#include "Lodestone.Java/classic/minev2/MineV2WorldIo.h"

#include "Lodestone.Java/Identifiers.h"
#include "Lodestone.Java/Version.h"
#include <BinaryIO/BinaryIO.h>
#include "Lodestone.Java/classic/minev2/MineV2LevelIO.h"
#include "Lodestone.Java/classic/minev2/MineV2World.h"
#include <Lodestone.Conversion/level/LevelIORegistry.h>

namespace lodestone::java::classic::minev2 {
    std::unique_ptr<level::world::World> MineV2WorldIO::read(uint8_t *data, const int version) const {
        bio::BinaryIO io(data);

        const uint32_t sig = io.readBE<uint32_t>();
        if (sig != SIGNATURE) {
            throw std::runtime_error("Signature does not match expected 0x271BB788");
        }

        char ver = io.readSignedByte();
        const std::string name = io.readString(io.readBE<uint16_t>());
        const std::string author = io.readString(io.readBE<uint16_t>());
        uint64_t creationTime = io.readBE<uint64_t>(); // todo use

        const MineV2LevelIO *lio = dynamic_cast<const MineV2LevelIO *>(getLevelIO(version));

        std::unique_ptr<level::Level> unique = lio->read(io.getDataRelative(), version); // todo: proper version!!!!
        return std::make_unique<MineV2World>(std::move(unique), name, author);
    }

    uint8_t *MineV2WorldIO::write(level::world::World *w, const int version) const {
        bio::BinaryIO io(new uint8_t[getSize(w, version)]{});

        io.writeBE<uint32_t>(SIGNATURE);
        io.writeByte(1);

        io.writeBE<uint16_t>(w->getName().length());
        io.writeString(w->getName());

        if (MineV2World *mv2 = dynamic_cast<MineV2World *>(w)) {
            io.writeBE<uint16_t>(mv2->getAuthor().length());
            io.writeString(mv2->getAuthor());

            io.writeBE<uint64_t>(mv2->getCreationTime());
        } else {
            io.writeBE<uint16_t>(strlen("Player"));
            io.writeString("Player");

            io.writeBE<uint64_t>(common::getCurrentTimeMillis());
        }

        const MineV2LevelIO *lio = dynamic_cast<const MineV2LevelIO *>(getLevelIO(version));
        lio->write(w->getDefaultLevel(), io.getDataRelative(), version);
        // todo: VERSION STUFF

        return io.getData();
    }

    size_t MineV2WorldIO::getSize(level::world::World *w, int version) const {
        size_t s = sizeof(uint32_t) // signature
                   + sizeof(char)
                   + sizeof(uint16_t)
                   + w->getName().length()
                   + sizeof(uint16_t);

        if (MineV2World *mv2 = dynamic_cast<MineV2World *>(w))
            s += mv2->getAuthor().length();
        else
            s += strlen("Player");

        s += sizeof(uint64_t);

        const MineV2LevelIO *lio = dynamic_cast<const MineV2LevelIO *>(getLevelIO(version));
        s += lio->getSize(w->getDefaultLevel(), version);

        return s;
    }

    const lodestone::conversion::level::LevelIO *MineV2WorldIO::getLevelIO(int version) const {
        return lodestone::conversion::level::LevelIORegistry::sInstance.getLevelIO(identifiers::MINEV2);
    }
}