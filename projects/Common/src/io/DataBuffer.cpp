//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#include "Lodestone.Common/io/DataBuffer.h"

namespace lodestone::common::io {
    DataBuffer::DataBuffer(uint8_t *data, const size_t size) {
        setg(reinterpret_cast<char *>(data), reinterpret_cast<char *>(data),
             reinterpret_cast<char *>(data + size));
    }
} // namespace lodestone::common::io