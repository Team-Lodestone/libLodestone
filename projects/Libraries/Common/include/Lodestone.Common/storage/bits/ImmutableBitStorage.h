//
// Created by Zero on 11/25/25.
//
#ifndef LODESTONE_IMMUTABLEBITSTORAGE_H
#define LODESTONE_IMMUTABLEBITSTORAGE_H
#include "Lodestone.Common/storage/bits/AbstractBitStorage.h"

namespace lodestone::common::storage::bits {
    class ImmutableBitStorage : public AbstractBitStorage {
      protected:
        ImmutableBitStorage() = default;

      public:
        static ImmutableBitStorage *getInstance();

        int getIndex(unsigned int x, unsigned int y, unsigned int z) const override;
        int getNibble(unsigned int x, unsigned int y, unsigned int z) const override;
        void setNibble(unsigned int x, unsigned int y, unsigned int z, unsigned int value) override;
    };
} // namespace lodestone::level::types

#endif // LODESTONE_IMMUTABLEBITSTORAGE_H