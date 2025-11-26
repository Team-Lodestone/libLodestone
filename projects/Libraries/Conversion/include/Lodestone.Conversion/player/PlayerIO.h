//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_PLAYERIO_H
#define LODESTONE_PLAYERIO_H

#include <Lodestone.Level/entity/Player.h>
#include <filesystem>

namespace lodestone::conversion::player {
    class LODESTONE_API PlayerIO {
      public:
        virtual ~PlayerIO() = default;

        /** Creates a new Player from data in the given input stream */
        virtual std::unique_ptr<lodestone::level::entity::Player>
        read(const std::filesystem::path &filename, std::istream &in,
             int version) const = 0;

        /** Writes a Player to the given output stream */
        virtual void write(lodestone::level::entity::Player *p, int version,
                           std::ostream &out) const = 0;
    };
} // namespace lodestone::conversion::player

#endif // LODESTONE_PLAYERIO_H