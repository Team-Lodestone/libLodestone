//
// Created by Zero on 11/25/25.
//

#include "Lodestone.Level/types/NibbleArray.h"

namespace lodestone::level::types {

    NibbleArray::NibbleArray(const int length, const int bits) {
        this->mData = new uint8_t[length >> 1]{};
        this->mBits = bits;
    }

    NibbleArray::NibbleArray(uint8_t *data,
                             const int bits) {
        this->mData = data;
        this->mBits = bits;
    }

    NibbleArray::~NibbleArray() {
        delete this->mData;
    }

    int NibbleArray::getIndex(const int x, const int y, const int z) const {
        return y << (this->mBits + 4) | z << this->mBits | x;
    }

    int NibbleArray::getNibble(const int x, const int y, const int z) const {
        const int index = getIndex(x, y, z);

        if ((index & 1) == 0) {
            return this->mData[index >> 1] & 0xF;
        }

        return this->mData[index >> 1] >> this->mBits & 0xF;
    }

    void NibbleArray::setNibble(const int x, const int y, const int z,
                                const int value) {
        const int index = getIndex(x, y, z);

        // Mask is equivalent to dividing by 2 (2 nibbles per byte)
        const int mask = index >> 1;
        if ((index & 1) == 0) {
            this->mData[mask] = this->mData[mask] & 0xF0 | value & 0xF;
        }
        this->mData[mask] = this->mData[mask] & 0xF | (value & 0xF)
                                                        << this->mBits;
    }

} // namespace lodestone::level::types