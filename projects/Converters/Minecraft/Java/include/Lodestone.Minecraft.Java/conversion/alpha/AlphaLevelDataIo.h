/** @file AlphaLevelDataIo.h
 *
 * @author DexrnZacAttack
 * @date 4/3/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_ALPHALEVELDATAIO_H
#define LODESTONE_ALPHALEVELDATAIO_H
#include <Lodestone.Conversion/registry/RegistryRelations.h>
#include <Lodestone.Minecraft.Common/conversion/registry/Registries.h>

#include <Lodestone.Minecraft.Common/conversion/io/ObjectIOs.h>
#include "Lodestone.Minecraft.Java/Identifiers.h"

namespace lodestone::minecraft::java::conversion::alpha {
    class AlphaNbtLevelDataIO;

    class AlphaLevelDataIO : public common::conversion::io::LevelDataIO<&identifiers::io::levelData::ALPHA_LEVEL_DATA_IO, const common::conversion::io::options::OptionPresets::CommonReadOptions, const lodestone::minecraft::common::conversion::io::options::OptionPresets::CommonWriteOptions>,
    public lodestone::conversion::registry::RegistryIdentifierRelations<
        lodestone::conversion::registry::RegistryIdentifierRelation<&identifiers::NBT_LEVEL_DATA_IO, const AlphaNbtLevelDataIO, &identifiers::io::levelData::nbt::ALPHA_NBT_LEVEL_DATA_IO, lodestone::conversion::registry::LevelDataIORegistry>
    >
    {
    public:
        std::unique_ptr<common::world::data::LevelData> read(const common::conversion::io::options::OptionPresets::CommonReadOptions &options) const override;
        void write(common::world::data::LevelData *ld, const lodestone::minecraft::common::conversion::io::options::OptionPresets::CommonWriteOptions &options) const override;
    };

    class AlphaNbtLevelDataIO : public common::conversion::io::NbtLevelDataIO<&identifiers::io::levelData::nbt::ALPHA_NBT_LEVEL_DATA_IO, const common::conversion::io::options::OptionPresets::CommonNbtReadOptions, const lodestone::conversion::io::options::EmptyOptions>,
    public lodestone::conversion::registry::RegistryIdentifierRelations<
        lodestone::conversion::registry::RegistryIdentifierRelation<&identifiers::LEVEL_DATA_IO, const AlphaLevelDataIO, &identifiers::io::levelData::ALPHA_LEVEL_DATA_IO, lodestone::conversion::registry::LevelDataIORegistry>
    > {
    public:
        std::unique_ptr<common::world::data::LevelData> read(const common::conversion::io::options::OptionPresets::CommonNbtReadOptions &options) const override;
        void write(common::world::data::LevelData *ld,const common::conversion::io::options::OptionPresets::NbtOutputWriteOptions<const lodestone::conversion::io::options::EmptyOptions> &options) const override;
    };
}

#endif // LODESTONE_ALPHALEVELDATAIO_H