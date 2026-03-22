/** @file LoadLibraryException.h
 *
 * @author DexrnZacAttack
 * @date 3/20/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_LOADLIBRARYEXCEPTION_H
#define LODESTONE_LOADLIBRARYEXCEPTION_H
#include "Lodestone.Core/loader/exception/LibraryException.h"

#include <filesystem>


namespace lodestone::core::loader::exception {
    class LODESTONE_CORE_API LoadLibraryException : public LibraryException {
    public:
        explicit LoadLibraryException(const std::filesystem::path &libraryPath, const std::error_code &errorCode = std::make_error_code(std::errc::invalid_argument));
        LoadLibraryException(const std::filesystem::path &libraryPath, const std::error_code &errorCode, const std::string &info);
    };
}

#endif // LODESTONE_LOADLIBRARYEXCEPTION_H