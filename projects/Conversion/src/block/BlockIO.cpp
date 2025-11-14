//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Lodestone.Conversion/block/BlockIO.h"

namespace lodestone::conversion::block {
    void version::BlockIO::registerBlock(const common::registry::NamespacedString *internal,
        data::AbstractBlockData *blk, const bool isDefault) {
        registerBlock(lodestone::level::block::BlockRegistry::sInstance.getBlock(internal), blk, isDefault);
    }

    void version::BlockIO::registerBlock(const lodestone::level::block::Block *internal,
                                         data::AbstractBlockData *blk,
                                         const bool isDefault) {
        mFromInternalConversionMap[internal] = blk;
        mToInternalConversionMap[blk] = internal;
    }

    void version::BlockIO::registerBlockIfNotExist(const lodestone::level::block::Block *internal,
                                                   data::AbstractBlockData *blk,
                                                   const bool isDefault) {
        if (mFromInternalConversionMap.contains(internal)) return;

        mFromInternalConversionMap[internal] = blk;
        mToInternalConversionMap[blk] = internal;
    }

    void version::BlockIO::registerBlockIfNotExist(const common::registry::NamespacedString *internal,
    data::AbstractBlockData *blk, const bool isDefault) {
        registerBlockIfNotExist(level::block::BlockRegistry::sInstance.getBlock(internal), blk, isDefault);
    }

    data::AbstractBlockData *version::BlockIO::
    convertBlockFromInternal(const lodestone::level::block::state::BlockState *b) {
        if (const auto it = mFromInternalConversionMap.find(b->getBlock()); it != mFromInternalConversionMap.end())
            return it->second;

        return nullptr;
    }

    level::block::state::BlockState version::BlockIO::convertBlockToInternal(const data::AbstractBlockData &b) {
        if (const auto it = mToInternalConversionMap.find(&b); it != mToInternalConversionMap.end()) { // because we hash by value this should theoretically work
            // if we have block ID with state in conversion map, return it
            return level::block::state::BlockState(it->second);
        }

#ifdef USE_FALLBACK_BLOCK
        return level::block::state::BlockState();
#else
        throw std::runtime_error(std::format("Could not find block {}", b.toString()));
#endif
    }
}
