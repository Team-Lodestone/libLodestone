cmake_minimum_required(VERSION 4.0)
project(Lodestone.Java)

set(CMAKE_CXX_STANDARD 20)

set(FILES
        include/Lodestone.Java/Classic/MineV1/MineV1LevelIO.h
        src/Classic/MineV1/MineV1LevelIO.cpp
        src/LodestoneJava.cpp
        src/Classic/ClassicBlockIO.cpp
        include/Lodestone.Java/Classic/ClassicBlockIO.h
        include/Lodestone.Java/LodestoneJava.h
        src/Classic/MineV2/MineV2LevelIO.cpp
        include/Lodestone.Java/Classic/MineV2/MineV2LevelIO.h
        src/Classic/MineV2/MineV2World.cpp
        include/Lodestone.Java/Classic/MineV2/MineV2World.h
        src/Indev/McLevelLevelIO.cpp
        include/Lodestone.Java/Indev/McLevelLevelIO.h
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