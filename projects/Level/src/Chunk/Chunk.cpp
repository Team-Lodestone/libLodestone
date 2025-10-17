//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "../../include/Chunk/Chunk.h"

namespace lodestone::level::chunk {
    int Chunk::getBlockHeight() const {
        return getHeight() * constants::SECTION_HEIGHT;
    }
}
