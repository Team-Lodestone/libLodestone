//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_PLAYERIO_H
#define LODESTONE_PLAYERIO_H

#include <filesystem>
#include <Lodestone.Level/entity/Player.h>

namespace lodestone::conversion::player {
    class LODESTONE_API PlayerIO {
    public:
        virtual ~PlayerIO() = default;

        /** Reads data into a new Player */
        virtual std::unique_ptr<lodestone::level::entity::Player> read(const std::filesystem::path &filename, std::istream &in, int version) const = 0;

        /** Writes a Player to data */
        virtual void write(lodestone::level::entity::Player *p, int version, std::ostream &out) const = 0;

        /** Gets the size of the Player in bytes */
        virtual size_t getSize(lodestone::level::entity::Player *p, int version) const = 0;
    };
}

#endif //LODESTONE_PLAYERIO_H