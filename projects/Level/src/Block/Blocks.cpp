#include "Block/Blocks.h"
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
namespace lodestone::level::block {
    const Block Blocks::AIR = Block{0, material::Material({0, 0, 0, 0})};

    const Block *gBlocks = {
        &Blocks::AIR
    };
}