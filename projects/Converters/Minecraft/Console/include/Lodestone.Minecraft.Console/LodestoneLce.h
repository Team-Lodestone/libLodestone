/** @file LodestoneLce.h
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#ifndef LODESTONE_LODESTONELCE_H
#define LODESTONE_LODESTONELCE_H
#include <Lodestone.Common/registry/Identifiable.h>
#include <Lodestone.Common/registry/Identifier.h>
#include <Lodestone.Core/LodestoneExtension.h>
#include <Lodestone.Common/Defines.h>
#include <Lodestone.Common/util/Semver.h>

namespace lodestone::minecraft::console {
    inline static constexpr lodestone::common::registry::Identifier IDENTIFIER = {"lodestone", "minecraft/legacy_console"};

    class LODESTONE_API LodestoneLCE : public core::LodestoneExtension, public common::registry::Identifiable<&IDENTIFIER> {
    private:
        LodestoneLCE();
    public:
        static constexpr common::util::Semver VERSION = {
            LODESTONE_MINECRAFT_CONSOLE_MAJOR_VERSION,
            LODESTONE_MINECRAFT_CONSOLE_MINOR_VERSION,
            LODESTONE_MINECRAFT_CONSOLE_PATCH_VERSION,
            LODESTONE_MINECRAFT_CONSOLE_DEV_VERSION
        };

        static LodestoneLCE *getInstance();

        lodestone::common::registry::Identifier getIdentifier() const override;
        lodestone::common::util::Semver getVersion() const override;
    };

    extern "C" {
        core::LodestoneExtension *lodestoneInit();
    }
}

#endif // LODESTONE_LODESTONELCE_H