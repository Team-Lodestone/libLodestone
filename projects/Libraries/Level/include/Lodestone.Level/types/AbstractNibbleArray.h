//
// Created by DexrnZacAttack on 11/26/25 using zPc-i2.
//
#ifndef LODESTONE_ABSTRACTNIBBLEARRAY_H
#define LODESTONE_ABSTRACTNIBBLEARRAY_H

namespace lodestone::level::types {
    class AbstractNibbleArray {
      public:
        virtual ~AbstractNibbleArray() = default;

        virtual int getIndex(int x, int y, int z) const = 0;
        virtual int getNibble(int x, int y, int z) const = 0;
        virtual void setNibble(int x, int y, int z, int value) = 0;
    };
} // namespace lodestone::level::types

#endif // LODESTONE_ABSTRACTNIBBLEARRAY_H
