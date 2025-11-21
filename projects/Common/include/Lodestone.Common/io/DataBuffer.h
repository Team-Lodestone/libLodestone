//
// Created by DexrnZacAttack on 11/8/25 using zPc-i2.
//
#ifndef LODESTONE_DATABUFFER_H
#define LODESTONE_DATABUFFER_H
#include <cstdint>
#include <iosfwd>
#include <streambuf>

namespace lodestone::common::io {
    class DataBuffer final : public std::streambuf {
      public:
        DataBuffer(uint8_t *data, size_t size);
    };
} // namespace lodestone::common::io

#endif // LODESTONE_DATABUFFER_H
