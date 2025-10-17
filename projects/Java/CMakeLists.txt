cmake_minimum_required(VERSION 4.0)
project(Lodestone.Java)

set(CMAKE_CXX_STANDARD 17)

set(FILES
        include/Lodestone.Java/Classic/MineV1/MineV1LevelIo.h
        src/Classic/MineV1/MineV1LevelIo.cpp
        src/LodestoneJava.cpp
        src/Classic/ClassicBlockIo.cpp
        include/Lodestone.Java/Classic/ClassicBlockIo.h
        include/Lodestone.Java/LodestoneJava.h
        src/Classic/MineV2/MineV2LevelIO.cpp
        include/Lodestone.Java/Classic/MineV2/MineV2LevelIO.h
        src/Classic/MineV2/MineV2World.cpp
        include/Lodestone.Java/Classic/MineV2/MineV2World.h
        src/Classic/Indev/McLevelLevelIo.cpp
        include/Lodestone.Java/Indev/McLevelLevelIo.h
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
            "-D_GLIBCXX_DEBUG"
    )
endif ()

add_library(Lodestone.Java SHARED ${FILES})
target_include_directories(Lodestone.Java
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include/Lodestone.Java
)

target_link_libraries(Lodestone.Java PRIVATE Lodestone.Level)
#target_link_libraries(Lodestone.Java PRIVATE Lodestone.Common)