//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKDATAHASH_H
#define LODESTONE_BLOCKDATAHASH_H
#include "Lodestone.Level/conversion/block/data/AbstractBlockData.h"

namespace lodestone::level::types::hash {
    struct BlockDataHash {
        size_t operator()(const conversion::block::data::AbstractBlockData *blk) const {
            return blk->hash();
        }
    };

    struct BlockDataComparator {
        bool operator()(const conversion::block::data::AbstractBlockData *lhs,
                        const conversion::block::data::AbstractBlockData *rhs) const {
            return lhs->equals(rhs);
        }
    };
}

#endif //LODESTONE_BLOCKDATAHASH_H