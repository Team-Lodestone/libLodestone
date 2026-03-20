/** @file LibraryHandle.h
 *
 * @author DexrnZacAttack
 * @date 3/12/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#ifndef LODESTONE_LIBRARYHANDLE_H
#define LODESTONE_LIBRARYHANDLE_H
#include <filesystem>
#include <optional>

#ifdef _WIN32
#include <windows.h>
#elif defined(__unix__) || defined (__APPLE__)
#include <dlfcn.h>
#endif

namespace lodestone::core::loader {
    /** Holds an OS library handle, and provides utility functions for interacting with that handle.
     *
     * @note You must call @ref LibraryHandle::load() in order to load the library.
     *
     * Usage:
     * @code
     * LibraryHandle myLibrary(path);
     *
     * try {
     *     myLibrary.load();
     * } catch (LoadLibraryException &ex) { // Gets thrown if the library fails to load, the handle is considered NOT valid after this point.
     *     std::cerr << ex.what() << std::endl;
     * }
     *
     * if (myLibrary.valid()) {
     *     // Lets get and call a function
     *     using Init = int (*)(void);
     *
     *     const Init func = myLibrary.getFunction<Init>("init"); // assumes you've externed a function with this name
     *     int res = func();
     *
     *     std::cout << res << std::endl; // Prints the result
     *
     *     // When you're done with the library, you can unload it if wanted
     *     try {
     *         myLibrary.unload();
     *     } catch (UnloadLibraryException &ex) { // Gets thrown if the library fails to unload. Whether the handle is still valid is platform dependent.
     *         std::cerr << ex.what() << std::endl;
     *     }
     * }
     * @endcode
     */
    class LibraryHandle {
    public:
#ifdef _WIN32
        using handle_t = HMODULE;
        using function_t = FARPROC;

        static constexpr const handle_t NULL_HANDLE = NULL;
        static constexpr const function_t NULL_FUNCTION = nullptr;
#elif defined(__unix__) || defined (__APPLE__)
        using handle_t = void *;
        using function_t = void *;

        static constexpr const handle_t NULL_HANDLE = nullptr;
        static constexpr const function_t NULL_FUNCTION = nullptr;
#endif

        /** Creates a new LibraryHandle
         *
         * @note You must call @ref LibraryHandle::load() in order to load the library.
         */
        explicit LibraryHandle(const std::filesystem::path &path);

        /** Loads a library at the stored path
         *
         * @throws lodestone::core::loader::exception::LoadLibraryException If the library failed to load
         */
        void load();

        /** Unloads the library
         *
         * @throws lodestone::core::loader::exception::UnloadLibraryException If the library failed to unload
         */
        void unload();

        /** Returns true if the library handle is valid */
        bool valid() const noexcept;

        /** Returns the address of an exported function by name, casts to the given function type */
        template <typename Func>
        requires std::is_function_v<std::remove_pointer_t<std::remove_reference_t<Func>>>
        Func getFunction(const char *name) {
            return reinterpret_cast<Func>(this->getFunction(name));
        }

        /** Returns the address of an exported function by name, nullptr if it doesn't exist. */
        function_t getFunction(const char *name);

    private:
        std::filesystem::path m_path; /**< The path of the library file */

        handle_t m_handle; /**< The library handle */
        // TODO for emscripten and other platforms we will impl custom, internal loader which initializes libs added at compile time
    };
}

#endif // LODESTONE_LIBRARYHANDLE_H