/** @file LibraryException.h
 *
 * @author DexrnZacAttack
 * @date 3/20/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_LIBRARYEXCEPTION_H
#define LODESTONE_LIBRARYEXCEPTION_H
#include <filesystem>

#include "Lodestone.Core/internal/Exports.h"

namespace lodestone::core::loader::exception {
    class LODESTONE_CORE_API LibraryException : public std::system_error {
    public:
        LibraryException(const std::string &message, const std::filesystem::path &libraryPath, const std::error_code &errorCode);

        const std::filesystem::path &path() const noexcept {
            return this->m_libraryPath;
        }

    private:
        const std::filesystem::path m_libraryPath;
    };
}

#endif // LODESTONE_LIBRARYEXCEPTION_H