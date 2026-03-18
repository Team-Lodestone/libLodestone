/** @file NativeExtensionLoader.cpp
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#include "Lodestone.Core/loader/NativeExtensionLoader.h"

#include <filesystem>
#include <iostream>
#include <print>

#include "Lodestone.Core/loader/LibraryHandle.h"

namespace lodestone::core::loader {
  void NativeExtensionLoader::load() {
    const std::filesystem::path extensionsFolder = std::filesystem::current_path() / "extensions";

    if (!std::filesystem::exists(extensionsFolder)) {
        if (std::error_code ec; !std::filesystem::create_directories(extensionsFolder, ec)) {
            throw std::filesystem::filesystem_error("Couldn't create extensions folder", extensionsFolder, ec);
        }
    }

    if (std::error_code ec; !std::filesystem::is_directory(extensionsFolder, ec))
      throw std::filesystem::filesystem_error("Extensions folder path is not a directory", extensionsFolder, ec);

    for (const auto &p : std::filesystem::directory_iterator(extensionsFolder)) {
      if (!std::filesystem::is_regular_file(p))
        continue;

      // TODO we might want to require a specific extension for this to make sure we're not trying to load random files as libraries
      LibraryHandle h = LibraryHandle(p);
      if (!h.valid()) {
        std::cerr << "Failed to load library '" << p.path() << "'" << "\n";
        continue;
      }

      const LodestoneInit init = h.getFunction<LodestoneInit>(ENTRYPOINT);
      if (init == nullptr) {
        std::cerr << "Library '" << p.path() << "' does not contain entrypoint '" << ENTRYPOINT << "'" << "\n";
        continue;
      }

      common::event::Cancellable c;
      this->extensionLoadingEvent.notify(c, p.path());
      if (c.cancelled)
        return;

      this->loadExtension(init);
    }
  }
}