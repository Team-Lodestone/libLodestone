//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_VERSIONEDBLOCKIO_H
#define LODESTONE_VERSIONEDBLOCKIO_H

#include <iostream>
#include <map>
#include <memory>
#include <variant>

#include <Lodestone.Common/Defines.h>
#include "Lodestone.Level/block/state/BlockState.h"

#include "Lodestone.Level/conversion/block/BlockIO.h"
#include "Lodestone.Level/conversion/block/data/AbstractBlockData.h"

namespace lodestone::level::conversion::block::version {
    class LODESTONE_API VersionedBlockIO {
    public:
        constexpr void registerBlock(const uint32_t version,
                                     const lodestone::common::registry::NamespacedString *internal,
                                     data::AbstractBlockData *blk) {
            mFromInternalConversionMap[version][internal] = blk;
        }

        std::unique_ptr<BlockIO> getIo(uint32_t version);

    private:
        std::map<uint32_t, gtl::flat_hash_map<const lodestone::common::registry::NamespacedString *,
            data::AbstractBlockData *> > mFromInternalConversionMap{};
    };
}

#endif //LODESTONE_VERSIONEDBLOCKIO_H