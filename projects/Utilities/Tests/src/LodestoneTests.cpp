#include <Lodestone.Level/Level.h>
#include <Lodestone.Level/chunk/Chunk.h>

#include <Lodestone.Core/loader/NativeExtensionLoader.h>

#include <filesystem>
#include <iostream>
#include <ostream>

#include <Lodestone.Common/LodestoneCommon.h>
#include <Lodestone.Minecraft.Java/LodestoneJava.h>

#include "Lodestone.Tests/tests/MainTests.h"
#include "Lodestone.Tests/util.h"
#include <print>
#include <BinaryIO/Exports.h>
//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//

// uint8_t *generateMap(lodestone::level::chunk::Chunk *c) {
//     uint8_t *arr = new uint8_t[(lodestone::constants::CHUNK_WIDTH *
//                                 lodestone::constants::CHUNK_DEPTH) * 3];
//
//     for (int y = 0; y < lodestone::constants::CHUNK_DEPTH; ++y) {
//         for (int x = 0; x < lodestone::constants::CHUNK_WIDTH; ++x) {
//             const int16_t h = c->getHeightAt(x, y);
//             const lodestone::level::material::Material &m =
//                 c->getBlockmapBlockAt(x, y)->getBlock()->getMaterial();
//             const
//                 lodestone::level::types::Color &col = m.getColor();
//
//             float r = col.r;
//             float g = col.g;
//             float b = col.b;
//
//             if (y > 0) {
//                 // this might break the top row of pixels, but it prevents us
//                 // from going OOB until I fix
//                 const int16_t nh =
//                     c->getHeightAt(x, y - 1);
//                 if (h < nh) {
//                     r *= 0.75;
//                     g *= 0.75;
//                     b *= 0.75;
//                 } else if (h > nh) {
//                     r *= 1.25;
//                     g *= 1.25;
//                     b *= 1.25;
//                 }
//             }
//
//             arr[(x + y * lodestone::constants::CHUNK_WIDTH) * 3 + 2] =
//                 std::floor(r);
//             arr[(x + y * lodestone::constants::CHUNK_WIDTH) *
//                 3 + 1] = std::floor(g);
//             arr[(x + y *
//                  lodestone::constants::CHUNK_WIDTH) * 3 + 0] = std::floor(b);
//             // arr[(x+y*lodestone::constants::CHUNK_WIDTH)*4 + 3] = 0xff;
//         }
//     }
//
//     return arr;
// }

// void createMap(lodestone::level::types::Vec2i coords,
//                lodestone::level::chunk::Chunk *chunk) {
//     const HEADER h = {
//         0,
//         0,
//         2,
//         0,
//         0,
//         0,
//         0,
//         0,
//         static_cast<short>(lodestone::constants::CHUNK_WIDTH),
//         static_cast<short>(lodestone::constants::CHUNK_DEPTH),
//         24,
//         0
//     };
//
//     std::ofstream o3(std::format("heightmaps/bitmaps/{}.{}.tga", coords.x,
//                                  coords.y), std::ios::binary);
//     o3.write(reinterpret_cast<const char
//                  *>(&h), sizeof(HEADER));
//     o3.write(reinterpret_cast<const char
//                  *>(generateMap(chunk)),
//              (lodestone::common::constants::CHUNK_WIDTH *
//               lodestone::common::constants::CHUNK_DEPTH) * 3);
//     o3.close();
// }
//
// void createHeightmap(lodestone::level::types::Vec2i coords, const
//                      lodestone::level::chunk::Chunk *chunk) {
//     std::ofstream o(std::format("heightmaps/{}.{}.out", coords.x, coords.z),
//                     std::ios::binary);
//     o.write(reinterpret_cast<const char
//                 *>(chunk->getBlockmap()),
//             (lodestone::common::constants::CHUNK_WIDTH *
//              lodestone::common::constants::CHUNK_DEPTH) * 2);
//     o.close();
// }

// void generateWorld(lodestone::level::Level *l, const int w, const int h,
// const int d) {
// const std::unique_ptr<lodestone::conversion::block::version::BlockIO> io
// =
//             lodestone::minecraft::java::LodestoneJava::getInstance()->io.getIo(lodestone::minecraft::java::rd131655);
//     for (int x = 0; x < w; x++) {
//         for (int y = 0; y < h; y++) {
//             for (int z = 0; z < d; z++) {
//                 if (x == y && z == y
//                     && x == z && y == z
//                     && y == x && z == x) {
//                     l->setBlockCreate(lodestone::level::block::state::BlockState(
//                                           io->convertBlockToInternal(
//                                           lodestone::conversion::block::data::ClassicBlockData(x))),
//                                           x,
//                                       y, z, h);
//                 } else {
//                     l->setBlockCreate(lodestone::level::block::state::BlockState(
//                                           io->convertBlockToInternal(
//                                           lodestone::conversion::block::data::ClassicBlockData(
//                                                   x + y + z))), x, y, z, h);
//                 }
//             }
//         }
//     }
// }
//

int main(const int argc, char **argv) {
    LOG_INFO(lodestone::common::lodestone_get_library_string());
    LOG_INFO(bio::bio_get_library_string());

    lodestone::core::loader::NativeExtensionLoader l("./extensions", lodestone::core::Lodestone::getInstance());
    l.extensionLoadedEvent += [](const lodestone::core::LodestoneExtension *ext) {
        std::print("Initialized extension '{}' {}\n", ext->getIdentifier(), ext->getVersion().toString());
    };

    l.loadExtension(lodestone::minecraft::java::lodestoneInit);

    std::filesystem::create_directories(lodestone::tests::util::INPUT_FOLDER);
    std::filesystem::create_directories(lodestone::tests::util::OUTPUT_FOLDER);

    auto tfw = tfw::TestFramework::initFromArgs(argc, argv);

    ADD_TESTS(RUN_MAIN_TESTS, lodestone::tests::test::MainTests::add);

    tfw->run();

    return 0;
};