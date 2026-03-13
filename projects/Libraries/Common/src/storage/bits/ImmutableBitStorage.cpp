//
// Created by Zero on 11/25/25.
//
#include "Lodestone.Common/storage/bits/ImmutableBitStorage.h"

namespace lodestone::common::storage::bits {
    ImmutableBitStorage *ImmutableBitStorage::getInstance() {
        static ImmutableBitStorage s_instance;
        return &s_instance;
    }

    int ImmutableBitStorage::getIndex(unsigned int x, unsigned int y, unsigned int z) const { return 0; }

    int ImmutableBitStorage::getNibble(unsigned int x, unsigned int y, unsigned int z) const { return 0; }

    void ImmutableBitStorage::setNibble(const unsigned int x, const unsigned int y, const unsigned int z,
                                     const unsigned int value) {}
} // namespace lodestone::level::types