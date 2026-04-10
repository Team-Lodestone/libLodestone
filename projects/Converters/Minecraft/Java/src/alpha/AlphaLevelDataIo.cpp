/** @file AlphaLevelDataIo.cpp
 *
 * @author DexrnZacAttack
 * @date 4/3/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.Minecraft.Java/conversion/alpha/AlphaLevelDataIo.h"

#include <libnbt++/io/stream_reader.h>

namespace lodestone::minecraft::java::conversion::alpha {
    std::unique_ptr<common::world::data::LevelData> AlphaLevelDataIO::read(
        const common::conversion::io::options::OptionPresets::
        CommonReadOptions &options) const {
        auto streamReader = nbt::io::stream_reader(options.input, endian::big);

        auto [name, root] = streamReader.read_compound();
        nbt::tag_compound &level = root.get()->at("Level").as<nbt::tag_compound>();

        const AlphaNbtLevelDataIO *io = this->getAsByRelation<const AlphaNbtLevelDataIO, &identifiers::NBT_LEVEL_DATA_IO>();

        return io->read(common::conversion::io::options::OptionPresets::CommonNbtReadOptions {
            common::conversion::io::options::NbtReaderOptions {
                level
            },
            lodestone::conversion::io::options::versioned::VersionedOptions {
                options.version
            }
        });
    }

    void AlphaLevelDataIO::write(common::world::data::LevelData *ld,
        const lodestone::minecraft::common::conversion::io::options::
        OptionPresets::CommonWriteOptions &options) const {
    }

    std::unique_ptr<common::world::data::LevelData> AlphaNbtLevelDataIO::read(
        const common::conversion::io::options::OptionPresets::
        CommonNbtReadOptions &options) const {
    }

    void AlphaNbtLevelDataIO::write(common::world::data::LevelData *ld,
        const common::conversion::io::options::OptionPresets::
        NbtOutputWriteOptions<const lodestone::conversion::io::options::
        EmptyOptions> &options) const {
    }
}