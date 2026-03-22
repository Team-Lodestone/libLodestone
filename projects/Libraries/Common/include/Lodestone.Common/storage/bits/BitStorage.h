//
// Created by Zero on 11/25/25.
//

#ifndef LODESTONE_BITSTORAGE_H
#define LODESTONE_BITSTORAGE_H
#include <cstdint>

#include "Lodestone.Common/storage/bits/AbstractBitStorage.h"

namespace lodestone::common::storage::bits {

    class LODESTONE_COMMON_API BitStorage : public AbstractBitStorage {
      public:
        BitStorage(unsigned int length, unsigned int bits);
        BitStorage(uint8_t *data, unsigned int bits);
        ~BitStorage() override;

        int getIndex(unsigned int x, unsigned int y, unsigned int z) const override;
        int getNibble(unsigned int x, unsigned int y, unsigned int z) const override;
        void setNibble(unsigned int x, unsigned int y, unsigned int z, unsigned int value) override;

      private:
        /**
         * Indexed by YZX
         */
        uint8_t *m_data;

        const unsigned int m_bitWidth;

        /** Whether we own the array we're storing */
        bool m_owned;
    };

} // namespace lodestone::level::types

#endif // LODESTONE_BITSTORAGE_H
