/** @file NativeExtensionLoader.h
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_NATIVEPLUGINLOADER_H
#define LODESTONE_NATIVEPLUGINLOADER_H
#include "Lodestone.Core/loader/ExtensionLoader.h"

namespace lodestone::core::loader {
  class NativeExtensionLoader : public ExtensionLoader {
  public:
    explicit NativeExtensionLoader(core::Lodestone *core)
      : ExtensionLoader(core) {
    }

    void load() override;
  };
}

#endif // LODESTONE_NATIVEPLUGINLOADER_H