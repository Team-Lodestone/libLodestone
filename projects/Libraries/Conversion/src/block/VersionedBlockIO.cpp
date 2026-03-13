//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#include "Lodestone.Conversion/block/VersionedBlockIO.h"

#include <Lodestone.Common/util/Logging.h>

namespace lodestone::conversion::block {
    std::unique_ptr<version::BlockIO>
    version::VersionedBlockIO::getIo(const uint32_t version) {
        std::unique_ptr<BlockIO> io = std::make_unique<BlockIO>();

        // auto auto auto auto
        for (auto it = m_fromInternalConversionMap.lower_bound(version); it != m_fromInternalConversionMap.end(); ++it) {
            for (auto &[internal, blk] : it->second) {
                // if we want to signify block removal we
                // can set it to nullptr
                if (blk != nullptr) {
                    LOG_DEBUG("Registered block '" << blk->toString() << "' ('" << internal->toString() << "') for version " << std::to_string(version));
                    io->registerBlockIfNotExist(internal, blk);
                }
            }
        }

        return io;
    }
} // namespace lodestone::conversion::block
