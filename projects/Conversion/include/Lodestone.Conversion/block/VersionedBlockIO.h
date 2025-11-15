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
#include <Lodestone.Level/block/properties/BlockProperties.h>

#include "Lodestone.Conversion/block/BlockIO.h"
#include "Lodestone.Conversion/block/data/AbstractBlockData.h"

namespace lodestone::conversion::block::version {
    class LODESTONE_API VersionedBlockIO {
    public:
        constexpr void registerBlock(const uint32_t version,
                                     const lodestone::common::registry::Identifier *internal,
                                     data::AbstractBlockData *blk) {
            mFromInternalConversionMap[version][internal] = blk;
        }

        std::unique_ptr<BlockIO> getIo(uint32_t version);

    private:
        std::map<uint32_t, gtl::flat_hash_map<const lodestone::common::registry::Identifier *,
            data::AbstractBlockData *> > mFromInternalConversionMap{};
    };
}

#endif //LODESTONE_VERSIONEDBLOCKIO_H