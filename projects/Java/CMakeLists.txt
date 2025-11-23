cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Java)

set(CMAKE_CXX_STANDARD 20)

set(FILES
        include/Lodestone.Java/classic/minev1/MineV1LevelIO.h
        src/classic/minev1/MineV1LevelIO.cpp
        src/LodestoneJava.cpp
        include/Lodestone.Java/LodestoneJava.h
        src/classic/minev2/MineV2LevelIO.cpp
        include/Lodestone.Java/classic/minev2/MineV2LevelIO.h
        src/classic/minev2/MineV2World.cpp
        include/Lodestone.Java/classic/minev2/MineV2World.h
        src/indev/McLevelLevelIO.cpp
        include/Lodestone.Java/indev/McLevelLevelIO.h
        include/Lodestone.Java/Version.h
        src/classic/minev2/MineV2WorldIo.cpp
        include/Lodestone.Java/classic/minev2/MineV2WorldIo.h
        src/mcr/chunk/McRegionChunkIo.cpp
        include/Lodestone.Java/mcr/chunk/McRegionChunkIo.h
        src/mcr/chunk/McRegionChunk.cpp
        include/Lodestone.Java/mcr/chunk/McRegionChunk.h
        src/mcr/region/McRegionRegionIo.cpp
        include/Lodestone.Java/mcr/region/McRegionRegionIo.h
        include/Lodestone.Java/mcr/RegionChunkIndice.h
        include/Lodestone.Java/mcr/RegionCompression.h
        include/Lodestone.Java/Identifiers.h
        src/mcr/world/McRegionWorldIo.cpp
        include/Lodestone.Java/mcr/world/McRegionWorldIo.h
        src/mcr/world/McRegionWorld.cpp
        include/Lodestone.Java/mcr/world/McRegionWorld.h
        src/mcr/region/McRegionRegion.cpp
        include/Lodestone.Java/mcr/region/McRegionRegion.h
        src/mcr/player/McRegionPlayer.cpp
        include/Lodestone.Java/mcr/player/McRegionPlayer.h
        src/mcr/player/McRegionPlayerIo.cpp
        include/Lodestone.Java/mcr/player/McRegionPlayerIo.h
        include/Lodestone.Java/io/chunk/NbtChunkIo.h
        include/Lodestone.Java/classic/minev2/options/MineV2WorldWriteOptions.h
        include/Lodestone.Java/alpha/world/AlphaWorld.h
        src/alpha/world/AlphaWorld.cpp
        src/alpha/world/AlphaWorldIo.cpp
        include/Lodestone.Java/alpha/world/AlphaWorldIo.h
        src/classic/minev2/options/MineV2WorldWriteOptions.cpp
        src/alpha/player/AlphaPlayer.cpp
        include/Lodestone.Java/alpha/player/AlphaPlayer.h
        src/alpha/player/AlphaPlayerIo.cpp
        include/Lodestone.Java/alpha/player/AlphaPlayerIo.h
)

# NBT
set(NBT_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
        nbt++
        GIT_REPOSITORY https://github.com/Team-Lodestone/libnbtplusplus.git
        GIT_TAG master
)
FetchContent_MakeAvailable(nbt++)

#FetchContent_Declare(
#        stduuid
#        GIT_REPOSITORY https://github.com/mariusbancila/stduuid.git
#        GIT_TAG master
#)
#FetchContent_MakeAvailable(stduuid)

add_library(Lodestone.Java SHARED ${FILES})
target_include_directories(Lodestone.Java
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

find_package(OpenMP COMPONENTS C CXX)
target_link_libraries(Lodestone.Java PRIVATE Lodestone.Level Lodestone.Conversion nbt++)
target_link_libraries(Lodestone.Java PUBLIC Lodestone.Core)
#target_link_libraries(Lodestone.Java PRIVATE Lodestone.Common)

option(USE_OPENMP "Use OpenMP" ON)
if (USE_OPENMP STREQUAL ON AND OpenMP_CXX_FOUND AND OpenMP_C_FOUND)
    message(STATUS "Using OpenMP")
    target_link_libraries(Lodestone.Java PRIVATE OpenMP::OpenMP_CXX)
    target_compile_definitions(Lodestone.Java PRIVATE USE_OPENMP)
endif()

option(ENABLE_RISKY_OPTIMIZATIONS "Enable risky optimizations" ON)
if (ENABLE_RISKY_OPTIMIZATIONS STREQUAL ON)
    target_compile_definitions(Lodestone.Java PRIVATE USE_RISKY_OPTIMIZATIONS)
endif ()