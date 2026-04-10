/** @file Materials.h
 *
 * @author DexrnZacAttack
 * @date 4/8/26
 * 
 * @device zPc-i2
 */
#ifndef LODESTONE_MINECRAFT_COMMON_MATERIALS_H
#define LODESTONE_MINECRAFT_COMMON_MATERIALS_H
#include <Lodestone.Level/material/Material.h>

namespace lodestone::minecraft::common::materials {
    inline constexpr auto NONE = level::material::Material(0, 0, 0, 0);
    inline constexpr auto GRASS = level::material::Material(127, 178, 56);
    inline constexpr auto SAND = level::material::Material(247, 233, 163);
    inline constexpr auto WOOL = level::material::Material(199, 199, 199);
    inline constexpr auto FIRE = level::material::Material(255, 0, 0);
    inline constexpr auto ICE = level::material::Material(160, 160, 255);
    inline constexpr auto METAL = level::material::Material(167, 167, 167);
    inline constexpr auto PLANT = level::material::Material(0, 124, 0);
    inline constexpr auto SNOW = level::material::Material(255, 255, 255);
    inline constexpr auto CLAY = level::material::Material(164, 168, 184);
    inline constexpr auto DIRT = level::material::Material(151, 109, 77);
    inline constexpr auto STONE = level::material::Material(112, 112, 112);
    inline constexpr auto WATER = level::material::Material(64, 64, 255);
    inline constexpr auto WOOD = level::material::Material(143, 119, 72);
    inline constexpr auto QUARTZ = level::material::Material(255, 252, 245);
    inline constexpr auto COLOR_ORANGE = level::material::Material(216, 127, 51);
    inline constexpr auto COLOR_MAGENTA = level::material::Material(178, 76, 216);
    inline constexpr auto COLOR_LIGHT_BLUE = level::material::Material(102, 153, 216);
    inline constexpr auto COLOR_YELLOW = level::material::Material(229, 229, 51);
    inline constexpr auto COLOR_LIGHT_GREEN = level::material::Material(127, 204, 25);
    inline constexpr auto COLOR_PINK = level::material::Material(242, 127, 165);
    inline constexpr auto COLOR_GRAY = level::material::Material(76, 76, 76);
    inline constexpr auto COLOR_LIGHT_GRAY = level::material::Material(153, 153, 153);
    inline constexpr auto COLOR_CYAN = level::material::Material(76, 127, 153);
    inline constexpr auto COLOR_PURPLE = level::material::Material(127, 63, 178);
    inline constexpr auto COLOR_BLUE = level::material::Material(51, 76, 178);
    inline constexpr auto COLOR_BROWN = level::material::Material(102, 76, 51);
    inline constexpr auto COLOR_GREEN = level::material::Material(102, 127, 51);
    inline constexpr auto COLOR_RED = level::material::Material(153, 51, 51);
    inline constexpr auto COLOR_BLACK = level::material::Material(25, 25, 25);
    inline constexpr auto GOLD = level::material::Material(250, 238, 77);
    inline constexpr auto DIAMOND = level::material::Material(92, 219, 213);
    inline constexpr auto LAPIS = level::material::Material(74, 128, 255);
    inline constexpr auto EMERALD = level::material::Material(0, 217, 58);
    inline constexpr auto PODZOL = level::material::Material(129, 86, 49);
    inline constexpr auto NETHER = level::material::Material(112, 2, 0);
    inline constexpr auto TERRACOTTA_WHITE = level::material::Material(209, 177, 161);
    inline constexpr auto TERRACOTTA_ORANGE = level::material::Material(159, 82, 36);
    inline constexpr auto TERRACOTTA_MAGENTA = level::material::Material(149, 87, 108);
    inline constexpr auto TERRACOTTA_LIGHT_BLUE = level::material::Material(112, 108, 138);
    inline constexpr auto TERRACOTTA_YELLOW = level::material::Material(186, 133, 36);
    inline constexpr auto TERRACOTTA_LIGHT_GREEN = level::material::Material(103, 117, 53);
    inline constexpr auto TERRACOTTA_PINK = level::material::Material(160, 77, 78);
    inline constexpr auto TERRACOTTA_GRAY = level::material::Material(57, 41, 35);
    inline constexpr auto TERRACOTTA_LIGHT_GRAY = level::material::Material(135, 107, 98);
    inline constexpr auto TERRACOTTA_CYAN = level::material::Material(87, 92, 92);
    inline constexpr auto TERRACOTTA_PURPLE = level::material::Material(122, 73, 88);
    inline constexpr auto TERRACOTTA_BLUE = level::material::Material(76, 62, 92);
    inline constexpr auto TERRACOTTA_BROWN = level::material::Material(76, 50, 35);
    inline constexpr auto TERRACOTTA_GREEN = level::material::Material(76, 82, 42);
    inline constexpr auto TERRACOTTA_RED = level::material::Material(142, 60, 46);
    inline constexpr auto TERRACOTTA_BLACK = level::material::Material(37, 22, 16);
    inline constexpr auto CRIMSON_NYLIUM = level::material::Material(189, 48, 49);
    inline constexpr auto CRIMSON_STEM = level::material::Material(148, 63, 97);
    inline constexpr auto CRIMSON_HYPHAE = level::material::Material(92, 25, 29);
    inline constexpr auto WARPED_NYLIUM = level::material::Material(22, 126, 134);
    inline constexpr auto WARPED_STEM = level::material::Material(58, 142, 140);
    inline constexpr auto WARPED_HYPHAE = level::material::Material(86, 44, 62);
    inline constexpr auto WARPED_WART_BLOCK = level::material::Material(20, 180, 133);
    inline constexpr auto DEEPSLATE = level::material::Material(100, 100, 100);
    inline constexpr auto RAW_IRON = level::material::Material(216, 175, 147);
    inline constexpr auto GLOW_LICHEN = level::material::Material(127, 167, 150);
}

#endif // LODESTONE_MATERIALS_Ht