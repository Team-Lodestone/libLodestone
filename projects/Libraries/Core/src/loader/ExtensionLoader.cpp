/** @file ExtensionLoader.cpp
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#include "Lodestone.Core/loader/ExtensionLoader.h"

namespace lodestone::core::loader {
    ExtensionLoader::ExtensionLoader(core::Lodestone* core) : m_core(core) {
    }

    void ExtensionLoader::loadExtension(const LodestoneInit entrypoint) {
        core::LodestoneExtension *ext = entrypoint();

        this->extensionLoadedEvent.notify(ext);
        this->m_core->registerExtension(ext);
    }
}