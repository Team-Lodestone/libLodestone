//
// Created by Zero on 11/25/25.
//

#ifndef LODESTONE_NIBBLEARRAY_H
#define LODESTONE_NIBBLEARRAY_H
#include <cstdint>

#include "Lodestone.Level/types/AbstractNibbleArray.h"

namespace lodestone::level::types {

    class NibbleArray : public AbstractNibbleArray {
      public:
        NibbleArray(int length, int bits);
        NibbleArray(uint8_t *data, int bits);
        ~NibbleArray() override;

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
