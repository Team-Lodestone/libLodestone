//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#include "DataBuffer.h"

namespace lodestone::common::io {
    DataBuffer::DataBuffer(uint8_t *data, size_t size) {
        setg(reinterpret_cast<char *>(data), reinterpret_cast<char *>(data), reinterpret_cast<char *>(data + size));
    }
}
