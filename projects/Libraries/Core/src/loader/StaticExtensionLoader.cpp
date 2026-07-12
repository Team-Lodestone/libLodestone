//
// Created by zero on 7/12/26.
//

#include "Lodestone.Core/loader/StaticExtensionLoader.h"

void lodestone::core::loader::StaticExtensionLoader::loadExtension(core::LodestoneExtension *ext) {
    this->extensionLoadedEvent.notify(ext);
    this->m_core->registerExtension(ext);
}