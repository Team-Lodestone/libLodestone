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

    gtl::flat_hash_map<data::AbstractBlockData *, const lodestone::common::registry::NamespacedString *,
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
        gtl::flat_hash_map<data::AbstractBlockData *, const lodestone::common::registry::NamespacedString *,
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
        gtl::flat_hash_map<data::AbstractBlockData *, const lodestone::common::registry::NamespacedString *,
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
        const gtl::flat_hash_map<const lodestone::common::registry::NamespacedString *, data::AbstractBlockData *> &m =
                getFromInternalConversionMap();
        const lodestone::common::registry::NamespacedString *id = b->getBlock()->getID();

        if (const auto it = m.find(id); it != m.end()) return it->second;

        return nullptr;
    }

    level::block::state::BlockState version::BlockIO::convertBlockToInternal(data::AbstractBlockData *b) {
        thread_local size_t lastBlock = 0;
        thread_local lodestone::level::block::state::BlockState lastState = lodestone::level::block::state::BlockState(
            &lodestone::level::block::Blocks::AIR);

        const size_t hash = b->hash();
        if (hash == lastBlock)
            return lastState;

        const gtl::flat_hash_map<data::AbstractBlockData *, const lodestone::common::registry::NamespacedString *,
            types::hash::BlockDataHash, types::hash::BlockDataComparator> &m = getToInternalConversionMap();

        if (const auto it = m.find(b); it != m.end()) {
            // if we have block ID with state in conversion map, return it
            lastBlock = hash;
            lastState = level::block::state::BlockState(it->second);
            return lastState;
        }

        // otherwise, if we have block id with default value, return that
        const auto &d = getDefaultDataMap();
        if (const auto it = d.find(b->getIdPtr()); it != d.end()) {
            if (const auto itr = m.find(b); itr != m.end()) {
                lastBlock = hash;
                lastState = level::block::state::BlockState(itr->second);
                return lastState;
            }
        }

#ifdef USE_FALLBACK_BLOCK
        return level::block::state::BlockState();
#else
        throw std::runtime_error("Could not find block");
#endif
    }
}
