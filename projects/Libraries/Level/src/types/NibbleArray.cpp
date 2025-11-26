//
// Created by Zero on 11/25/25.
//

#include "Lodestone.Level/types/NibbleArray.h"

namespace lodestone::level::types {

    NibbleArray::NibbleArray(const int length, const int bits) {
        this->data = std::vector<unsigned char>(length >> 1);
        this->mBits = bits;
    }

    NibbleArray::NibbleArray(const std::vector<unsigned char> &data,
                             const int bits) {
        this->data = data;
        this->mBits = bits;
    }

    NibbleArray::~NibbleArray() { this->data.clear(); }

    int NibbleArray::getIndex(const int x, const int y, const int z) const {
        return y << (this->mBits + 4) | z << this->mBits | x;
    }

    int NibbleArray::getNibble(const int x, const int y, const int z) const {
        const int index = getIndex(x, y, z);

        if ((index & 1) == 0) {
            return this->data[index >> 1] & 0xF;
        }
        return this->data[index >> 1] >> this->mBits & 0xF;
    }

    void NibbleArray::setNibble(const int x, const int y, const int z,
                                const int value) {
        const int index = getIndex(x, y, z);

        // Mask is equivalent to dividing by 2 (2 nibbles per byte)
        const int mask = index >> 1;
        if ((index & 1) == 0) {
            this->data[mask] = this->data[mask] & 0xF0 | value & 0xF;
        }
        this->data[mask] = this->data[mask] & 0xF | (value & 0xF)
                                                        << this->mBits;
    }

} // namespace lodestone::level::types