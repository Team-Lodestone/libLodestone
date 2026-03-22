//
// Created by DexrnZacAttack on 2/15/26 using zPc-i2.
//
#ifndef LODESTONE_OBJECTIOS_H
#define LODESTONE_OBJECTIOS_H
#include <Lodestone.Common/registry/Identifier.h>
#include <Lodestone.Common/util/Concepts.h>
#include "Lodestone.Conversion/io/AbstractObjectIo.h"
#include "Lodestone.Conversion/internal/Exports.h"

namespace lodestone::conversion::io {
    template <const common::registry::Identifier *I, typename RO, typename WO, typename WR = void>
    requires lodestone::common::util::concepts::void_or_derived_from_v<options::IOptions, RO> && lodestone::common::util::concepts::void_or_derived_from_v<options::IOptions, WO>
    class LODESTONE_CONVERSION_API PlayerIO : public interfaces::IPlayerIO,
                     public AbstractObjectIO<I, std::unique_ptr<level::entity::Player>, level::entity::Player *, RO, WO, WR> {};

    template <const common::registry::Identifier *I, typename RO, typename WO, typename WR = void>
    requires lodestone::common::util::concepts::void_or_derived_from_v<options::IOptions, RO> && lodestone::common::util::concepts::void_or_derived_from_v<options::IOptions, WO>
    class LODESTONE_CONVERSION_API RegionIO : public interfaces::IRegionIO,
                     public AbstractObjectIO<I, std::unique_ptr<level::region::Region>, level::Level *, RO, WO, WR> {};

    template <const common::registry::Identifier *I, typename RO, typename WO, typename WR = void>
        requires lodestone::common::util::concepts::void_or_derived_from_v<options::IOptions, RO> && lodestone::common::util::concepts::void_or_derived_from_v<options::IOptions, WO>
    class LODESTONE_CONVERSION_API LevelIO : public interfaces::ILevelIO,
                    public AbstractObjectIO<I, std::unique_ptr<level::Level>, level::Level *, RO, WO, WR> {
    };

    template <const common::registry::Identifier *I, typename RO, typename WO, typename WR = void>
    requires lodestone::common::util::concepts::void_or_derived_from_v<options::IOptions, RO> && lodestone::common::util::concepts::void_or_derived_from_v<options::IOptions, WO>
    class LODESTONE_CONVERSION_API WorldIO : public interfaces::IWorldIO,
                    public AbstractObjectIO<I, std::unique_ptr<level::world::World>, level::world::World *, RO, WO, WR> {};

    template <const common::registry::Identifier *I, typename RO, typename WO, typename WR = void>
    requires lodestone::common::util::concepts::void_or_derived_from_v<options::IOptions, RO> && lodestone::common::util::concepts::void_or_derived_from_v<options::IOptions, WO>
    class LODESTONE_CONVERSION_API ChunkIO : public interfaces::IChunkIO,
                    public AbstractObjectIO<I, std::unique_ptr<level::chunk::Chunk>, level::chunk::Chunk *, RO, WO, WR> {};
}

#endif // LODESTONE_OBJECTIOS_H