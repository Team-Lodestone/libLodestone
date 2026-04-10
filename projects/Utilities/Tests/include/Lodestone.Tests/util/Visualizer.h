/** @file Visualizer.h
 *
 * @author DexrnZacAttack
 * @date 4/8/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_VISUALIZER_H
#define LODESTONE_VISUALIZER_H
#include <Lodestone.Level/Level.h>
#include <Lodestone.Level/world/World.h>
#include "Lodestone.Tests/util.h"

#include <cstdint>
#include <fstream>

namespace lodestone::tests::util {
    class Visualizer {
    public:
        // http://www.paulbourke.net/dataformats/tga/ temp for writing map tga
#pragma pack(push, 1)
        struct TgaHeader {
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
        } __attribute__((packed));
#pragma pack(pop)

        static std::filesystem::path getDirectory(const level::world::World *world, const common::registry::Identifier &levelType);

        // Minecraft-style map image generator made by a friend who does not wish to be named
        static uint8_t *generateMap(const level::Level *l);

        static uint8_t *generateHeightmapImage(const level::Level *l);

        static int16_t *getHeightmap(const level::Level *l);

        static void createMap(level::world::World *world);

        static void createHeightmap(level::world::World *world);

        static void createAll(level::world::World *world);
    };
}

#endif // LODESTONE_VISUALIZER_H