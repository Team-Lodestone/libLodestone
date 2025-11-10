#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <format>
#include <ranges>

#include <Lodestone.Common/Lodestone.h>
#include <Lodestone.Java/LodestoneJava.h>
#include <Lodestone.Level/block/BlockRegistry.h>
#include <Lodestone.Level/chunk/Chunk.h>
#include <Lodestone.Level/chunk/LevelChunk.h>
#include <Lodestone.Level/conversion/level/LevelIORegistry.h>
#include <Lodestone.Common/Indexing.h>
#include <Lodestone.Level/conversion/block/BlockIO.h>

#include "Lodestone.Tests/util.h"
#include <BinaryIO/Exports.h>
#include <Lodestone.Common/io/DataBuffer.h>
#include <Lodestone.Java/Version.h>
#include <Lodestone.Java/classic/minev2/MineV2World.h>
#include <Lodestone.Level/conversion/block/data/ClassicBlockData.h>
#include <Lodestone.Level/conversion/world/FileWorldIo.h>
#include <Lodestone.Level/conversion/world/WorldIORegistry.h>
#include "Lodestone.Tests/tests/MainTests.h"
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//

// http://www.paulbourke.net/dataformats/tga/ temp for writing map tga
#pragma pack(push, 1)
typedef struct {
    char idlength;
    char colourmaptype;
    char datatypecode;
    short int colourmaporigin;
    short int colourmaplength;
    char colourmapdepth;
    short int x_origin;
    short int y_origin;
    const short width;
    const short height;
    char bitsperpixel;
    char imagedescriptor;
}

HEADER __attribute__((packed));
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

            if (y > 0) {
                // this might break the top row of pixels, but it prevents us from going OOB until I fix
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

            arr[(x + y * w) * 3 + 2] = std::floor(r);
            arr[(x + y * w) * 3 + 1] = std::floor(g);
            arr[(x + y * w) * 3 + 0] = std::floor(b);
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
            arr[x + y * w] = l->getHeightAt(x, y);
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

            if (y > 0) {
                // this might break the top row of pixels, but it prevents us from going OOB until I fix
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

            arr[(x + y * lodestone::constants::CHUNK_WIDTH) * 3 + 2] = std::floor(r);
            arr[(x + y * lodestone::constants::CHUNK_WIDTH) * 3 + 1] = std::floor(g);
            arr[(x + y * lodestone::constants::CHUNK_WIDTH) * 3 + 0] = std::floor(b);
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
    o2.write(reinterpret_cast<const char *>(&h), sizeof(HEADER));
    o2.write(reinterpret_cast<const char *>(generateMap(lvl)), (w * d) * 3);
    o2.close();
}

void createHeightmap(lodestone::level::Level *lvl) {
    auto [min, max] = lvl->getBlockBounds();

    const int w = max.x - min.x + 1;
    const int d = max.z - min.z + 1;

    std::ofstream o3(std::format("heightmaps/level.out"), std::ios::binary);
    o3.write(reinterpret_cast<const char *>(getHeightmap(lvl)), (w * d) * 2);
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
    o3.write(reinterpret_cast<const char *>(&h), sizeof(HEADER));
    o3.write(reinterpret_cast<const char *>(generateMap(chunk)),
             (lodestone::constants::CHUNK_WIDTH * lodestone::constants::CHUNK_DEPTH) * 3);
    o3.close();
}

void createHeightmap(lodestone::level::types::Vec2i coords, const lodestone::level::chunk::Chunk *chunk) {
    std::ofstream o(std::format("heightmaps/{}.{}.out", coords.x, coords.z), std::ios::binary);
    o.write(reinterpret_cast<const char *>(chunk->getHeightmap()),
            (lodestone::constants::CHUNK_WIDTH * lodestone::constants::CHUNK_DEPTH) * 2);
    o.close();
}

void generateWorld(lodestone::level::Level *l, const int w, const int h, const int d) {
    std::unique_ptr<lodestone::level::conversion::block::version::BlockIO> io =
            lodestone::java::LodestoneJava::getInstance()->io.getIo(lodestone::java::caveGame);
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            for (int z = 0; z < d; z++) {
                if (x == y && z == y
                    && x == z && y == z
                    && y == x && z == x) {
                    l->setBlockCreate(new lodestone::level::block::state::BlockState(
                                          io->convertBlockToInternal(
                                              new lodestone::level::conversion::block::data::ClassicBlockData(x))), x,
                                      y, z, h);
                } else {
                    l->setBlockCreate(new lodestone::level::block::state::BlockState(
                                          io->convertBlockToInternal(
                                              new lodestone::level::conversion::block::data::ClassicBlockData(
                                                  x + y + z))), x, y, z, h);
                }
            }
        }
    }
}

// TODO: proper test framework, probably based off of libLCE's (I made libLCE)
int mainOld() {
    std::cout << lodestone::lodestone_get_library_string() << std::endl;

    lodestone::java::LodestoneJava::init();

    std::unique_ptr<lodestone::level::conversion::block::version::BlockIO> io =
            lodestone::java::LodestoneJava::getInstance()->io.getIo(lodestone::java::Version::rd20090515);
    for (auto [fst, snd]: io->getFromInternalConversionMap()) {
        std::cout << fst << " -> " << static_cast<int>(*static_cast<const uint8_t *>(snd->getIdPtr())) << std::endl;
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
    lodestone::level::Level *level = new lodestone::level::Level();
    generateWorld(level, 48, 48, 48);

    // for (int x = 0; x < 48; x++) {
    //     auto b = lodestone::level::block::state::BlockState(lodestone::level::block::Blocks::DIRT);
    //     level->setBlockCreate(&b, x, 0, 0);
    // }
    //
    // for (int y = 0; y < 48; y++) {
    //     auto b = lodestone::level::block::state::BlockState(lodestone::level::block::Blocks::STONE);
    //     level->setBlockCreate(&b, 0, y, 0);
    // }
    //
    // for (int z = 0; z < 48; z++) {
    //     auto b = lodestone::level::block::state::BlockState(lodestone::level::block::Blocks::COBBLESTONE);
    //     level->setBlockCreate(&b, 0, 0, z);
    // }

    const lodestone::level::conversion::world::FileWorldIO *l2 = dynamic_cast<const
        lodestone::level::conversion::world::FileWorldIO *>(
        lodestone::level::conversion::world::WorldIORegistry::sInstance.getWorldIO({"lodestone", "minev2"}));
    std::ofstream o("minev2.mine.out", std::ios::binary);
    lodestone::java::classic::minev2::MineV2World *w = new lodestone::java::classic::minev2::MineV2World(
        std::unique_ptr<lodestone::level::Level>(level), "New World", "h");
    o.write(reinterpret_cast<const char *>(l2->write(w, lodestone::java::caveGame)),
            l2->getSize(w, lodestone::java::caveGame));
    o.close();

    std::filesystem::create_directories("heightmaps/bitmaps");

    createHeightmap(level);
    createMap(level);

    for (auto &[coords, chunk]: level->getChunks()) {
        createHeightmap(coords, chunk.get());
        createMap(coords, chunk.get());
    }

    // std::ofstream o("minev1.mine.out", std::ios::binary);
    // o.write(reinterpret_cast<const char*>(l->write(level)), l->getSize(level));
    // o.close();

    return 0;
}

int main(int argc, char **argv) {
    std::cout << lodestone::lodestone_get_library_string() << std::endl;
    std::cout << bio::bio_get_library_string() << std::endl;

    lodestone::java::LodestoneJava::init();

    std::filesystem::create_directories(lodestone::tests::util::INPUT_FOLDER);
    std::filesystem::create_directories(lodestone::tests::util::OUTPUT_FOLDER);

    ADD_TESTS(RUN_MAIN_TESTS, lodestone::tests::test::MainTests::run);

    return 0;
};