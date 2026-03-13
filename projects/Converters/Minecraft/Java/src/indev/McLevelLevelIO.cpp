//
// Created by DexrnZacAttack on 10/16/25 using zPc-i2.
//

#include "Lodestone.Minecraft.Java/conversion/indev/McLevelLevelIO.h"

namespace lodestone::minecraft::java::indev {

    std::unique_ptr<lodestone::level::Level>
    McLevelLevelIO::read(const lodestone::minecraft::common::conversion::io::options::OptionPresets::CommonReadOptions &options) const {}

    void McLevelLevelIO::write(lodestone::level::Level *l, const lodestone::minecraft::common::conversion::io::options::OptionPresets::CommonWriteOptions &options) const {}

    std::unique_ptr<level::Level> McLevelNbtLevelIO::read(
        const common::conversion::io::options::OptionPresets::
        CommonNbtReadOptions &options) const {
    }

    void McLevelNbtLevelIO::write(level::Level *l, const common::conversion::io::options::OptionPresets::NbtOutputWriteOptions<const conversion::io::options::EmptyOptions> &options) const {
    }

} // namespace lodestone::minecraft::java::indev