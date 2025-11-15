//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKIO_H
#define LODESTONE_BLOCKIO_H

#include <iostream>
#include <variant>

#include <Lodestone.Common/Defines.h>
#include <Lodestone.Level/block/properties/BlockProperties.h>

#include "Lodestone.Conversion/block/data/AbstractBlockData.h"
#include <gtl/phmap.hpp>
#include "Lodestone.Conversion/types/hash/BlockDataHash.h"

namespace lodestone::conversion::block::version {
    /** Aids with block conversion between versions */
    class LODESTONE_API BlockIO {
    public:
        // TODO: handle converting block states!!!
        // via a separate conversion map

        void registerBlock(const common::registry::Identifier *internal, data::AbstractBlockData *blk,
                           const bool isDefault = false);
        void registerBlock(const lodestone::level::block::Block *internal, data::AbstractBlockData *blk,
                   const bool isDefault = false);

        void registerBlockIfNotExist(const common::registry::Identifier *internal, data::AbstractBlockData *blk,
                                     const bool isDefault = false);
        void registerBlockIfNotExist(const lodestone::level::block::Block *internal, data::AbstractBlockData *blk,
                             const bool isDefault = false);

        /** Converts an internal block to the BlockIO's format */
        data::AbstractBlockData *convertBlockFromInternal(const lodestone::level::block::properties::BlockProperties *b);

        /** Converts a block from BlockIO to the internal format */
        lodestone::level::block::properties::BlockProperties convertBlockToInternal(const data::AbstractBlockData &b);
    private:
        // todo I have learned about the existence of bimap but I don't know if a lib exists for cpp
        gtl::flat_hash_map<const lodestone::level::block::Block *, data::AbstractBlockData *>
        mFromInternalConversionMap;
        gtl::flat_hash_map<const data::AbstractBlockData *, const lodestone::level::block::Block *,
            types::hash::BlockDataHash, types::hash::BlockDataComparator> mToInternalConversionMap;
    };
}

#endif //LODESTONE_BLOCKIO_H