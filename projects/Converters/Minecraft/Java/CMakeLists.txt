cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Minecraft.Java VERSION 1.0.2)

set(VERSION_SUFFIX "-dev.0") # used for non-stable versions, otherwise blank
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
        src/mcregion/chunk/McRegionChunkIo.cpp
        include/Lodestone.Minecraft.Java/mcregion/chunk/McRegionChunkIo.h
        src/mcregion/chunk/McRegionChunk.cpp
        include/Lodestone.Minecraft.Java/mcregion/chunk/McRegionChunk.h
        src/mcregion/region/McRegionRegionIo.cpp
        include/Lodestone.Minecraft.Java/mcregion/region/McRegionRegionIo.h
        include/Lodestone.Minecraft.Java/Identifiers.h
        src/mcregion/world/McRegionWorldIo.cpp
        include/Lodestone.Minecraft.Java/mcregion/world/McRegionWorldIo.h
        src/mcregion/world/McRegionWorld.cpp
        include/Lodestone.Minecraft.Java/mcregion/world/McRegionWorld.h
        src/mcregion/region/McRegionRegion.cpp
        include/Lodestone.Minecraft.Java/mcregion/region/McRegionRegion.h
        src/mcregion/player/McRegionPlayer.cpp
        include/Lodestone.Minecraft.Java/mcregion/player/McRegionPlayer.h
        src/mcregion/player/McRegionPlayerIo.cpp
        include/Lodestone.Minecraft.Java/mcregion/player/McRegionPlayerIo.h
        include/Lodestone.Minecraft.Java/classic/minev2/options/MineV2WorldWriteOptions.h
        include/Lodestone.Minecraft.Java/alpha/world/AlphaWorld.h
        src/alpha/world/AlphaWorld.cpp
        src/alpha/world/AlphaWorldIo.cpp
        include/Lodestone.Minecraft.Java/alpha/world/AlphaWorldIo.h
        src/alpha/player/AlphaPlayer.cpp
        include/Lodestone.Minecraft.Java/alpha/player/AlphaPlayer.h
        src/alpha/player/AlphaPlayerIo.cpp
        include/Lodestone.Minecraft.Java/alpha/player/AlphaPlayerIo.h
        src/classic/minev2/options/MineV2WorldWriteOptions.cpp
        include/Lodestone.Minecraft.Java/anvil/jungle/chunk/JungleAnvilChunk.h
        src/anvil/jungle/chunk/JungleAnvilChunkIo.cpp
        include/Lodestone.Minecraft.Java/anvil/jungle/chunk/JungleAnvilChunkIo.h
        include/Lodestone.Minecraft.Java/anvil/jungle/region/JungleAnvilRegion.h
        src/anvil/jungle/region/JungleAnvilRegion.cpp
        include/Lodestone.Minecraft.Java/anvil/jungle/region/JungleAnvilRegionIo.h
        src/anvil/jungle/region/JungleAnvilRegionIo.cpp
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