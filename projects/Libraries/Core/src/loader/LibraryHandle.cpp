/** @file LibraryHandle.cpp
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#include "Lodestone.Core/loader/LibraryHandle.h"

#include <cstddef>

namespace lodestone::core::loader {
  void* LibraryHandle::getFunction(const char* name) {
    if (!this->valid())
      return nullptr;

#ifdef _WIN32
    return GetProcAddress(this->m_handle, name);
#elif defined(__unix__)
    return dlsym(this->m_handle, name);
#endif
  }

  LibraryHandle::LibraryHandle(const std::filesystem::path& path) : LibraryHandle() {
    this->load(path);
  }

  LibraryHandle::LibraryHandle() : m_handle(NULL) {
  }

  void LibraryHandle::load(const std::filesystem::path& path) {
#ifdef _WIN32
    this->m_handle = LoadLibraryW(path.c_str());
#elif defined(__unix__)
    this->m_handle = dlopen(path.c_str(), RTLD_NOW);
#endif
  }

  void LibraryHandle::unload() {
#ifdef _WIN32
    FreeLibrary(this->m_handle);
#elif defined(__unix__)
    dlclose(this->m_handle);
#endif

    this->m_handle = NULL;
  }

  bool LibraryHandle::valid() const {
    return this->m_handle != NULL;
  }
}