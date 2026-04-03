/** @file McRegionLevelDataIo.h
 *
 * @author DexrnZacAttack
 * @date 3/11/26
 * 
 * @device zPc-i2
 *
 * @copyright Copyright (c) 2026 Team Lodestone
 * @license This project is licensed under the LGPL 3.0 license, see the LICENSE file for details.
 */
#ifndef LODESTONE_MCREGIONLEVELDATAIO_H
#define LODESTONE_MCREGIONLEVELDATAIO_H
#include <Lodestone.Conversion/registry/RegistryRelations.h>
#include <Lodestone.Minecraft.Common/conversion/io/ObjectIOs.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"

namespace lodestone::minecraft::java::conversion::mcregion {
    class McRegionNbtLevelDataIO;

    class McRegionLevelDataIO : public common::conversion::io::LevelDataIO<&identifiers::MCREGION_PLAYER_IO, const common::conversion::io::options::OptionPresets::CommonPlayerReadOptions, const lodestone::minecraft::common::conversion::io::options::OptionPresets::CommonWriteOptions>,
    public lodestone::conversion::registry::RegistryIdentifierRelations<
        lodestone::conversion::registry::RegistryIdentifierRelation<&identifiers::NBT_LEVEL_DATA_IO, const McRegionNbtLevelDataIO, &identifiers::MCREGION_NBT_PLAYER_IO, conversion::registry::LevelDataIORegistry>
    >
    {
    public:
        std::unique_ptr<common::world::data::LevelData> read(const common::conversion::io::options::OptionPresets::CommonPlayerReadOptions &options) const override;
        void write(common::world::data::LevelData *ld, const lodestone::minecraft::common::conversion::io::options::OptionPresets::CommonWriteOptions &options) const override;
    };

    class McRegionNbtLevelDataIO : public common::conversion::io::NbtLevelDataIO<&identifiers::MCREGION_NBT_LEVEL_DATA_IO, const common::conversion::io::options::OptionPresets::CommonNbtFilesystemReadOptions, const lodestone::conversion::io::options::EmptyOptions>,
    public lodestone::conversion::registry::RegistryIdentifierRelations<
        lodestone::conversion::registry::RegistryIdentifierRelation<&identifiers::LEVEL_DATA_IO, const McRegionLevelDataIO, &identifiers::MCREGION_LEVEL_DATA_IO, conversion::registry::LevelDataIORegistry>
    > {
    public:
        std::unique_ptr<common::world::data::LevelData> read(const common::conversion::io::options::OptionPresets::CommonNbtFilesystemReadOptions &options) const override;
        void write(common::world::data::LevelData *ld,const common::conversion::io::options::OptionPresets::NbtOutputWriteOptions<const lodestone::conversion::io::options::EmptyOptions> &options) const override;
    };
}

#endif //LODESTONE_MCREGIONLEVELDATAIO_H