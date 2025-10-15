#include "Block/Blocks.h"
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
namespace lodestone::level::block {
    Blocks *Blocks::sInstance = new Blocks();
    const Block *Blocks::sDefaultBlock = Blocks::sInstance->getBlock("lodestone:air");

    Blocks::Blocks() {
    }
}
