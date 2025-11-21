//
// Created by DexrnZacAttack on 11/19/25 using zPc-i2.
//
#ifndef LODESTONE_LOGGING_H
#define LODESTONE_LOGGING_H


#ifdef CMAKE_BUILD_DEBUG
/** Only gets the filename instead of full file path */
#define FILE_NAME (__FILE__ + std::string(__FILE__).find_last_of("\\/") + 1)

#define LOG_INFO(...)                                                          \
    std::cout << "[" << FILE_NAME << ":" << __LINE__ << " | " << __func__ << "/INFO] " << __VA_ARGS__ << std::endl

#define LOG_INFO_WIDE(...)                                                     \
    std::wcout << L"[" << FILE_NAME << L":" << __LINE__ << L" | " << __func__ << L"/INFO] " << __VA_ARGS__ << std::endl

#define LOG_WARNING(...)                                                       \
    std::cout << "[" << FILE_NAME << ":" << __LINE__ << " | " << __func__ << "/WARN] " << __VA_ARGS__ << std::endl

#define LOG_WARNING_WIDE(...)                                                  \
    std::cout << L"[" << FILE_NAME << L":" << __LINE__ << L" | " << __func__ << L"/WARN] " << __VA_ARGS__ << std::endl

#define LOG_ERROR(...)                                                         \
    std::cerr << "[" << FILE_NAME << ":" << __LINE__ << " | " << __func__ << "/ERROR] " << __VA_ARGS__ << std::cerr

#define LOG_ERROR_WIDE(...)                                                     \
    std::cerr << L"[" << FILE_NAME << L":" << __LINE__ << L" | " << __func__ << L"/ERROR] " << __VA_ARGS__ << std::cerr

#define LOG_DEBUG(...)                                                          \
    std::cout << "[" << FILE_NAME << ":" << __LINE__ << " | " << __func__ << "/DEBUG] " << __VA_ARGS__ << std::endl

#define LOG_DEBUG_WIDE(...)                                                         \
    std::wcout << L"[" << FILE_NAME << L":" << __LINE__ << L" | " << __func__ << L"/DEBUG] " << __VA_ARGS__ << std::endl

#else

#define LOG_INFO(...)                                                          \
    std::cout << "[" << __func__ << "/INFO] " << __VA_ARGS__ << std::endl

#define LOG_INFO_WIDE(...)                                                     \
    std::wcout << L"[" << __func__ << L"/INFO] " << __VA_ARGS__ << std::endl

#define LOG_WARNING(...)                                                       \
    std::cout << "[" << __func__ << "/WARN] " << __VA_ARGS__ << std::endl

#define LOG_WARNING_WIDE(...)                                                  \
    std::cout << L"[" << __func__ << L"/WARN] " << __VA_ARGS__ << std::endl

#define LOG_ERROR(...)                                                         \
    std::cerr << "[" << __func__ << "/ERROR] " << __VA_ARGS__ << std::cerr

#define LOG_ERROR_WIDE(...)                                                     \
    std::cerr << L"[" << __func__ << L"/ERROR] " << __VA_ARGS__ << std::cerr

#define LOG_DEBUG(...)
#define LOG_DEBUG_WIDE(...)
#endif

#endif //LODESTONE_LOGGING_H