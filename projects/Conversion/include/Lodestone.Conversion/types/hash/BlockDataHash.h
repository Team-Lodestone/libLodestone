//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKDATAHASH_H
#define LODESTONE_BLOCKDATAHASH_H
#include "Lodestone.Conversion/block/data/AbstractBlockData.h"

namespace lodestone::conversion::types::hash {
    struct BlockDataHash {
        size_t operator()(
            const conversion::block::data::AbstractBlockData *blk) const {
            return blk->hash();
        }
    };

    struct BlockDataComparator {
        bool operator()(
            const conversion::block::data::AbstractBlockData *lhs,
            const conversion::block::data::AbstractBlockData *rhs) const {
            return lhs->equals(rhs);
        }
    };
} // namespace lodestone::conversion::types::hash

#endif // LODESTONE_BLOCKDATAHASH_H