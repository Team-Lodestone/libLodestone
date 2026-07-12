//
// Created by zero on 7/12/26.
//

#ifndef LODESTONE_STATIC_EXTENSION_LOADER_H
#define LODESTONE_STATIC_EXTENSION_LOADER_H
#include "Lodestone.Core/loader/ExtensionLoader.h"

namespace lodestone::core::loader {
    class StaticExtensionLoader : public ExtensionLoader {
    public:
        explicit StaticExtensionLoader(core::Lodestone *core)
            : ExtensionLoader(core) {
        }

        void load() override {}

        void loadExtension(core::LodestoneExtension *ext);
    };
}

#endif //LODESTONE_STATIC_EXTENSION_LOADER_H