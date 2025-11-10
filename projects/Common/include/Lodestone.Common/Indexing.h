//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_INDEXING_H
#define LODESTONE_INDEXING_H

namespace lodestone::level {
#define INDEX_YZX(x, y, z, w, d) (y * d + z) * w + x
#define INDEX_XZY(x, y, z, h, d) (x * d + z) * h + y
#define INDEX_YX(x, y, w) y * w + x
#define INDEX_XY(x, y, h) x * h + y

#define BLOCK_IDX_TO_CHUNK_IDX(i) ((i + (constants::CHUNK_WIDTH - 1)) / constants::CHUNK_WIDTH)
}

#endif // LODESTONE_INDEXING_H