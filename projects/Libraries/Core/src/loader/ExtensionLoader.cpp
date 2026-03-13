/** @file ExtensionLoader.cpp
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
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