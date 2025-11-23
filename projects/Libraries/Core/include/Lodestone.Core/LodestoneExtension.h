//
// Created by DexrnZacAttack on 11/19/25 using zPc-i2.
//
#ifndef LODESTONE_LODESTONEEXTENSION_H
#define LODESTONE_LODESTONEEXTENSION_H
#include <Lodestone.Common/registry/Identifier.h>

namespace lodestone::core {
    class LodestoneExtension {
      public:
        virtual ~LodestoneExtension() = default;

        // CHANGING VTABLE ORDER MAY BREAK OLDER LIBRARY BUILDS.
        virtual common::registry::Identifier getIdentifier() = 0;
        virtual std::string getVersion() = 0;
    };
} // namespace lodestone::core

#endif // LODESTONE_LODESTONEEXTENSION_H
