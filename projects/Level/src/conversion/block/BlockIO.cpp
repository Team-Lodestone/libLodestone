//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Lodestone.Level/conversion/block/BlockIO.h"

namespace lodestone::level::conversion::block {
    void version::BlockIO::registerBlock(const lodestone::common::registry::NamespacedString *internal,
                                         data::AbstractBlockData *blk,
                                         const bool isDefault) {
        mFromInternalConversionMap[internal] = blk;
        mToInternalConversionMap[blk] = internal;
        if (isDefault) {
            mDefaultDataMap[blk->getIdPtr()] = blk;
        }
    }

    void version::BlockIO::registerBlockIfNotExist(const lodestone::common::registry::NamespacedString *internal,
                                                   data::AbstractBlockData *blk,
                                                   const bool isDefault) {
        if (mFromInternalConversionMap.contains(internal)) return;

        mFromInternalConversionMap[internal] = blk;
        mToInternalConversionMap[blk] = internal;
        if (isDefault) {
            mDefaultDataMap[blk->getIdPtr()] = blk;
        }
    }

    data::AbstractBlockData *version::BlockIO::
    convertBlockFromInternal(const lodestone::level::block::state::BlockState *b) {
        if (const auto it = mFromInternalConversionMap.find(b->getBlock()->getID()); it != mFromInternalConversionMap.end()) return it->second;

        return nullptr;
    }

    level::block::state::BlockState version::BlockIO::convertBlockToInternal(const data::AbstractBlockData &b) {
        if (const auto it = mToInternalConversionMap.find(&b); it != mToInternalConversionMap.end()) { // because we hash by value this should theoretically work
            // if we have block ID with state in conversion map, return it
            return level::block::state::BlockState(it->second);
        }

        // otherwise, if we have block id with default value, return that
        if (mDefaultDataMap.find(b.getIdPtr()) != mDefaultDataMap.end()) {
            if (const auto itr = mToInternalConversionMap.find(&b); itr != mToInternalConversionMap.end()) {
                return level::block::state::BlockState(itr->second);
            }
        }

#ifdef USE_FALLBACK_BLOCK
        return level::block::state::BlockState();
#else
        throw std::runtime_error("Could not find block");
#endif
    }
}
