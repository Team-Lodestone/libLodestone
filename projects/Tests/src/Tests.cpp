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
#include <Lodestone.Level/Indexing.h>
#include <Lodestone.Level/Conversion/Block/BlockIO.h>

#include "Lodestone.Java/Version.h"
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//

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

// Minecraft-style map image generator made by a friend who does not wish to be named
uint8_t *generateMap(lodestone::level::Level *l) {
    auto [min, max] = l->getBlockBounds();

    const int w = max.x - min.x + 1;
    const int d = max.z - min.z + 1;
    uint8_t *arr = new uint8_t[(w * d) * 3];

    for (int y = 0; y < d; y++) {
        for (int x = 0; x < w; x++) {
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

int16_t *getHeightmap(lodestone::level::Level *l) {
    auto [min, max] = l->getBlockBounds();

    const int w = max.x - min.x + 1;
    const int d = max.z - min.z + 1;
    int16_t *arr = new int16_t[w * d];

    for (int y = 0; y < d; ++y) {
        for (int x = 0; x < w; ++x) {
           arr[x+y*w] = l->getHeightAt(x, y);
        }
    }

    return arr;
}

// Minecraft-style map image generator made by a friend who does not wish to be named
uint8_t *generateMap(lodestone::level::chunk::Chunk *c) {
    uint8_t *arr = new uint8_t[(lodestone::constants::CHUNK_WIDTH * lodestone::constants::CHUNK_DEPTH) * 3];

    for (int y = 0; y < lodestone::constants::CHUNK_DEPTH; ++y) {
        for (int x = 0; x < lodestone::constants::CHUNK_WIDTH; ++x) {
            const int16_t h = c->getHeightAt(x, y);
            const lodestone::level::material::Material &m = c->getBlockmapBlockAt(x, y)->getBlock()->getMaterial();
            const lodestone::level::types::Color &col = m.getColor();

            float r = col.r;
            float g = col.g;
            float b = col.b;

            if (y > 0) { // this might break the top row of pixels, but it prevents us from going OOB until I fix
                const int16_t nh = c->getHeightAt(x, y - 1);
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

            arr[(x+y*lodestone::constants::CHUNK_WIDTH)*3 + 2] = std::floor(r);
            arr[(x+y*lodestone::constants::CHUNK_WIDTH)*3 + 1] = std::floor(g);
            arr[(x+y*lodestone::constants::CHUNK_WIDTH)*3 + 0] = std::floor(b);
            // arr[(x+y*lodestone::constants::CHUNK_WIDTH)*4 + 3] = 0xff;
        }
    }

    return arr;
}

void createMap(lodestone::level::Level *lvl) {
    auto [min, max] = lvl->getBlockBounds();

    const int w = max.x - min.x + 1;
    const int d = max.z - min.z + 1;

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

    // Oxygen... *bwoomp bwoomp* Oxygen...
    std::ofstream o2(std::format("heightmaps/bitmaps/level.tga"), std::ios::binary);
    o2.write(reinterpret_cast<const char*>(&h), sizeof(HEADER));
    o2.write(reinterpret_cast<const char*>(generateMap(lvl)), (w * d) * 3);
    o2.close();
}

void createHeightmap(lodestone::level::Level *lvl) {
    auto [min, max] = lvl->getBlockBounds();

    const int w = max.x - min.x + 1;
    const int d = max.z - min.z + 1;

    std::ofstream o3(std::format("heightmaps/level.out"), std::ios::binary);
    o3.write(reinterpret_cast<const char*>(getHeightmap(lvl)), (w * d) * 2);
    o3.close();
}

void createMap(lodestone::level::types::Vec2i coords, lodestone::level::chunk::Chunk *chunk) {
    const HEADER h = {
        0,
        0,
        2,
        0,
        0,
        0,
        0,
        0,
        static_cast<short>(lodestone::constants::CHUNK_WIDTH),
        static_cast<short>(lodestone::constants::CHUNK_DEPTH),
        24,
        0
    };

    std::ofstream o3(std::format("heightmaps/bitmaps/{}.{}.tga", coords.x, coords.z), std::ios::binary);
    o3.write(reinterpret_cast<const char*>(&h), sizeof(HEADER));
    o3.write(reinterpret_cast<const char*>(generateMap(chunk)), (lodestone::constants::CHUNK_WIDTH * lodestone::constants::CHUNK_DEPTH) * 3);
    o3.close();
}

void createHeightmap(lodestone::level::types::Vec2i coords, const lodestone::level::chunk::Chunk *chunk) {
    std::ofstream o(std::format("heightmaps/{}.{}.out", coords.x, coords.z), std::ios::binary);
    o.write(reinterpret_cast<const char*>(chunk->getHeightmap()), (lodestone::constants::CHUNK_WIDTH * lodestone::constants::CHUNK_DEPTH) * 2);
    o.close();
}

void generateWorld(lodestone::level::Level *l, const int w, const int h, const int d) {
    for (char x = 0; x < w; x++) {
        for (char y = 0; y < h; y++) {
            for (char z = 0; z < d; z++) {
                if (x == y && x == z
                    && y == x && y == z
                    && z == x && z == y) {
                    // l->setBlockCreate(new lodestone::level::block::state::BlockState(lodestone::java::classic::ClassicBlockIO::sInstance->convertBlockToInternal(x, std::monostate{})), x, y, z, h);
                } else {
                    // l->setBlockCreate(new lodestone::level::block::state::BlockState(lodestone::java::classic::ClassicBlockIO::sInstance->convertBlockToInternal(x +y +z, std::monostate{})), x, y, z, h);

                }
            }
        }
    }
}

// TODO: proper test framework, probably based off of libLCE's (I made libLCE)
int main() {
    std::cout << lodestone::lodestone_get_library_string() << std::endl;

    lodestone::java::LodestoneJava::init();

    std::unique_ptr<lodestone::level::conversion::block::version::BlockIO> io = lodestone::java::LodestoneJava::getInstance()->io.getIo(lodestone::java::Version::rd20090515);
    for (auto [fst, snd] : io->getFromInternalConversionMap()) {
        std::cout << fst << " -> " << static_cast<int>(*static_cast<const uint8_t *>(snd->getId())) << std::endl;
    }

    for (const auto &i: lodestone::level::block::BlockRegistry::sInstance | std::views::keys) {
        std::cout << i << std::endl;
    }

    // for (const auto &i: lodestone::java::LodestoneJava::sIo.getFromInternalConversionMap() | std::views::keys) {
    //     std::cout << "frominternal->name: " << i << std::endl;
    // }
    //
    // for (const auto &i: lodestone::java::LodestoneJava::sIo.getFromInternalConversionMap() | std::views::values) {
    //     std::cout << "frominternal->id: " << i->getId() << std::endl;
    // }
    //
    // for (const auto &i: lodestone::java::LodestoneJava::sIo.getToInternalConversionMap() | std::views::keys) {
    //     std::cout << "tointernal->id: " << i->getId() << std::endl;
    // }
    //
    // for (const auto i: lodestone::java::LodestoneJava::sIo.getDefaultDataMap() | std::views::keys) {
    //     std::cout << "datamap: " << i << std::endl;
    // }
    //
    // std::ifstream i("minev1.mine", std::ios::binary);
    // if (!i) throw std::runtime_error("no exist!!!!!!!");
    //
    // i.seekg(0, std::ios::end);
    // std::size_t s = i.tellg();
    // i.seekg(0, std::ios::beg);
    //
    // std::vector<uint8_t> b(s);
    // i.read(reinterpret_cast<char*>(b.data()), s);
    //
    // const lodestone::level::conversion::level::LevelIO *l = lodestone::level::conversion::level::LevelIORegistry::sInstance.getLevelIO({ "lodestone", "minev1" });
    // auto startTime = std::chrono::high_resolution_clock::now();
    // // lodestone::level::Level *level = l->read(b.data());
    // const std::chrono::duration<double, std::milli> duration =
    //             std::chrono::high_resolution_clock::now() - startTime;
    //
    // std::cout << "finished after "
    //           << duration.count() << "ms" << std::endl;
    //
    // lodestone::level::Level *level = new lodestone::level::Level();
    // generateWorld(level, 49, 49, 49);
    //
    // // lodestone::level::Level *level = new lodestone::level::Level();
    // // for (int x = 0; x < 256; x++) {
    // //     auto b = lodestone::level::block::state::BlockState({ "lodestone", "dirt" });
    // //     level->setBlockCreate(b, x, 0, 0);
    // // }
    // //
    // // for (int y = 0; y < 256; y++) {
    // //     auto b = lodestone::level::block::state::BlockState({ "lodestone", "stone" });
    // //     level->setBlockCreate(b, 0, y, 0);
    // // }
    // //
    // // for (int z = 0; z < 256; z++) {
    // //     auto b = lodestone::level::block::state::BlockState({ "lodestone", "cobblestone" });
    // //     level->setBlockCreate(b, 0, 0, z);
    // // }
    //
    // const lodestone::level::conversion::level::LevelIO *l2 = lodestone::level::conversion::level::LevelIORegistry::sInstance.getLevelIO({ "lodestone", "minev2" });
    // std::ofstream o("minev2.mine.out", std::ios::binary);
    // o.write(reinterpret_cast<const char*>(l2->write(level)), l2->getSize(level));
    // o.close();
    //
    // std::filesystem::create_directories("heightmaps/bitmaps");
    //
    // createHeightmap(level);
    // createMap(level);
    //
    // for (auto &[coords, chunk] : level->getChunks()) {
    //     createHeightmap(coords, chunk.get());
    //     createMap(coords, chunk.get());
    // }
    //
    // // std::ofstream o("minev1.mine.out", std::ios::binary);
    // // o.write(reinterpret_cast<const char*>(l->write(level)), l->getSize(level));
    // // o.close();

    return 0;
}