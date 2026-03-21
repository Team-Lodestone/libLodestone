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

#include "Lodestone.Core/loader/exception/LoadLibraryException.h"
#include "Lodestone.Core/loader/exception/UnloadLibraryException.h"

#include <cstddef>

namespace lodestone::core::loader {
    LibraryHandle::function_t LibraryHandle::getFunction(const char *name) {
        if (!this->valid())
            return NULL_FUNCTION;

#ifdef _WIN32
        return GetProcAddress(this->m_handle, name);
#elif defined(__unix__) || defined (__APPLE__)
        return dlsym(this->m_handle, name);
#endif
    }

    LibraryHandle::LibraryHandle(const std::filesystem::path &path) : m_path(path), m_handle(NULL_HANDLE) {}

    void LibraryHandle::load() {
        if (this->valid())
            throw std::runtime_error("The library is already loaded!");

#ifdef _WIN32
        SetLastError(0);

        this->m_handle = LoadLibraryW(this->m_path.c_str());

        if (GetLastError() != 0) {
            this->m_handle = NULL_HANDLE;

            throw exception::LoadLibraryException(this->m_path, std::error_code(GetLastError(), std::system_category()));
        }
#elif defined(__unix__) || defined (__APPLE__)
        this->m_handle = dlopen(this->m_path.c_str(), RTLD_NOW);
        if (!this->m_handle) {
            const char *err = dlerror();
            if (!err) {
                err = "dlopen failed!";
            }

            throw exception::LoadLibraryException(
                this->m_path, std::make_error_code(std::errc::invalid_argument), err);
        }
#endif
    }

    void LibraryHandle::unload() {
        if (!this->valid())
            return; //already assumed to be either not loaded or already unloaded

#ifdef _WIN32
        SetLastError(0);

        if (!FreeLibrary(this->m_handle)) {
            if (GetLastError() != 0) {
                throw exception::UnloadLibraryException(this->m_path, std::error_code(GetLastError(), std::system_category()));
            } else {
                throw exception::UnloadLibraryException(this->m_path, std::make_error_code(std::errc::invalid_argument), "FreeLibrary failed!");
            }
        }
#elif defined(__unix__) || defined (__APPLE__)
        if (dlclose(this->m_handle)) {
            const char *err = dlerror();
            if (!err) {
                err = "dlclose failed!";
            }

            throw exception::UnloadLibraryException(this->m_path, std::make_error_code(std::errc::invalid_argument), err);
        }
#endif

        // TODO should this always be invalidated even on failure?
        this->m_handle = NULL_HANDLE;
    }

    bool LibraryHandle::valid() const noexcept {
        return this->m_handle != NULL_HANDLE;
    }
}