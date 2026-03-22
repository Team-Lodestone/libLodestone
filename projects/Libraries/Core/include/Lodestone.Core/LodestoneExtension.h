//
// Created by DexrnZacAttack on 11/19/25 using zPc-i2.
//
#ifndef LODESTONE_LODESTONEEXTENSION_H
#define LODESTONE_LODESTONEEXTENSION_H
#include <Lodestone.Common/util/Semver.h>

#include <Lodestone.Common/registry/Identifier.h>
#include "Lodestone.Core/internal/Exports.h"

namespace lodestone::core {
    class LODESTONE_CORE_API LodestoneExtension {
      public:
        virtual ~LodestoneExtension() = default;

        // CHANGING VTABLE ORDER MAY BREAK OLDER LIBRARY BUILDS.
        virtual constexpr common::registry::Identifier getIdentifier() const = 0;
        virtual constexpr common::util::Semver getVersion() const = 0;
    };
} // namespace lodestone::core

#endif // LODESTONE_LODESTONEEXTENSION_H
