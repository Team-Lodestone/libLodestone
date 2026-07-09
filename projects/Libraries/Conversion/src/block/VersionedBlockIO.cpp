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

        // auto auto auto auto
        auto upper = m_fromInternalConversionMap.upper_bound(version);
        auto it = std::make_reverse_iterator(upper);
        auto rend = m_fromInternalConversionMap.rend();

        //so that if we process a block (e.g. added it, or removed it) for a version, it doesnt get processed again
        std::set<const lodestone::common::registry::Identifier*> processed;

        for (; it != rend; ++it) {
            for (auto &[internal, blk] : it->second) {
                if (processed.find(internal) == processed.end()) {
                    processed.insert(internal);

                    // if we want to signify block removal we
                    // can set it to nullptr
                    if (blk != nullptr) {
                        LOG_DEBUG("Registered block '" << blk->toString() << "' ('" << internal->toString() << "') for version " << std::to_string(version));
                        io->registerBlockIfNotExist(internal, blk);
                    }
                }
            }
        }

        return io;
    }
} // namespace lodestone::conversion::block
