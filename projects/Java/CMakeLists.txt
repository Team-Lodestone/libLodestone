cmake_minimum_required(VERSION 4.0)
project(Lodestone.Java)

set(CMAKE_CXX_STANDARD 17)

set(FILES
        include/Classic/MineV1/MineV1LevelIo.h
        src/Classic/MineV1/MineV1LevelIo.cpp
        src/Main.cpp
        src/Classic/ClassicBlockIo.cpp
        include/Classic/ClassicBlockIo.h
        include/Main.h
        src/Classic/MineV2/MineV2LevelIO.cpp
        include/Classic/MineV2/MineV2LevelIO.h
        src/Classic/MineV2/MineV2World.cpp
        include/Classic/MineV2/MineV2World.h
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
            "-D_GLIBCXX_DEBUG"
    )
endif ()

add_library(Lodestone.Java SHARED ${FILES})
target_include_directories(Lodestone.Java PUBLIC include src)

target_link_libraries(Lodestone.Java PRIVATE Lodestone.Level)
target_link_libraries(Lodestone.Java PRIVATE Lodestone.Common)