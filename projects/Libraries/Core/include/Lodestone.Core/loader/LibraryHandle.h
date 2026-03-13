/** @file LibraryHandle.h
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_LIBRARYHANDLE_H
#define LODESTONE_LIBRARYHANDLE_H
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#elif defined(__unix__)
#include <dlfcn.h>
#endif

namespace lodestone::core::loader {
  class LibraryHandle {
  public:
    explicit LibraryHandle(const std::filesystem::path& path);
    LibraryHandle();

    void load(const std::filesystem::path& path);
    void unload();

    bool valid() const;

    template <typename F>
    F getFunction(const char *name) {
      return reinterpret_cast<F>(this->getFunction(name));
    }

    void *getFunction(const char *name);

  private:
#ifdef _WIN32
    HMODULE m_handle;
#elif defined(__unix__)
    void *m_handle;
#endif
    // TODO for emscripten and other platforms we will impl custom, internal loader which initializes libs added at compile time
  };
}

#endif // LODESTONE_LIBRARYHANDLE_H