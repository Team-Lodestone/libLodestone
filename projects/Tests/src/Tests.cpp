#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <format>
#include <ranges>

#include <Lodestone.Common/Lodestone.h>
#include <Lodestone.Java/LodestoneJava.h>
#include <Lodestone.Level/Block/BlockRegistry.h>
#include <Lodestone.Level/Chunk/Chunk.h>
#include <Lodestone.Level/Chunk/LevelChunk.h>
#include <Lodestone.Level/Conversion/Level/LevelIORegistry.h>
#include <Lodestone.Java/Classic/ClassicBlockIO.h>
#include <Lodestone.Level/Indexing.h>
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//

// Minecraft-style map image generator made by a friend who does not wish to be named
uint8_t *generateMap(lodestone::level::Level *l) {
    auto [min, max] = l->getBlockBounds();

    const int w = max.x - min.x + 1;
    const int d = max.z - min.z + 1;
    uint8_t *arr = new uint8_t[(w * d) * 3];

    for (int y = 0; y < d; ++y) {
        for (int x = 0; x < w; ++x) {
            const int16_t h = l->getHeightAt(x, y);
            const lodestone::level::material::Material &m = l->getBlockmapBlockAt(x, y)->getBlock()->getMaterial();
            const lodestone::level::types::Color &col = m.getColor();

            float r = col.r;
            float g = col.g;
            float b = col.b;

            if (y > 0) { // this might break the top row of pixels, but it prevents us from going OOB until I fix
                const int16_t nh = l->getHeightAt(x, y - 1);
                if (h < nh) {
                    r *= 0.75;
                    g *= 0.75;
                    b *= 0.75;
                } else if (h > nh) {
                    r *= 1.25;
                    g *= 1.25;
                    b *= 1.25;
                }
            }

            arr[(x+y*w)*3 + 2] = std::floor(r);
            arr[(x+y*w)*3 + 1] = std::floor(g);
            arr[(x+y*w)*3 + 0] = std::floor(b);
            // arr[(x+y*w)*4 + 3] = 0xff;
        }
    }

    return arr;
}

// http://www.paulbourke.net/dataformats/tga/ temp for writing map tga
#pragma pack(push, 1)
typedef struct {
    char  idlength;
    char  colourmaptype;
    char  datatypecode;
    short int colourmaporigin;
    short int colourmaplength;
    char  colourmapdepth;
    short int x_origin;
    short int y_origin;
    const short width;
    const short height;
    char  bitsperpixel;
    char  imagedescriptor;
} HEADER __attribute__((packed));
#pragma pack(pop)

// TODO: proper test framework, probably based off of libLCE's (I made libLCE)
int main() {
    std::cout << lodestone::lodestone_get_library_string() << std::endl;

    lodestone_java_init();

    for (const auto &i: lodestone::level::block::BlockRegistry::sInstance | std::views::keys) {
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
    auto startTime = std::chrono::high_resolution_clock::now();
    lodestone::level::Level *level = l->read(b.data());
    const std::chrono::duration<double, std::milli> duration =
                std::chrono::high_resolution_clock::now() - startTime;

    std::cout << "finished after "
              << duration.count() << "ms" << std::endl;

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

    std::filesystem::create_directories("heightmaps/bitmaps");

    for (auto &[coords, chunk] : level->getChunks()) {
        std::ofstream o(std::format("heightmaps/{}.{}.out", coords.x, coords.z), std::ios::binary);
        o.write(reinterpret_cast<const char*>(chunk->getHeightmap()), (lodestone::constants::CHUNK_WIDTH * lodestone::constants::CHUNK_DEPTH) * 2);
        o.close();
    }

    auto [min, max] = level->getBlockBounds();

    const int w = max.x - min.x + 1;
    const int d = max.z - min.z + 1;

    // Oxygen... *bwoomp bwoomp* Oxygen...
    std::ofstream o2(std::format("heightmaps/bitmaps/level.tga"), std::ios::binary);
    HEADER h = {
        0,
        0,
        2,
        0,
        0,
        0,
        0,
        0,
        static_cast<short>(w),
        static_cast<short>(d),
        24,
        0
    };
    o2.write(reinterpret_cast<const char*>(&h), sizeof(HEADER));
    o2.write(reinterpret_cast<const char*>(generateMap(level)), (w * d) * 3);
    o2.close();

    return 0;
}