//
// Created by Zero on 11/25/25.
//
#ifndef LODESTONE_EMPTYNIBBLEARRAY_H
#define LODESTONE_EMPTYNIBBLEARRAY_H
#include "Lodestone.Common/storage/bits/AbstractBitsArray.h"

namespace lodestone::common::storage::bits {
    class ImmutableBitsArray : public AbstractBitsArray {
      protected:
        ImmutableBitsArray() = default;

      public:
        static ImmutableBitsArray *getInstance();

        int getIndex(int x, int y, int z) const override;
        int getNibble(int x, int y, int z) const override;
        void setNibble(int x, int y, int z, int value) override;
    };
} // namespace lodestone::level::types

#endif // LODESTONE_EMPTYNIBBLEARRAY_H