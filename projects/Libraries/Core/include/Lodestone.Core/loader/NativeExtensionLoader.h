/** @file NativeExtensionLoader.h
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#ifndef LODESTONE_NATIVEPLUGINLOADER_H
#define LODESTONE_NATIVEPLUGINLOADER_H
#include "Lodestone.Core/loader/ExtensionLoader.h"
#include "Lodestone.Core/internal/Exports.h"

namespace lodestone::core::loader {
  class LODESTONE_CORE_API NativeExtensionLoader : public ExtensionLoader {
  public:
    explicit NativeExtensionLoader(const std::filesystem::path &extensionsDirectory, core::Lodestone *core)
      : ExtensionLoader(core), m_extensionsDirectory(extensionsDirectory) {
    }

    void load() override;

  private:
      std::filesystem::path m_extensionsDirectory;
  };
}

#endif // LODESTONE_NATIVEPLUGINLOADER_H