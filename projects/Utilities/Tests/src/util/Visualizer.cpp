/** @file Visualizer.cpp
 *
 * @author DexrnZacAttack
 * @date 4/8/26
 * 
 * @device zPc-i2
 */
#include "Lodestone.Tests/util/Visualizer.h"

namespace lodestone::tests::util {
    std::filesystem::path Visualizer::getDirectory(const level::world::World *world, const common::registry::Identifier &levelType) {
        std::filesystem::path worldPath = OUTPUT_FOLDER / std::format("maps/{}", world->getName());
        worldPath.make_preferred();

        auto levelPath = std::filesystem::path(levelType.getNamespace()) / levelType.getPath();
        levelPath.make_preferred();

        return worldPath / levelPath;
    }

    uint8_t * Visualizer::generateMap(const level::Level *l) {
        auto [min, max] = l->getBlockBounds();

        const signed_size_t w = max.x - min.x + 1;
        const signed_size_t d = max.z - min.z + 1;
        uint8_t *pixels = new uint8_t[(w * d) * 3];

        for (signed_size_t z = min.z; z <= max.z; ++z) {
            for (signed_size_t x = min.x; x <= max.x; ++x) {
                const int16_t height = l->getHeightAt(x, z);
                const level::block::instance::BlockInstance &block = l->getBlockAtHeight(x, z);

                const level::material::Material &m = block.getBlock()->getMaterial();
                const level::types::Color &col = m.getColor();

                float r = col.r;
                float g = col.g;
                float b = col.b;

                const int16_t nextHeight = l->getHeightAt(x, z - 1);
                if (height < nextHeight) {
                    r *= 0.75;
                    g *= 0.75;
                    b *= 0.75;
                } else if (height > nextHeight) {
                    r *= 1.25;
                    g *= 1.25;
                    b *= 1.25;
                }

                const int pixelX = x + -min.x;
                const int pixelY = max.z - z;

                pixels[(pixelY * w + pixelX) * 3 + 2] = std::floor(r);
                pixels[(pixelY * w + pixelX) * 3 + 1] = std::floor(g);
                pixels[(pixelY * w + pixelX) * 3 + 0] = std::floor(b);
                // arr[(x+y*w)*4 + 3] = 0xff;
            }
        }

        return pixels;
    }

    int16_t * Visualizer::getHeightmap(const level::Level *l) {
        auto [min, max] = l->getBlockBounds();

        const int w = max.x - min.x + 1;
        const int d = max.z - min.z + 1;
        auto arr = new int16_t[w * d];

        for (int z = min.z; z <= max.z; ++z) {
            for (int x = min.x; x <= max.x; ++x) {
                const int idxX = x + -min.x;
                const int idxY = max.z - z;

                arr[idxY * w + idxX] = l->getHeightAt(x, z);
            }
        }

        return arr;
    }

    void Visualizer::createMap(level::world::World *world) {
        for (const auto &[id, level] : world->getLevels()) {
            auto [min, max] = level->getBlockBounds();

            const int w = max.x - min.x + 1;
            const int d = max.z - min.z + 1;

            TgaHeader h = {
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

            auto dir = getDirectory(world, id);
            std::filesystem::create_directories(dir);

            std::filesystem::path file = dir / "map.tga";

            // Oxygen... *bwoomp bwoomp* Oxygen...
            std::ofstream o2(file, std::ios::binary);
            o2.write(reinterpret_cast<const char *>(&h),
                     sizeof(TgaHeader));
            o2.write(reinterpret_cast<const char
                         *>(generateMap(level.get())), (w * d) * 3);
            o2.close();
        }
    }

    void Visualizer::createHeightmap(level::world::World *world) {
        for (const auto &[id, level] : world->getLevels()) {
            auto [min, max] = level->getBlockBounds();

            const int w = max.x - min.x + 1;
            const int d = max.z - min.z + 1;

            auto dir = getDirectory(world, id);
            std::filesystem::create_directories(dir);

            std::filesystem::path file = dir / "heightmap.dat";

            std::ofstream o3(file, std::ios::binary);
            o3.write(reinterpret_cast<const char *>(getHeightmap(level.get())), (w * d) * 2);
            o3.close();
        }
    }

    void Visualizer::createAll(level::world::World *world) {
        createHeightmap(world);
        createMap(world);
    }
}