//
// Created by Zero on 11/25/25.
//
#ifndef LODESTONE_EMPTYNIBBLEARRAY_H
#define LODESTONE_EMPTYNIBBLEARRAY_H
#include "Lodestone.Level/types/NibbleArray.h"

namespace lodestone::level::types {
    class EmptyNibbleArray : public AbstractNibbleArray {
      protected:
        EmptyNibbleArray() = default;

      public:
        static EmptyNibbleArray *getInstance();

        int getIndex(int x, int y, int z) const override;
        int getNibble(int x, int y, int z) const override;
        void setNibble(int x, int y, int z, int value) override;
    };
} // namespace lodestone::level::types

#endif // LODESTONE_EMPTYNIBBLEARRAY_H