/** @file UnloadLibraryException.h
 *
 * @author DexrnZacAttack
 * @date 3/20/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_UNLOADLIBRARYEXCEPTION_H
#define LODESTONE_UNLOADLIBRARYEXCEPTION_H
#include "Lodestone.Core/loader/exception/LibraryException.h"

namespace lodestone::core::loader::exception {
    class UnloadLibraryException : public LibraryException {
        explicit UnloadLibraryException(const std::filesystem::path &libraryPath, const std::error_code &errorCode = std::make_error_code(std::errc::invalid_argument));
        UnloadLibraryException(const std::filesystem::path &libraryPath, const std::error_code &errorCode, const std::string &info);
    };
}

#endif // LODESTONE_UNLOADLIBRARYEXCEPTION_H