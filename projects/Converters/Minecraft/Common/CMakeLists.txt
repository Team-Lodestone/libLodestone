cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Minecraft.Common)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(FILES
        include/Lodestone.Minecraft.Common/io/chunk/NbtChunkIo.h
        src/player/MinecraftPlayer.cpp
        include/Lodestone.Minecraft.Common/player/MinecraftPlayer.h
        include/Lodestone.Minecraft.Common/Identifiers.h
        src/LodestoneMinecraftCommon.cpp
        include/Lodestone.Minecraft.Common/LodestoneMinecraftCommon.h
        include/Lodestone.Minecraft.Common/block/Blocks.h
)

add_library(Lodestone.Minecraft.Common OBJECT ${FILES})
target_include_directories(Lodestone.Minecraft.Common
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

find_package(OpenMP COMPONENTS C CXX)
target_link_libraries(Lodestone.Minecraft.Common PRIVATE Lodestone.Level Lodestone.Conversion nbt++ BIO)
target_link_libraries(Lodestone.Minecraft.Common PUBLIC Lodestone.Core)

setupLinter(Lodestone.Minecraft.Common)