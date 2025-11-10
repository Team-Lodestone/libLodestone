//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKIO_H
#define LODESTONE_BLOCKIO_H

#include <iostream>
#include <variant>

#include <Lodestone.Common/Defines.h>
#include "Lodestone.Level/block/state/BlockState.h"

#include "Lodestone.Level/conversion/block/data/AbstractBlockData.h"
#include <gtl/phmap.hpp>
#include "Lodestone.Level/types/hash/BlockDataHash.h"

namespace lodestone::level::conversion::block::version {
    /** Aids with block conversion between versions */
    class LODESTONE_API BlockIO {
    public:
        // TODO: handle converting block states!!!
        // via a separate conversion map
        // TODO: this file is messy!

        virtual ~BlockIO() = default;

        /** Returns a map that maps internal block IDs to a Blk  */
        virtual gtl::flat_hash_map<const common::registry::NamespacedString *, data::AbstractBlockData *> &
        getFromInternalConversionMap();

        /** Returns a map that maps Blks to an internal block ID  */
        virtual gtl::flat_hash_map<data::AbstractBlockData *, const common::registry::NamespacedString *,
            types::hash::BlockDataHash, types::hash::BlockDataComparator> &getToInternalConversionMap();

        /** Returns a map that maps block IDs to their default data value */
        virtual gtl::flat_hash_map<const void *, data::AbstractBlockData *> &getDefaultDataMap();

        void registerBlock(const common::registry::NamespacedString *internal, data::AbstractBlockData *blk,
                           const bool isDefault = false);

        void registerBlockIfNotExist(const common::registry::NamespacedString *internal, data::AbstractBlockData *blk,
                                     const bool isDefault = false);

        /** Converts an internal block to the BlockIO's format */
        virtual data::AbstractBlockData *convertBlockFromInternal(const lodestone::level::block::state::BlockState *b);

        /** Converts a block from BlockIO to the internal format */
        virtual lodestone::level::block::state::BlockState convertBlockToInternal(data::AbstractBlockData *b);

        // /** Reads data into a new Block */
        // virtual lodestone::level::block::state::BlockState readBlock(uint8_t *data) = 0;
        // /** Writes a block to data */
        // virtual void writeBlock(lodestone::level::block::state::BlockState *b, uint8_t *arr) = 0;
    private:
        gtl::flat_hash_map<const common::registry::NamespacedString *, data::AbstractBlockData *>
        mFromInternalConversionMap;
        gtl::flat_hash_map<data::AbstractBlockData *, const common::registry::NamespacedString *,
            types::hash::BlockDataHash, types::hash::BlockDataComparator> mToInternalConversionMap;
        gtl::flat_hash_map<const void *, data::AbstractBlockData *> mDefaultDataMap;
    };
}

#endif //LODESTONE_BLOCKIO_H