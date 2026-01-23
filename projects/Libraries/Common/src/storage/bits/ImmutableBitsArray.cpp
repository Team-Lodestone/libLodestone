//
// Created by Zero on 11/25/25.
//
#include "Lodestone.Common/storage/bits/ImmutableBitsArray.h"

namespace lodestone::common::storage::bits {
    ImmutableBitsArray *ImmutableBitsArray::getInstance() {
        static ImmutableBitsArray sInstance;
        return &sInstance;
    }

    int ImmutableBitsArray::getIndex(int x, int y, int z) const { return 0; }

    int ImmutableBitsArray::getNibble(int x, int y, int z) const { return 0; }

    void ImmutableBitsArray::setNibble(const int x, const int y, const int z,
                                     const int value) {}
} // namespace lodestone::level::types