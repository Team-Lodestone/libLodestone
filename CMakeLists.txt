cmake_minimum_required(VERSION 3.30)
project(Lodestone)

include(${CMAKE_SOURCE_DIR}/script/cmake/linting.cmake)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DCMAKE_BUILD_DEBUG)
endif ()

# BIO
include(FetchContent)
FetchContent_Declare(
        BIO
        GIT_REPOSITORY https://github.com/DexrnZacAttack/libBIO.git
        GIT_TAG main
)
FetchContent_MakeAvailable(BIO)

# PROJECTS
add_subdirectory(projects/Libraries)
add_subdirectory(projects/Utilities)
add_subdirectory(projects/Converters)

add_custom_target(Lodestone.All ALL DEPENDS
        Lodestone.Libraries
        Lodestone.Converters
        Lodestone.Utilities
)


