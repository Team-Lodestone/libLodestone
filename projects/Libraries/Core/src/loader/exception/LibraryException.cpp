/** @file LibraryException.cpp
 *
 * @author DexrnZacAttack
 * @date 3/20/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.Core/loader/exception/LibraryException.h"

namespace lodestone::core::loader::exception {
    LibraryException::LibraryException(const std::string &message,
        const std::filesystem::path &libraryPath,
        const std::error_code &errorCode) : system_error(errorCode, message), m_libraryPath(libraryPath) {
    }
}