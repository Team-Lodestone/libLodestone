//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Conversion/Block/BlockIO.h"

namespace lodestone::level::conversion::block {
    std::unordered_map<std::string, data::AbstractBlockData *> & version::BlockIO::
    getFromInternalConversionMap() {
        return mFromInternalConversionMap;
    }

    std::unordered_map<data::AbstractBlockData *, std::string> & version::BlockIO::
    getToInternalConversionMap() {
        return mToInternalConversionMap;
    }

    std::unordered_map<const void *, data::AbstractBlockData *> & version::BlockIO::getDefaultDataMap() {
        return mDefaultDataMap;
    }

    void version::BlockIO::registerBlock(const std::string &internal, data::AbstractBlockData *blk,
        const bool isDefault) {
        std::unordered_map<std::string, data::AbstractBlockData*> &c = getFromInternalConversionMap();
        std::unordered_map<data::AbstractBlockData*, std::string> &i = getToInternalConversionMap();

        c[internal] = blk;
        i[blk] = internal;
        if (isDefault) {
            std::unordered_map<const void *, data::AbstractBlockData*> &d = getDefaultDataMap();
            d[blk->getId()] = blk;
        }
    }

    void version::BlockIO::registerBlockIfNotExist(const std::string &internal, data::AbstractBlockData *blk,
        const bool isDefault) {
        std::unordered_map<std::string, data::AbstractBlockData*> &c = getFromInternalConversionMap();
        std::unordered_map<data::AbstractBlockData*, std::string> &i = getToInternalConversionMap();

        if (c.contains(internal)) return;

        c[internal] = blk;
        i[blk] = internal;
        if (isDefault) {
            std::unordered_map<const void *, data::AbstractBlockData*> &d = getDefaultDataMap();
            d[blk->getId()] = blk;
        }
    }

    data::AbstractBlockData * version::BlockIO::
    convertBlockFromInternal(lodestone::level::block::state::BlockState *b) {
        const std::unordered_map<std::string, data::AbstractBlockData*> &m = getFromInternalConversionMap();
        const std::string id = b->getBlock()->getID();

        if (const auto it = m.find(id); it != m.end()) return it->second;

        throw std::runtime_error("h");
    }

    lodestone::level::block::state::BlockState version::BlockIO::convertBlockToInternal(data::AbstractBlockData *b) {
        const std::unordered_map<data::AbstractBlockData*, std::string> &m = getToInternalConversionMap();

        if (auto it = m.find(b); it != m.end()) {
            // if we have block ID with state in conversion map, return it
            return lodestone::level::block::state::BlockState(it->second);
        }

        // otherwise, if we have block id with default value, return that
        const auto& d = getDefaultDataMap();
        if (auto it = d.find(b->getId()); it != d.end()) {
            if (auto itr = m.find(b); itr != m.end()) {
                return lodestone::level::block::state::BlockState(itr->second);
            }
        }

#ifdef USE_FALLBACK_BLOCK
        return lodestone::level::block::state::BlockState();
#else
        throw std::runtime_error("Could not find block");
#endif
    }
}
