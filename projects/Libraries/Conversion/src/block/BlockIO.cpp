//
// Created by DexrnZacAttack on 10/15/25 using zPc-i2.
//
#include "Lodestone.Conversion/block/BlockIO.h"

#include <Lodestone.Level/block/instance/ImmutableBlockInstance.h>

namespace lodestone::conversion::block {
    void version::BlockIO::registerBlock(
        const common::registry::Identifier *internal,
        data::AbstractBlockData *blk, const bool isDefault) {
        registerBlock(
            lodestone::level::block::BlockRegistry::getInstance().getBlock(
                internal),
            blk, isDefault);
    }

    void version::BlockIO::registerBlock(
        const lodestone::level::block::Block *internal,
        data::AbstractBlockData *blk, const bool isDefault) {
        m_fromInternalConversionMap[internal] = blk;
        m_toInternalConversionMap[blk] = internal;
    }

    void version::BlockIO::registerBlockIfNotExist(
        const lodestone::level::block::Block *internal,
        data::AbstractBlockData *blk, const bool isDefault) {
        if (m_fromInternalConversionMap.contains(internal))
            return;

        m_fromInternalConversionMap[internal] = blk;
        m_toInternalConversionMap[blk] = internal;
    }

    void version::BlockIO::registerBlockIfNotExist(
        const common::registry::Identifier *internal,
        data::AbstractBlockData *blk, const bool isDefault) {
        registerBlockIfNotExist(
            level::block::BlockRegistry::getInstance().getBlock(internal), blk,
            isDefault);
    }

    data::AbstractBlockData *version::BlockIO::convertBlockFromInternal(
        const lodestone::level::block::instance::BlockInstance *b) {
        if (const auto it = m_fromInternalConversionMap.find(b->getBlock());
            it != m_fromInternalConversionMap.end())
            return it->second;

        return nullptr;
    }

    level::block::instance::BlockInstance
    version::BlockIO::convertBlockToInternal(const data::AbstractBlockData &b) {
        if (const auto it = m_toInternalConversionMap.find(&b);
            it !=
            m_toInternalConversionMap.end()) { // because we hash by value this
                                              // should theoretically work
            // if we have block ID with state in conversion map, return it
            return level::block::instance::BlockInstance(it->second);
        }

#ifdef USE_FALLBACK_BLOCK
        return *level::block::instance::ImmutableBlockInstance::getInstance();
#else
        throw std::runtime_error(
            std::format("Could not find block {}", b.toString()));
#endif
    }
} // namespace lodestone::conversion::block
