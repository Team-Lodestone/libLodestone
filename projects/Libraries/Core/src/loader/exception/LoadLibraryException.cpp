/** @file LoadLibraryException.cpp
 *
 * @author DexrnZacAttack
 * @date 3/20/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.Core/loader/exception/LoadLibraryException.h"
#include <format>

namespace lodestone::core::loader::exception {
    LoadLibraryException::LoadLibraryException(const std::filesystem::path &libraryPath, const std::error_code &errorCode) : LibraryException(std::format("Failed to load library '{}'", libraryPath.generic_string()), libraryPath, errorCode) {}
    LoadLibraryException::LoadLibraryException(const std::filesystem::path &libraryPath, const std::error_code &errorCode, const std::string &info) : LibraryException(std::format("Failed to load library '{}': {}", libraryPath.generic_string(), info), libraryPath, errorCode) {}
}