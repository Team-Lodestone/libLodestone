/** @file LibraryLoader.h
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_LIBRARYLOADER_H
#define LODESTONE_LIBRARYLOADER_H
#include <filesystem>

#include "Lodestone.Core/event/Event.h"
#include "Lodestone.Core/Lodestone.h"
#include "Lodestone.Core/LodestoneExtension.h"

namespace lodestone::core::loader {
    class ExtensionLoader {
    public:
      using LodestoneInit = lodestone::core::LodestoneExtension *(*)(void);
      static constexpr const char *ENTRYPOINT = "lodestoneInit";

      virtual ~ExtensionLoader() = default;

      explicit ExtensionLoader(core::Lodestone *core);

      virtual void load() = 0;
      virtual void loadExtension(LodestoneInit entrypoint);

    public:
      event::CancellableEvent<const std::filesystem::path &> extensionLoadingEvent;
      event::Event<core::LodestoneExtension *> extensionLoadedEvent;

    protected:
      core::Lodestone *m_core;
    };
}

#endif // LODESTONE_LIBRARYLOADER_H