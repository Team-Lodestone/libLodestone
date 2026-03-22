cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Minecraft.Common)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(FILES
        src/player/MinecraftPlayer.cpp
        include/Lodestone.Minecraft.Common/player/MinecraftPlayer.h
        include/Lodestone.Minecraft.Common/Identifiers.h
        src/LodestoneMinecraftCommon.cpp
        include/Lodestone.Minecraft.Common/LodestoneMinecraftCommon.h
        include/Lodestone.Minecraft.Common/block/Blocks.h
        src/world/MinecraftWorld.cpp
        include/Lodestone.Minecraft.Common/world/MinecraftWorld.h
        include/Lodestone.Minecraft.Common/region/RegionChunkIndice.h
        include/Lodestone.Minecraft.Common/region/RegionCompression.h
        include/Lodestone.Minecraft.Common/player/Abilities.h
        src/world/data/LevelData.cpp
        include/Lodestone.Minecraft.Common/world/data/LevelData.h
        include/Lodestone.Minecraft.Common/conversion/io/options/NbtReaderOptions.h
        include/Lodestone.Minecraft.Common/conversion/io/options/OptionPresets.h
        include/Lodestone.Minecraft.Common/conversion/registry/Registries.h
        include/Lodestone.Minecraft.Common/conversion/io/interfaces/ILevelDataIo.h
        include/Lodestone.Minecraft.Common/conversion/io/ObjectIOs.h
        include/Lodestone.Minecraft.Common/conversion/io/options/ChunkOptions.h
        include/Lodestone.Minecraft.Common/conversion/io/types/NbtOutputWritable.h
        include/Lodestone.Minecraft.Common/internal/Exports.h
)

add_library(Lodestone.Minecraft.Common OBJECT ${FILES})
target_include_directories(Lodestone.Minecraft.Common
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Lodestone.Minecraft.Common PRIVATE Lodestone.Level Lodestone.Conversion nbt++ bio-cpp20)
target_link_libraries(Lodestone.Minecraft.Common PUBLIC Lodestone.Core)

setupExports(Lodestone.Minecraft.Common)
setupLinter(Lodestone.Minecraft.Common)