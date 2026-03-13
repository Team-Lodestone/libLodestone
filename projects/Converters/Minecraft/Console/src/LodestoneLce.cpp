/** @file LodestoneLce.cpp
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#include "Lodestone.Minecraft.Console/LodestoneLce.h"

namespace lodestone::minecraft::console {
    LodestoneLCE::LodestoneLCE() {
    }

    LodestoneLCE * LodestoneLCE::getInstance() {
        static LodestoneLCE s_instance;
        return &s_instance;
    }

    lodestone::common::registry::Identifier LodestoneLCE::
    getIdentifier() const {
        return IDENTIFIER;
    }

    lodestone::common::util::Semver LodestoneLCE::getVersion() const {
        return VERSION;
    }

    core::LodestoneExtension * lodestoneInit() {
        return LodestoneLCE::getInstance();
    }
}