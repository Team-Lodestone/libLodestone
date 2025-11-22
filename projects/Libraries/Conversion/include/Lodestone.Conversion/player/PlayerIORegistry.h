//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_PLAYERIOFACTORY_H
#define LODESTONE_PLAYERIOFACTORY_H
#include <string>

#include "Lodestone.Conversion/level/LevelIO.h"
#include "Lodestone.Conversion/player/PlayerIO.h"
#include "Lodestone.Conversion/world/WorldIO.h"

namespace lodestone::conversion::player {
    /** Contains registered player IO classes */
    class LODESTONE_API PlayerIORegistry {
      protected:
        PlayerIORegistry() = default;

      public:
        static PlayerIORegistry &getInstance();

        void registerPlayerIO(const lodestone::common::registry::Identifier &id,
                              std::unique_ptr<const PlayerIO> io);

        const PlayerIO *
        getPlayerIO(const lodestone::common::registry::Identifier &id) const;

      private:
        map_t<lodestone::common::registry::Identifier,
              std::unique_ptr<const PlayerIO>, IdentifierHasher,
              IdentifierComparator>
            mRegisteredPlayerIOs;
    };
} // namespace lodestone::conversion::player

#endif // LODESTONE_PLAYERIOFACTORY_H