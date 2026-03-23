cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Minecraft.Java VERSION 1.2.2)
set(PROJECT_VERSION_DEV) # used for dev versions, otherwise blank

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(FILES
        include/Lodestone.Minecraft.Java/conversion/classic/minev1/MineV1LevelIO.h
        src/classic/minev1/MineV1LevelIO.cpp
        src/LodestoneJava.cpp
        include/Lodestone.Minecraft.Java/LodestoneJava.h
        src/classic/minev2/MineV2LevelIO.cpp
        include/Lodestone.Minecraft.Java/conversion/classic/minev2/MineV2LevelIO.h
        src/classic/minev2/MineV2World.cpp
        include/Lodestone.Minecraft.Java/classic/minev2/MineV2World.h
        src/indev/McLevelLevelIO.cpp
        include/Lodestone.Minecraft.Java/conversion/indev/McLevelLevelIO.h
        include/Lodestone.Minecraft.Java/Version.h
        src/classic/minev2/MineV2WorldIo.cpp
        include/Lodestone.Minecraft.Java/conversion/classic/minev2/MineV2WorldIo.h
        src/mcregion/chunk/McRegionChunkIo.cpp
        include/Lodestone.Minecraft.Java/conversion/mcregion/McRegionChunkIo.h
        src/mcregion/chunk/McRegionChunk.cpp
        include/Lodestone.Minecraft.Java/mcregion/McRegionChunk.h
        src/mcregion/region/McRegionRegionIo.cpp
        include/Lodestone.Minecraft.Java/conversion/mcregion/McRegionRegionIo.h
        include/Lodestone.Minecraft.Java/Identifiers.h
        src/mcregion/world/McRegionWorldIo.cpp
        include/Lodestone.Minecraft.Java/conversion/mcregion/McRegionWorldIo.h
        src/mcregion/world/McRegionWorld.cpp
        include/Lodestone.Minecraft.Java/mcregion/McRegionWorld.h
        src/mcregion/region/McRegionRegion.cpp
        include/Lodestone.Minecraft.Java/mcregion/McRegionRegion.h
        src/mcregion/player/McRegionPlayer.cpp
        include/Lodestone.Minecraft.Java/mcregion/McRegionPlayer.h
        src/mcregion/player/McRegionPlayerIo.cpp
        include/Lodestone.Minecraft.Java/conversion/mcregion/McRegionPlayerIo.h
        include/Lodestone.Minecraft.Java/conversion/classic/minev2/options/MineV2WorldWriteOptions.h
        include/Lodestone.Minecraft.Java/alpha/AlphaWorld.h
        src/alpha/world/AlphaWorld.cpp
        src/alpha/world/AlphaWorldIo.cpp
        include/Lodestone.Minecraft.Java/conversion/alpha/AlphaWorldIo.h
        src/alpha/player/AlphaPlayer.cpp
        include/Lodestone.Minecraft.Java/alpha/AlphaPlayer.h
        src/alpha/player/AlphaPlayerIo.cpp
        include/Lodestone.Minecraft.Java/conversion/alpha/AlphaPlayerIo.h
        include/Lodestone.Minecraft.Java/anvil/jungle/JungleAnvilChunk.h
        src/anvil/jungle/chunk/JungleAnvilChunkIo.cpp
        include/Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilChunkIo.h
        include/Lodestone.Minecraft.Java/anvil/jungle/JungleAnvilRegion.h
        src/anvil/jungle/region/JungleAnvilRegion.cpp
        include/Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilRegionIo.h
        src/anvil/jungle/region/JungleAnvilRegionIo.cpp
        src/anvil/jungle/world/JungleAnvilWorld.cpp
        include/Lodestone.Minecraft.Java/anvil/jungle/JungleAnvilWorld.h
        src/anvil/jungle/world/JungleAnvilWorldIo.cpp
        include/Lodestone.Minecraft.Java/conversion/anvil/jungle/JungleAnvilWorldIo.h
        include/Lodestone.Minecraft.Java/GeneratorTypes.h
        src/GeneratorTypes.cpp
        include/Lodestone.Minecraft.Java/alpha/AlphaLevelData.h
        src/mcregion/world/data/McRegionLevelData.cpp
        include/Lodestone.Minecraft.Java/mcregion/McRegionLevelData.h
        src/alpha/world/data/AlphaLevelData.cpp
        include/Lodestone.Minecraft.Java/conversion/mcregion/McRegionLevelDataIo.h
        src/classic/minev3/MineV3LevelIO.cpp
        include/Lodestone.Minecraft.Java/conversion/classic/minev3/MineV3LevelIO.h
        src/classic/minev3/JavaSerializedClassParser.cpp
        include/Lodestone.Minecraft.Java/classic/minev3/JavaSerializedClassParser.h
        src/classic/minev3/MineV3World.cpp
        src/classic/minev3/MineV3WorldIo.cpp
        include/Lodestone.Minecraft.Java/conversion/classic/minev3/MineV3WorldIo.h
        include/Lodestone.Minecraft.Java/conversion/classic/minev3/options/MineV3WorldWriteOptions.h
        include/Lodestone.Minecraft.Java/classic/minev3/MineV3World.h
)

add_library(Lodestone.Minecraft.Java SHARED ${FILES})
target_include_directories(Lodestone.Minecraft.Java
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Lodestone.Minecraft.Java PRIVATE Lodestone.Level Lodestone.Conversion nbt++ bio-cpp20)
target_link_libraries(Lodestone.Minecraft.Java PUBLIC Lodestone.Core Lodestone.Minecraft.Common)

set(VERSIONS
        MAJOR
        MINOR
        PATCH
        DEV
)

foreach(k IN LISTS VERSIONS)
    if (DEFINED PROJECT_VERSION_${k})
        target_compile_definitions(Lodestone.Minecraft.Java PUBLIC
                LODESTONE_MINECRAFT_JAVA_${k}_VERSION=${PROJECT_VERSION_${k}}
        )
    else()
        target_compile_definitions(Lodestone.Minecraft.Java PUBLIC
                LODESTONE_MINECRAFT_JAVA_${k}_VERSION=-1
        )
    endif()
endforeach ()

#None/TBB/STL-TBB/OpenMP/STL
set(THREADING_TYPE TBB CACHE STRING "Threading type")
set(APPLIED_THREADING_TYPE "None")
set(APPLIED_THREADING_TYPE_ID 0)

message(STATUS "Attempting to use threading type ${THREADING_TYPE}")

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (THREADING_TYPE STREQUAL "TBB")
        find_package(TBB)

        if (TBB_FOUND)
            set(APPLIED_THREADING_TYPE "TBB")
            set(APPLIED_THREADING_TYPE_ID 1)

            target_link_libraries(Lodestone.Minecraft.Java PRIVATE TBB::tbb)
        endif ()
    elseif (THREADING_TYPE STREQUAL "STL-TBB" AND TBB_FOUND)
        find_package(TBB)

        if (TBB_FOUND)
            set(APPLIED_THREADING_TYPE "STL-TBB")
            set(APPLIED_THREADING_TYPE_ID 2)

            target_link_libraries(Lodestone.Minecraft.Java PRIVATE TBB::tbb)
        endif ()
    elseif (THREADING_TYPE STREQUAL "OpenMP")
        find_package(OpenMP COMPONENTS C CXX)

        if (OpenMP_CXX_FOUND AND OpenMP_C_FOUND)
            set(APPLIED_THREADING_TYPE "OpenMP")
            set(APPLIED_THREADING_TYPE_ID 3)

            target_link_libraries(Lodestone.Minecraft.Java PRIVATE OpenMP::OpenMP_CXX)
        endif ()
    elseif (THREADING_TYPE STREQUAL "STL")
        set(APPLIED_THREADING_TYPE "STL")
        set(APPLIED_THREADING_TYPE_ID 4)
    endif ()
endif ()

message(STATUS "Using threading type ${APPLIED_THREADING_TYPE}")
target_compile_definitions(Lodestone.Minecraft.Java PRIVATE
        LODESTONE_MINECRAFT_JAVA_THREADING_TYPE=${APPLIED_THREADING_TYPE_ID}
)

unset(THREADING_TYPE CACHE)

option(ENABLE_RISKY_OPTIMIZATIONS "Enable risky optimizations" ON)
if (ENABLE_RISKY_OPTIMIZATIONS STREQUAL ON)
    target_compile_definitions(Lodestone.Minecraft.Java PRIVATE USE_RISKY_OPTIMIZATIONS)
endif ()
unset(ENABLE_RISKY_OPTIMIZATIONS CACHE)

setupLinter(Lodestone.Minecraft.Java)