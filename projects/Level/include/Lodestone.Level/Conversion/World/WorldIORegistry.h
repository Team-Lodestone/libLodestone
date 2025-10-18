//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//
#ifndef LODESTONE_WORLDIOREGISTRY_H
#define LODESTONE_WORLDIOREGISTRY_H
#include "Lodestone.Level/Conversion/World/WorldIO.h"

namespace lodestone {
    namespace level {
        namespace conversion::world {
            /** Creates worlds based on registered world IO classes */
            class LODESTONE_API WorldIORegistry {
            protected:
                WorldIORegistry() = default;
            public:
                static WorldIORegistry sInstance;

                void registerWorldIO(const std::string &id, std::unique_ptr<const WorldIO> io);

                const WorldIO *getWorldIO(const std::string &id) const;
            private:
                std::unordered_map<std::string, std::unique_ptr<const WorldIO>> mRegisteredWorldIOs = {};
            };
        }
    } // level
} // lodestone

#endif //LODESTONE_WORLDIOREGISTRY_H