//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#ifndef LODESTONE_BLOCKS_H
#define LODESTONE_BLOCKS_H
#include "Block.h"
#include "Defines.h"

namespace lodestone::level::block {
    class LODESTONE_API Blocks {
    public:
        static const Block AIR;
        static const Block STONE;
        static const Block GRASS;
        static const Block DIRT;
    };

    extern const Block *gBlocks;
}

#endif //LODESTONE_BLOCKS_H