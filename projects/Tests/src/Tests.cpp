#include <iostream>
#include <ostream>

#include "Block/Blocks.h"
#include "Chunk/Chunk.h"
#include "Chunk/LevelChunk.h"
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
int main() {
    lodestone::level::block::state::BlockState air = lodestone::level::block::Blocks::sInstance->getBlock("lodestone:air");
    air["Hello"] = "h";

    lodestone::level::chunk::Chunk *c = new lodestone::level::chunk::LevelChunk(128);
    std::cout << c->getBlock(0, 0, 0)->getBlock()->toString() << std::endl;

    return 0;
}