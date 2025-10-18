#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <format>

#include <Lodestone.Common/Lodestone.h>
#include <Lodestone.Java/LodestoneJava.h>
#include <Lodestone.Level/Block/BlockRegistry.h>
#include <Lodestone.Level/Chunk/Chunk.h>
#include <Lodestone.Level/Chunk/LevelChunk.h>
#include <Lodestone.Level/Conversion/Level/LevelIORegistry.h>
#include <Lodestone.Java/Classic/ClassicBlockIO.h>
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//

// TODO: proper test framework, probably based off of libLCE's (I made libLCE)
int main() {
    std::cout << lodestone::lodestone_get_library_string() << std::endl;

    lodestone_java_init();

    for (auto &[i,b] : lodestone::level::block::BlockRegistry::sInstance) {
        std::cout << i << std::endl;
    }

    std::ifstream i("minev1.mine", std::ios::binary);
    if (!i) throw std::runtime_error("no exist!!!!!!!");

    i.seekg(0, std::ios::end);
    std::size_t s = i.tellg();
    i.seekg(0, std::ios::beg);

    std::vector<uint8_t> b(s);
    i.read(reinterpret_cast<char*>(b.data()), s);

    const lodestone::level::conversion::level::LevelIO *l = lodestone::level::conversion::level::LevelIORegistry::sInstance.getLevelIO("lodestone:minev1");
    lodestone::level::Level *level = l->read(b.data());

    // lodestone::level::Level *level = new lodestone::level::Level();
    // for (int x = 0; x < 256; x++) {
    //     auto b = lodestone::level::block::state::BlockState("lodestone:dirt");
    //     level->setBlockCreate(b, x, 0, 0);
    // }
    //
    // for (int y = 0; y < 256; y++) {
    //     auto b = lodestone::level::block::state::BlockState("lodestone:stone");
    //     level->setBlockCreate(b, 0, y, 0);
    // }
    //
    // for (int z = 0; z < 256; z++) {
    //     auto b = lodestone::level::block::state::BlockState("lodestone:cobblestone");
    //     level->setBlockCreate(b, 0, 0, z);
    // }

    // std::ofstream o("minev1.mine.out", std::ios::binary);
    // o.write(reinterpret_cast<const char*>(l->write(level)), l->getSize());
    // o.close();

    // const lodestone::level::conversion::level::LevelIO *l2 = lodestone::level::conversion::level::LevelIORegistry::sInstance->getLevelIO("lodestone:minev2");
    // std::ofstream o("minev2.mine.out", std::ios::binary);
    // o.write(reinterpret_cast<const char*>(l2->write(level)), l2->getSize(level));
    // o.close();

    std::filesystem::create_directories("heightmaps");

    for (auto &[coords, chunk] : level->getChunks()) {
        std::ofstream o(std::format("heightmaps/{}.{}.out", coords.x, coords.z), std::ios::binary);
        o.write(reinterpret_cast<const char*>(chunk->getHeightmap()), (lodestone::constants::CHUNK_WIDTH * lodestone::constants::CHUNK_DEPTH) * 2);
        o.close();
    }

    return 0;
}