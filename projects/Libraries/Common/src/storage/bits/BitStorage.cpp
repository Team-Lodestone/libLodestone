//
// Created by Zero on 11/25/25.
//

#include "Lodestone.Common/storage/bits/BitStorage.h"

namespace lodestone::common::storage::bits {
    BitStorage::BitStorage(const unsigned int length, const unsigned int bits) : m_data(new uint8_t[length >> 1]{}), m_bitWidth(bits), m_owned(true) {}

    BitStorage::BitStorage(uint8_t *data, const unsigned int bits) : m_data(data), m_bitWidth(bits), m_owned(false) {}

    BitStorage::~BitStorage() { if (m_owned) delete[] this->m_data; }

    int BitStorage::getIndex(const unsigned int x, const unsigned int y, const unsigned int z) const {
        return y << (this->m_bitWidth + 4) | z << this->m_bitWidth | x;
    }

    int BitStorage::getNibble(const unsigned int x, const unsigned int y, const unsigned int z) const {
        const int index = getIndex(x, y, z);

        if ((index & 1) == 0) {
            return this->m_data[index >> 1] & 0xF;
        }

        return this->m_data[index >> 1] >> this->m_bitWidth & 0xF;
    }

    void BitStorage::setNibble(const unsigned int x, const unsigned int y, const unsigned int z,
                                const unsigned int value) {
        const int index = getIndex(x, y, z);

        // Mask is equivalent to dividing by 2 (2 nibbles per byte)
        const int mask = index >> 1;
        if ((index & 1) == 0) {
            this->m_data[mask] = this->m_data[mask] & 0xF0 | value & 0xF;
        }
        this->m_data[mask] = this->m_data[mask] & 0xF | (value & 0xF)
                                                          << this->m_bitWidth;
    }

} // namespace lodestone::level::types