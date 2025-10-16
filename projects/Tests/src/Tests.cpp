#include <fstream>
#include <iostream>
#include <ostream>

#include "Main.h"
#include "Block/Blocks.h"
#include "Chunk/Chunk.h"
#include "Chunk/LevelChunk.h"
#include "Conversion/Level/LevelIORegistry.h"
#include "Classic/ClassicBlockIo.h"
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//

// TODO: proper test framework, probably based off of libLCE's (I made libLCE)
int main() {
    lodestone_java_init();

    std::ifstream i("minev1.mine", std::ios::binary);
    if (!i) throw std::runtime_error("no exist!!!!!!!");

    i.seekg(0, std::ios::end);
    std::size_t s = i.tellg();
    i.seekg(0, std::ios::beg);

    std::vector<uint8_t> b(s);
    i.read(reinterpret_cast<char*>(b.data()), s);

    const lodestone::level::conversion::level::LevelIO *l = lodestone::level::conversion::level::LevelIORegistry::sInstance->getLevelIO("lodestone:minev1");
    lodestone::level::Level *level = l->read(b.data());

    std::ofstream o("minev1.mine.out", std::ios::binary);
    o.write(reinterpret_cast<const char*>(l->write(level)), l->getSize());
    o.close();

    return 0;
}