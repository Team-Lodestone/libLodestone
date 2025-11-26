//
// Created by DexrnZacAttack on 11/9/25 using zPc-i2.
//
#ifndef LODESTONE_REGIONCOMPRESSION_H
#define LODESTONE_REGIONCOMPRESSION_H

namespace lodestone::minecraft::java::mcregion {
    enum RegionCompression : signed char {
        GZip = 1,
        Zlib = 2,
        Uncompressed = 3,
        LZ4 = 4,
        Custom = 127
    };
}

#endif // LODESTONE_REGIONCOMPRESSION_H