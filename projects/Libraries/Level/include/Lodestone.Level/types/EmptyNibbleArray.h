//
// Created by Zero on 11/25/25.
//
#ifndef LODESTONE_EMPTYNIBBLEARRAY_H
#define LODESTONE_EMPTYNIBBLEARRAY_H
#include "Lodestone.Level/types/NibbleArray.h"

namespace lodestone::level::types {
    class EmptyNibbleArray : public NibbleArray {
      public:
        EmptyNibbleArray(const int length, const int bits)
            : NibbleArray(length, bits) {}

      private:
        int getNibble(int x, int y, int z);
        void setNibble(int x, int y, int z, int value);
    };
} // namespace lodestone::level::types

#endif // LODESTONE_EMPTYNIBBLEARRAY_H