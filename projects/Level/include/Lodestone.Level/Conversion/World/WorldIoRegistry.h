//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_WORLDIOREGISTRY_H
#define LODESTONE_WORLDIOREGISTRY_H
#include "Lodestone.Level/Conversion/World/WorldIo.h"

namespace lodestone {
    namespace level {
        namespace conversion::world {
            /** Creates worlds based on registered world IO classes */
            class LODESTONE_API WorldIoRegistry {
            protected:
                WorldIoRegistry() = default;
            public:
                static WorldIoRegistry *sInstance;

                void registerWorldIO(const std::string &id, const WorldIo* io);

                const WorldIo *getWorldIO(const std::string &id) const;
            private:
                std::unordered_map<std::string, const WorldIo*> mRegisteredWorldIOs = {};
            };
        }
    } // level
} // lodestone

#endif //LODESTONE_WORLDIOREGISTRY_H