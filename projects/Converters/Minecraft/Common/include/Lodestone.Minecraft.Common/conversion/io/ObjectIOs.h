//
// Created by DexrnZacAttack on 2/14/26 using zPc-i2.
//
#ifndef LODESTONE_MINECRAFT_COMMON_OBJECTIOS_H
#define LODESTONE_MINECRAFT_COMMON_OBJECTIOS_H
#include <type_traits>

#include "Lodestone.Common/registry/Identifier.h"
#include "Lodestone.Minecraft.Common/conversion/io/interfaces/ILevelDataIo.h"
#include "Lodestone.Minecraft.Common/conversion/io/interfaces/IRegionIo.h"
#include "Lodestone.Minecraft.Common/conversion/io/options/NbtOutputOptions.h"
#include "Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h"
#include "Lodestone.Minecraft.Common/region/Region.h"

#include <Lodestone.Conversion/io/AbstractObjectIo.h>
#include <Lodestone.Conversion/io/options/OptionsBuilder.h>
#include "Lodestone.Minecraft.Common/world/data/LevelData.h"
#include <libnbt++/io/stream_writer.h>

#include <Lodestone.Conversion/io/interfaces/IWorldIo.h>
#include <Lodestone.Conversion/io/interfaces/ILevelIo.h>
#include <Lodestone.Conversion/io/interfaces/IPlayerIo.h>
#include <Lodestone.Conversion/io/interfaces/IChunkIo.h>

namespace nbt {
    class tag_compound;
}

namespace lodestone::minecraft::common::conversion::io {
    template <const lodestone::common::registry::Identifier *I, typename RO, typename WO, typename WR = void>
    requires lodestone::common::util::concepts::void_or_derived_from_v<lodestone::conversion::io::options::IOptions, RO> && lodestone::common::util::concepts::void_or_derived_from_v<lodestone::conversion::io::options::IOptions, WO>
    class LevelDataIO : public interfaces::ILevelDataIO,
                public lodestone::conversion::io::AbstractObjectIO<I, std::unique_ptr<world::data::LevelData>, world::data::LevelData *, RO, WO, WR> {};

    template <const lodestone::common::registry::Identifier *I, typename RO, typename WO, typename WR = void>
    requires lodestone::common::util::concepts::void_or_derived_from_v<lodestone::conversion::io::options::IOptions, RO> && lodestone::common::util::concepts::void_or_derived_from_v<lodestone::conversion::io::options::IOptions, WO>
    class RegionIO : public interfaces::IRegionIO,
                     public lodestone::conversion::io::AbstractObjectIO<I, std::unique_ptr<region::Region>, level::Level *, RO, WO, WR> {};

    template <const lodestone::common::registry::Identifier *I, typename R, typename W, typename RO, typename WO>
    requires lodestone::common::util::concepts::void_or_derived_from_v<lodestone::conversion::io::options::IOptions, RO>
          && lodestone::common::util::concepts::void_or_derived_from_v<lodestone::conversion::io::options::IOptions, WO>
    class NbtIO : public lodestone::conversion::io::AbstractObjectIO<I, R, W, RO, const options::OptionPresets::NbtOutputWriteOptions<WO>, void> {
    public:

        nbt::tag_compound tagFromWritten(W obj, WO &options) const {
            nbt::tag_compound c;

            options::OptionPresets::NbtOutputWriteOptions<WO> h {
                options,
                options::NbtOutputOptions {
                    c
                }
            };

            this->write(obj, h);

            return c;
        };

        void writeToNbtStreamWriter(W obj, const std::string& key, nbt::io::stream_writer &writer, WO &options) const {
            writer.write_tag(key, this->tagFromWritten(obj, options));
        }
    };

    template <const lodestone::common::registry::Identifier *I, typename RO, typename WO>
    requires lodestone::common::util::concepts::void_or_derived_from_v<lodestone::conversion::io::options::IOptions, RO> && lodestone::common::util::concepts::void_or_derived_from_v<lodestone::conversion::io::options::IOptions, WO>
    class NbtPlayerIO : public lodestone::conversion::io::interfaces::IPlayerIO,
                 public NbtIO<I, std::unique_ptr<level::entity::Player>, level::entity::Player *, RO, WO> {};

    template <const lodestone::common::registry::Identifier *I, typename RO, typename WO>
    requires lodestone::common::util::concepts::void_or_derived_from_v<lodestone::conversion::io::options::IOptions, RO> && lodestone::common::util::concepts::void_or_derived_from_v<lodestone::conversion::io::options::IOptions, WO>
    class NbtLevelIO : public lodestone::conversion::io::interfaces::ILevelIO,
             public NbtIO<I, std::unique_ptr<level::Level>, level::Level *, RO, WO> {};

    template <const lodestone::common::registry::Identifier *I, typename RO, typename WO>
    requires lodestone::common::util::concepts::void_or_derived_from_v<lodestone::conversion::io::options::IOptions, RO> && lodestone::common::util::concepts::void_or_derived_from_v<lodestone::conversion::io::options::IOptions, WO>
    class NbtLevelDataIO : public interfaces::ILevelDataIO,
         public NbtIO<I, std::unique_ptr<world::data::LevelData>, world::data::LevelData *, RO, WO> {};

    template <const lodestone::common::registry::Identifier *I, typename RO, typename WO>
    requires lodestone::common::util::concepts::void_or_derived_from_v<lodestone::conversion::io::options::IOptions, RO> && lodestone::common::util::concepts::void_or_derived_from_v<lodestone::conversion::io::options::IOptions, WO>
    class NbtChunkIO : public lodestone::conversion::io::interfaces::IChunkIO,
                 public NbtIO<I, std::unique_ptr<level::chunk::Chunk>, level::chunk::Chunk *, RO, WO> {};
}

#endif // LODESTONE_OBJECTIOS_H