/** @file ZipUtils.cpp
*
 * @author Zero_DSRS_VX
 * @date 6/22/26
 *
 * @device PC
 */
#include "Lodestone.Tests/util/ZipUtils.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <unzip.h>
#include <sys/stat.h>

void lodestone::tests::util::ZipUtils::extractAll(const std::filesystem::path &input_path,
                                                  const std::filesystem::path &output_path) {
    const unzFile zip_file = unzOpen(input_path.c_str());
    if (!zip_file) {
        throw std::runtime_error(std::string("unzOpen failed for ") + input_path.c_str());
    }

    unz_global_info global_info;
    if (unzGetGlobalInfo(zip_file, &global_info) != UNZ_OK) {
        unzClose(zip_file);
        throw std::runtime_error(std::string("unzGetGlobalInfo failed for ") + input_path.c_str());
    }

    char buffer[READ_SIZE];

    // Read file-by-file
    for (int i = 0; i < global_info.number_entry; i++) {
        unz_file_info file_info;

        // Get current file info
        char file_name[MAX_FILENAME];
        if (unzGetCurrentFileInfo(zip_file, &file_info, file_name, MAX_FILENAME, nullptr, 0, nullptr, 0) != UNZ_OK) {
            unzClose(zip_file);
            throw std::runtime_error(std::string("unzGetCurrentFile failed for ") + file_name);
        }

        extractEntry(zip_file, file_name, (output_path / file_name).c_str(), buffer);

        if (i + 1 < global_info.number_entry) {
            if (unzGoToNextFile(zip_file) != UNZ_OK) {
                unzClose(zip_file);
            }
        }
    }

    unzClose(zip_file);
}

void lodestone::tests::util::ZipUtils::extractEntry(const unzFile zip_file, const char *file_name,
                                                           const char *output_file_name, char buffer[]) {
    // Check if file entry is a directory
    if (file_name[std::strlen(file_name) - 1] == '/') {
        mkdir(file_name, S_IRWXU);
    } else {
        // Entry is a file, extract to directory.
        if (unzOpenCurrentFile(zip_file) != UNZ_OK) {
            unzClose(zip_file);
            throw std::runtime_error(std::string("unzOpenCurrentFile failed for ") + file_name);
        }

        const std::filesystem::path file_path(output_file_name);
        std::filesystem::path parentDir = file_path.parent_path();

        try {
            if (!parentDir.empty()) {
                std::filesystem::create_directories(parentDir);
            }

            std::ofstream outputFile(file_path);
            if (outputFile.is_open()) {
                int error = UNZ_OK;
                do {
                    error = unzReadCurrentFile(zip_file, buffer, READ_SIZE);
                    if (error < 0) {
                        unzCloseCurrentFile(zip_file);
                        unzClose(zip_file);
                        throw std::runtime_error(std::string("unzReadCurrentFile failed for file: ") + file_name);
                    }

                    if (error > 0) {
                        outputFile.write(buffer, error);
                        error = outputFile.good() ? 0 : 1;
                    }
                } while (error > 0);

                outputFile.close();
            } else {
                std::cerr << "Failed to open or create the file.\n";
            }
        } catch (const std::filesystem::filesystem_error &e) {
            std::cerr << "Filesystem error: " << e.what() << '\n';
            unzCloseCurrentFile(zip_file);
            unzClose(zip_file);
        }

        unzCloseCurrentFile(zip_file);
    }
}
