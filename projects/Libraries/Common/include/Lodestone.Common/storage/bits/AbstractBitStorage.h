//
// Created by DexrnZacAttack on 11/26/25 using zPc-i2.
//
#ifndef LODESTONE_ABSTRACTBITSTORAGE_H
#define LODESTONE_ABSTRACTBITSTORAGE_H
#include <cstdlib>

#include "Lodestone.Common/internal/Exports.h"

namespace lodestone::common::storage::bits {
    class LODESTONE_COMMON_API AbstractBitStorage {
      public:
        virtual ~AbstractBitStorage() = default;

        virtual int getIndex(unsigned int x, unsigned int y, unsigned int z) const = 0;
        virtual int getNibble(unsigned int x, unsigned int y, unsigned int z) const = 0;
        virtual void setNibble(unsigned int x, unsigned int y, unsigned int z, unsigned int value) = 0;
    };
} // namespace lodestone::level::types

#endif // LODESTONE_ABSTRACTBITSTORAGE_H
