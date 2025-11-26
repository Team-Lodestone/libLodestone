//
// Created by DexrnZacAttack on 11/7/25 using zPc-i2.
//
#ifndef LODESTONE_FILEWORLDIO_H
#define LODESTONE_FILEWORLDIO_H
#include "Lodestone.Conversion/world/WorldIO.h"
#include "Lodestone.Conversion/world/options/AbstractWorldReadOptions.h"
#include "Lodestone.Conversion/world/options/AbstractWorldWriteOptions.h"

namespace lodestone::conversion::world {
    class LODESTONE_API FileWorldIO : public WorldIO {
      public:
        /** Creates a new World from data in the given input stream */
        virtual std::unique_ptr<lodestone::level::world::World>
        read(std::istream &in, int version,
             const options::AbstractWorldReadOptions &options) const = 0;

        /** Writes a World to the given output stream */
        virtual void
        write(lodestone::level::world::World *w, int version, std::ostream &out,
              const options::AbstractWorldWriteOptions &options) const = 0;
    };
} // namespace lodestone::conversion::world

#endif // LODESTONE_FILEWORLDIO_H