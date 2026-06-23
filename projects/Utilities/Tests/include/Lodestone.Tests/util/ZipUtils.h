/** @file ZipUtils.h
*
 * @author Zero_DSRS_VX
 * @date 6/22/26
 *
 * @device PC
 */
#ifndef LODESTONE_ZIPUTILS_H
#define LODESTONE_ZIPUTILS_H

#define MAX_FILENAME 512
#define READ_SIZE 8192
#include <filesystem>

#include <unzip.h>

namespace lodestone::tests::util {
    class ZipUtils {
        public:
            static void extractAll(const std::filesystem::path &input_path, const std::filesystem::path &output_path);
            static void extractEntry(unzFile zip_file, const char *file_name, const char *output_file_name, char buffer[]);
    };
} // lodestone::tests::util

#endif //LODESTONE_ZIPUTILS_H
