cmake_minimum_required(VERSION 4.0)
project(Lodestone VERSION 1.0.0)

set(VERSION_SUFFIX "-dev.16") # used for non-stable versions, otherwise blank
set(CMAKE_CXX_STANDARD 20)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DCMAKE_BUILD_DEBUG)
endif ()

option(ENABLE_OPTIMIZATIONS "Enable compiler optimizations" ON)
if (ENABLE_OPTIMIZATIONS STREQUAL "ON")
    add_compile_options(
            "$<$<COMPILE_LANGUAGE:CXX>:-O3;-ffast-math;-march=native;-fpic;-ftree-vectorize>"
    )
endif ()
unset(ENABLE_OPTIMIZATIONS CACHE)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# BIO
include(FetchContent)
FetchContent_Declare(
        BIO
        GIT_REPOSITORY https://github.com/DexrnZacAttack/libBIO.git
        GIT_TAG main
)
FetchContent_MakeAvailable(BIO)

# NBT
set(NBT_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
        nbt++
        GIT_REPOSITORY https://github.com/PrismLauncher/libnbtplusplus.git
        GIT_TAG master
)
FetchContent_MakeAvailable(nbt++)

#include_directories(${BIO_SOURCE_DIR})

# PROJECTS
add_subdirectory(projects/Tests)
add_subdirectory(projects/Common)
add_subdirectory(projects/Level)
add_subdirectory(projects/Java)

# TODO: this is probably a bad idea incase one wants to only include certain licenses
target_link_libraries(Lodestone.Tests PRIVATE BIO)
target_link_libraries(Lodestone.Common PRIVATE BIO)
target_link_libraries(Lodestone.Level PRIVATE BIO)
target_link_libraries(Lodestone.Java PRIVATE BIO nbt++)

# DEFINITIONS
target_compile_definitions(Lodestone.Common PUBLIC
        LODESTONE_COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}"
        LODESTONE_PLATFORM_NAME="${CMAKE_SYSTEM_NAME}"
        LODESTONE_PLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
        LODESTONE_VERSION="${PROJECT_VERSION}${VERSION_SUFFIX}"
        LODESTONE_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
)

# because otherwise jetbrains implodes
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
            "-D_GLIBCXX_DEBUG"
    )
endif ()

add_custom_target(Lodestone.All ALL DEPENDS Lodestone.Common Lodestone.Level Lodestone.Tests Lodestone.Java)


