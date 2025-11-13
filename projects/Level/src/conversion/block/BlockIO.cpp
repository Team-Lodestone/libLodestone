//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Lodestone.Level/conversion/block/BlockIO.h"

namespace lodestone::level::conversion::block {
    gtl::flat_hash_map<const lodestone::common::registry::NamespacedString *, data::AbstractBlockData *> &
    version::BlockIO::
    getFromInternalConversionMap() {
        return mFromInternalConversionMap;
    }

    gtl::flat_hash_map<const data::AbstractBlockData *, const lodestone::common::registry::NamespacedString *,
        types::hash::BlockDataHash, types::hash::BlockDataComparator> &version::BlockIO::
    getToInternalConversionMap() {
        return mToInternalConversionMap;
    }

    gtl::flat_hash_map<const void *, data::AbstractBlockData *> &version::BlockIO::getDefaultDataMap() {
        return mDefaultDataMap;
    }

    void version::BlockIO::registerBlock(const lodestone::common::registry::NamespacedString *internal,
                                         data::AbstractBlockData *blk,
                                         const bool isDefault) {
        gtl::flat_hash_map<const lodestone::common::registry::NamespacedString *, data::AbstractBlockData *> &c =
                getFromInternalConversionMap();
        gtl::flat_hash_map<const data::AbstractBlockData *, const lodestone::common::registry::NamespacedString *,
            types::hash::BlockDataHash, types::hash::BlockDataComparator> &i = getToInternalConversionMap();

        c[internal] = blk;
        i[blk] = internal;
        if (isDefault) {
            gtl::flat_hash_map<const void *, data::AbstractBlockData *> &d = getDefaultDataMap();
            d[blk->getIdPtr()] = blk;
        }
    }

    void version::BlockIO::registerBlockIfNotExist(const lodestone::common::registry::NamespacedString *internal,
                                                   data::AbstractBlockData *blk,
                                                   const bool isDefault) {
        gtl::flat_hash_map<const lodestone::common::registry::NamespacedString *, data::AbstractBlockData *> &c =
                getFromInternalConversionMap();
        gtl::flat_hash_map<const data::AbstractBlockData *, const lodestone::common::registry::NamespacedString *,
            types::hash::BlockDataHash, types::hash::BlockDataComparator> &i = getToInternalConversionMap();

        if (c.contains(internal)) return;

        c[internal] = blk;
        i[blk] = internal;
        if (isDefault) {
            gtl::flat_hash_map<const void *, data::AbstractBlockData *> &d = getDefaultDataMap();
            d[blk->getIdPtr()] = blk;
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
        const auto &d = getDefaultDataMap();
        if (d.find(b.getIdPtr()) != d.end()) {
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
