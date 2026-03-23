/** @file MineV3WorldIo.cpp
*
* @author Zero_DSRS_VX
* @date 3/23/26
*
* @device mac-8
*
* @copyright Copyright (c) 2026 Team Lodestone
* @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
*/

#include "Lodestone.Minecraft.Java/conversion/classic/minev3/MineV3WorldIo.h"

#include "BinaryIO/stream/BinaryInputStream.h"
#include "Lodestone.Minecraft.Java/classic/minev3/MineV3World.h"
#include "Lodestone.Minecraft.Java/conversion/classic/minev3/MineV3LevelIO.h"

namespace lodestone::minecraft::java::classic::minev3 {
    std::unique_ptr<level::world::World> MineV3WorldIO::read(const common::conversion::io::options::OptionPresets::CommonReadOptions &options) const {
        bio::stream::BinaryInputStream bis(options.input);

        const MineV3LevelIO *lio = this->getAsByRelation<const MineV3LevelIO, &conversion::identifiers::LEVEL_IO>();

        std::unique_ptr<level::Level> unique =
            lio->read( common::conversion::io::options::OptionPresets::CommonReadOptions {
            conversion::io::options::fs::file::FileReaderOptions {
                bis.getStream()
            },
            conversion::io::options::versioned::VersionedOptions {
                options.version
            }
        }); // todo: proper version!!!!

        // TODO: world and author name
        return std::make_unique<MineV3World>(std::move(unique));
    }

    void MineV3WorldIO::write(level::world::World *w, const MineV3WriteOptions &options) const {
    }

    void MineV3WorldIO::write(level::world::World *w, const MineV3WriteOptions &options) {

    }
} // namespace lodestone::minecraft::java::classic::minev3