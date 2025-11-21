//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_UTIL_H
#define LODESTONE_UTIL_H
#include <chrono>
#include <filesystem>
#include <iostream>

#include <Lodestone.Common/Logging.h>

namespace lodestone::tests::util {
    template <class... Args>
    constexpr void runTest(void (*test)(Args...), const char *const type,
                           const std::string &name, Args... args) {
        LOG_INFO("Running test \"" << type << "::" << name << "\"");

        auto startTime = std::chrono::high_resolution_clock::now();

#if ALLOW_THROW != true
        try {
#endif
            // reset clock since inside try block
            startTime = std::chrono::high_resolution_clock::now();

            test(args...);

            const std::chrono::duration<double, std::milli> duration =
                std::chrono::high_resolution_clock::now() - startTime;

            std::cout << "[" << type << "] \"" << name << "\" finished after "
                      << duration.count() << "ms" << std::endl;
#if ALLOW_THROW != true
        } catch (const std::exception &e) {
            const std::chrono::duration<double, std::milli> duration =
                std::chrono::high_resolution_clock::now() - startTime;

            std::cerr << "[" << type << "] \"" << name << "\" failed after "
                      << duration.count() << "ms" << " due to " << e.what()
                      << std::endl;
        }
#endif
    }

#define _OPEN_FILE_STREAM(path, out, name)                                     \
    std::ifstream name(util::INPUT_FOLDER / path, std::ifstream::binary);      \
                                                                               \
    if (!name.is_open())                                                       \
        throw std::ios_base::failure(std::string("Failed to open file ") +     \
                                     (util::INPUT_FOLDER / path).string());

#define _OPEN_FILE(path, out, name)                                            \
    _OPEN_FILE_STREAM(path, out, name)                                         \
                                                                               \
    std::vector<uint8_t> out(                                                  \
        std::filesystem::file_size(util::INPUT_FOLDER / path));                \
    name.read(reinterpret_cast<char *>(out.data()), out.size())

#define _OPEN_WRITE_FILE_STREAM(path, name)                                    \
    std::ofstream name(util::OUTPUT_FOLDER / path, std::ios::binary);          \
                                                                               \
    if (!name)                                                                 \
        throw std::ios_base::failure("Failed to open file");

#define _WRITE_FILE(path, data, size, name)                                    \
    _OPEN_WRITE_FILE_STREAM(path, name)                                        \
                                                                               \
    name.write(data, size);                                                    \
                                                                               \
    if (!name)                                                                 \
        throw std::ios_base::failure("Failed to write");                       \
                                                                               \
    name.close()

#define OPEN_FILE(path, out) _OPEN_FILE(path, out, in)
#define OPEN_FILE_STREAM(path, out) _OPEN_FILE_STREAM(path, out, in)
#define OPEN_WRITE_FILE_STREAM(path) _OPEN_WRITE_FILE_STREAM(path, out)
#define WRITE_FILE(path, data, size) _WRITE_FILE(path, data, size, out)

#define ADD_TEST(testName, ...)                                                \
    if (testName)                                                              \
    lodestone::tests::util::runTest(__VA_ARGS__)

#define ADD_TESTS(testName, func, ...)                                         \
    if (testName)                                                              \
    func(__VA_ARGS__)

    const std::filesystem::path INPUT_FOLDER =
        std::filesystem::weakly_canonical("../../../projects/Tests/input");
    const std::filesystem::path OUTPUT_FOLDER =
        std::filesystem::weakly_canonical("../../../projects/Tests/output");

    namespace types {
        static constexpr const char *const MAIN = "main";
    } // namespace types
} // namespace lodestone::tests::util

#endif // LODESTONE_UTIL_H