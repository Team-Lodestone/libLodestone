cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Minecraft.Java VERSION 1.0.0)

set(VERSION_SUFFIX "") # used for non-stable versions, otherwise blank
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(FILES
        include/Lodestone.Minecraft.Java/classic/minev1/MineV1LevelIO.h
        src/classic/minev1/MineV1LevelIO.cpp
        src/LodestoneJava.cpp
        include/Lodestone.Minecraft.Java/LodestoneJava.h
        src/classic/minev2/MineV2LevelIO.cpp
        include/Lodestone.Minecraft.Java/classic/minev2/MineV2LevelIO.h
        src/classic/minev2/MineV2World.cpp
        include/Lodestone.Minecraft.Java/classic/minev2/MineV2World.h
        src/indev/McLevelLevelIO.cpp
        include/Lodestone.Minecraft.Java/indev/McLevelLevelIO.h
        include/Lodestone.Minecraft.Java/Version.h
        src/classic/minev2/MineV2WorldIo.cpp
        include/Lodestone.Minecraft.Java/classic/minev2/MineV2WorldIo.h
        src/mcr/chunk/McRegionChunkIo.cpp
        include/Lodestone.Minecraft.Java/mcr/chunk/McRegionChunkIo.h
        src/mcr/chunk/McRegionChunk.cpp
        include/Lodestone.Minecraft.Java/mcr/chunk/McRegionChunk.h
        src/mcr/region/McRegionRegionIo.cpp
        include/Lodestone.Minecraft.Java/mcr/region/McRegionRegionIo.h
        include/Lodestone.Minecraft.Java/mcr/RegionChunkIndice.h
        include/Lodestone.Minecraft.Java/mcr/RegionCompression.h
        include/Lodestone.Minecraft.Java/Identifiers.h
        src/mcr/world/McRegionWorldIo.cpp
        include/Lodestone.Minecraft.Java/mcr/world/McRegionWorldIo.h
        src/mcr/world/McRegionWorld.cpp
        include/Lodestone.Minecraft.Java/mcr/world/McRegionWorld.h
        src/mcr/region/McRegionRegion.cpp
        include/Lodestone.Minecraft.Java/mcr/region/McRegionRegion.h
        src/mcr/player/McRegionPlayer.cpp
        include/Lodestone.Minecraft.Java/mcr/player/McRegionPlayer.h
        src/mcr/player/McRegionPlayerIo.cpp
        include/Lodestone.Minecraft.Java/mcr/player/McRegionPlayerIo.h
        include/Lodestone.Minecraft.Java/classic/minev2/options/MineV2WorldWriteOptions.h
)

add_library(Lodestone.Minecraft.Java SHARED ${FILES})
target_include_directories(Lodestone.Minecraft.Java
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

find_package(OpenMP COMPONENTS C CXX)
target_link_libraries(Lodestone.Minecraft.Java PRIVATE Lodestone.Level Lodestone.Conversion nbt++ BIO)
target_link_libraries(Lodestone.Minecraft.Java PUBLIC Lodestone.Core Lodestone.Minecraft.Common)

option(USE_OPENMP "Use OpenMP" ON)
if (USE_OPENMP STREQUAL ON AND OpenMP_CXX_FOUND AND OpenMP_C_FOUND)
    message(STATUS "Using OpenMP")
    target_link_libraries(Lodestone.Minecraft.Java PRIVATE OpenMP::OpenMP_CXX)
    target_compile_definitions(Lodestone.Minecraft.Java PRIVATE USE_OPENMP)
endif()

option(ENABLE_RISKY_OPTIMIZATIONS "Enable risky optimizations" ON)
if (ENABLE_RISKY_OPTIMIZATIONS STREQUAL ON)
    target_compile_definitions(Lodestone.Minecraft.Java PRIVATE USE_RISKY_OPTIMIZATIONS)
endif ()

target_compile_definitions(Lodestone.Minecraft.Java PUBLIC
        LODESTONE_JAVA_VERSION="${PROJECT_VERSION}${VERSION_SUFFIX}"
        LODESTONE_JAVA_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
)

setupLinter(Lodestone.Minecraft.Java)