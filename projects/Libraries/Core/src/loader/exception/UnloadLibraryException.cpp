/** @file UnloadLibraryException.cpp
 *
 * @author DexrnZacAttack
 * @date 3/20/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.Core/loader/exception/UnloadLibraryException.h"
#include <format>

namespace lodestone::core::loader::exception {
    UnloadLibraryException::UnloadLibraryException(const std::filesystem::path &libraryPath, const std::error_code &errorCode) : LibraryException(std::format("Failed to unload library '{}'", libraryPath.generic_string()), libraryPath, errorCode) {}
    UnloadLibraryException::UnloadLibraryException(const std::filesystem::path &libraryPath, const std::error_code &errorCode, const std::string &info) : LibraryException(std::format("Failed to unload library '{}': {}", libraryPath.generic_string(), info), libraryPath, errorCode) {}
}