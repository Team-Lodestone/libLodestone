//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_LEVELIO_H
#define LODESTONE_LEVELIO_H

#include "Lodestone.Level/Level.h"

#include "Lodestone.Conversion/world/options/AbstractWorldReadOptions.h"
#include "Lodestone.Conversion/world/options/AbstractWorldWriteOptions.h"

namespace lodestone::conversion::level {
    class LODESTONE_API LevelIO {
      public:
        virtual ~LevelIO() = default;

        /** Creates a new Level from data in the given input stream */
        virtual std::unique_ptr<lodestone::level::Level>
        read(std::istream &in, int version) const = 0;

        /** Writes a Level to the given output stream */
        virtual void write(lodestone::level::Level *l, int version,
                           std::ostream &out) const = 0;
    };
} // namespace lodestone::conversion::level

#endif // LODESTONE_LEVELIO_H