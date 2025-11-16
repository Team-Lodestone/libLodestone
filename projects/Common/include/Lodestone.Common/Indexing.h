//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_INDEXING_H
#define LODESTONE_INDEXING_H

namespace lodestone::common {
#define INDEX_YZX(x, y, z, w, d) (y * d + z) * w + x
#define INDEX_XZY(x, y, z, h, d) (x * d + z) * h + y
#define INDEX_YX(x, y, w) y * w + x
#define INDEX_XY(x, y, h) x * h + y

#define CHUNK_IDX(blk) (blk >> 4)
#define CHUNK_LOCAL_IDX(blk, v) (blk & (v - 1))
}

#endif // LODESTONE_INDEXING_H