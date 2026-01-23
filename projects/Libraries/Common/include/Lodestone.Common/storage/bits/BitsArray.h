//
// Created by Zero on 11/25/25.
//

#ifndef LODESTONE_NIBBLEARRAY_H
#define LODESTONE_NIBBLEARRAY_H
#include <cstdint>

#include "Lodestone.Common/storage/bits/AbstractBitsArray.h"

namespace lodestone::common::storage::bits {

    class BitsArray : public AbstractBitsArray {
      public:
        BitsArray(int length, int bits);
        BitsArray(uint8_t *data, int bits);
        ~BitsArray() override;

        int getIndex(int x, int y, int z) const override;
        int getNibble(int x, int y, int z) const override;
        void setNibble(int x, int y, int z, int value) override;

      private:
        /**
         * Indexed by YZX
         */
        uint8_t *mData;

        int mBits;
    };

} // namespace lodestone::level::types

#endif // LODESTONE_NIBBLEARRAY_H
