//
// Created by DexrnZacAttack on 11/2/25 using zPc-i2.
//
#include "Lodestone.Conversion/block/VersionedBlockIO.h"

namespace lodestone::conversion::block {
    std::unique_ptr<version::BlockIO>
    version::VersionedBlockIO::getIo(const uint32_t version) {
        std::unique_ptr<BlockIO> io = std::make_unique<BlockIO>();

        // auto auto auto auto
        auto it = mFromInternalConversionMap.upper_bound(version);
        while (it != mFromInternalConversionMap.begin()) {
            --it;
            for (auto &[internal, blk] : it->second) {
                if (blk != nullptr) // if we want to signify block removal we
                                    // can set it to nullptr
                    io->registerBlockIfNotExist(internal, blk);
            }
        }

        return io;
    }
} // namespace lodestone::conversion::block
