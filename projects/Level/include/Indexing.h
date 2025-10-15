//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_INDEXING_H
#define LODESTONE_INDEXING_H

namespace lodestone::level {
    #define INDEX_YZX(x, y, z, w, d) (y * d + z) * w + x
}

#endif // LODESTONE_INDEXING_H