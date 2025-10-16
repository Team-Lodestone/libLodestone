cmake_minimum_required(VERSION 4.0)
project(Lodestone.Java)

set(CMAKE_CXX_STANDARD 17)

set(FILES
        include/Classic/MineV1LevelIo.h
        src/Classic/MineV1LevelIo.cpp
        src/Main.cpp
        src/Classic/ClassicBlockIo.cpp
        include/Classic/ClassicBlockIo.h
        include/Main.h
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