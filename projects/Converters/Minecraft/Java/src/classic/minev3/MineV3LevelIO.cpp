/** @file MineV3LevelIO.cpp
*
* @author Zero_DSRS_VX
* @date 3/22/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/

#include "Lodestone.Minecraft.Java/conversion/classic/minev3/MineV3LevelIO.h"
#include "Lodestone.Minecraft.Java/classic/minev3/JavaSerializedClassParser.h"

#include <fstream>

#include "BinaryIO/stream/BinaryInputStream.h"

namespace lodestone::minecraft::java::classic::minev3 {
    std::unique_ptr<level::Level>
    MineV3LevelIO::read(const common::conversion::io::options::OptionPresets::CommonReadOptions& options) const {
        bio::stream::BinaryInputStream strm(options.input);

        auto level = std::make_unique<level::Level>();

        // Check magic header
        const uint32_t header = strm.readBE<uint32_t>();

        if (header != 0x271BB788) {
            return level;
        }

        // Read serialized class file starting entry
        strm.readByte();

        const uint16_t magic = strm.readBE<uint16_t>(); // AC ED
        const uint16_t classVersion = strm.readBE<uint16_t>(); // 00 05

        if (magic != 0xACED) {
            return level;
        }

        if (classVersion != 5) {
            LOG_DEBUG("Class file version is not tested!");
        }

        auto class_parser = common::java::classic::minev3::JavaSerializedClassParser(strm);
        // class_parser.parseAllEntries();
        class_parser.parseEntry();

        return level;
    }

    void MineV3LevelIO::write(level::Level *l, const common::conversion::io::options::OptionPresets::CommonWriteOptions &options) const {

    }
} // namespaace lodestone::minecraft::java::classic::minev3