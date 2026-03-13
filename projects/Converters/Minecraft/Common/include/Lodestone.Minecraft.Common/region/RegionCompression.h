//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#ifndef LODESTONE_REGIONCOMPRESSION_H
#define LODESTONE_REGIONCOMPRESSION_H

namespace lodestone::minecraft::common::region {
    enum RegionCompression : signed char {
        GZIP = 1,
        ZLIB = 2,
        UNCOMPRESSED = 3,
        LZ4 = 4,
        CUSTOM = std::numeric_limits<int8_t>::max()
    };
}

#endif // LODESTONE_REGIONCOMPRESSION_H