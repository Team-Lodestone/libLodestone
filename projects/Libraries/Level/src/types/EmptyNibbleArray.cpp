//
// Created by Zero on 11/25/25.
//
#include "Lodestone.Level/types/EmptyNibbleArray.h"

namespace lodestone::level::types {
    EmptyNibbleArray * EmptyNibbleArray::getInstance() {
        static EmptyNibbleArray sInstance;
        return &sInstance;
    }

    int EmptyNibbleArray::getIndex(int x, int y, int z) const {
        return 0;
    }

    int EmptyNibbleArray::getNibble(int x, int y, int z) const {
        return 0;
    }

    void EmptyNibbleArray::setNibble(const int x, const int y, const int z, const int value) {}
} // namespace lodestone::level::types