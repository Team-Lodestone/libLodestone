//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_INDEXING_H
#define LODESTONE_INDEXING_H

namespace lodestone::level {
    #define INDEX_YZX(x, y, z, w, d) (y * d + z) * w + x
    #define INDEX_YX(x, y, w) y * w + x
    #define INDEX_XY(x, y, h) x * h + y
}

#endif // LODESTONE_INDEXING_H