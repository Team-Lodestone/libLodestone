//
// Created by Zero on 11/25/25.
//
#include "Lodestone.Level/types/EmptyNibbleArray.h"

namespace lodestone::level::types {
    int EmptyNibbleArray::getNibble(const int x, const int y, const int z) {
        return 0;
    }

    void EmptyNibbleArray::setNibble(const int x, const int y, const int z,
                                     const int value) {}
} // namespace lodestone::level::types