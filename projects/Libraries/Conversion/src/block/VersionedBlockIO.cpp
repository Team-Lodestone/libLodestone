//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#include "Lodestone.Conversion/block/VersionedBlockIO.h"

#include <set>
#include <Lodestone.Common/util/Logging.h>

namespace lodestone::conversion::block {
    std::unique_ptr<version::BlockIO>
    version::VersionedBlockIO::getIo(const uint32_t version) {
        std::unique_ptr<BlockIO> io = std::make_unique<BlockIO>();

        const auto it = m_fromInternalConversionMap.upper_bound(version);

        // auto auto auto auto
        // rit
        for (auto rit = std::make_reverse_iterator(it); rit != m_fromInternalConversionMap.rend(); ++rit) {
            for (auto &[internal, blk] : rit->second) {
                if (blk == nullptr) {
                    // Block is removed. Gone... poof to ashes.
                    continue;
                }

                LOG_DEBUG("Registered block '" << blk->toString() << "' ('" << internal->toString() << "') for version " << std::to_string(version));
                io->registerBlockIfNotExist(internal, blk);
            }
        }

        return io;
    }
} // namespace lodestone::conversion::block
