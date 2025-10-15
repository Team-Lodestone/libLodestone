#include <iostream>
#include <ostream>

#include "Block/Blocks.h"
#include "Block/BlockState.h"
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
int main() {
    lodestone::level::block::BlockState air = lodestone::level::block::Blocks::sInstance->getBlock("lodestone:air");
    air["Hello"] = "h";

    return 0;
}