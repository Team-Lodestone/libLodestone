cmake_minimum_required(VERSION 3.30)
project(Lodestone VERSION 1.0.0)

set(VERSION_SUFFIX "-dev.29_restructure-1") # used for non-stable versions, otherwise blank
set(CMAKE_CXX_STANDARD 20)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DCMAKE_BUILD_DEBUG)
endif ()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# BIO
include(FetchContent)
FetchContent_Declare(
        BIO
        GIT_REPOSITORY https://github.com/DexrnZacAttack/libBIO.git
        GIT_TAG main
)
FetchContent_MakeAvailable(BIO)

# GTL
include(FetchContent)
FetchContent_Declare(
        gtl
        GIT_REPOSITORY https://github.com/greg7mdp/gtl.git
        GIT_TAG        main
)
FetchContent_MakeAvailable(gtl)

FetchContent_Declare(
        zlib
        GIT_REPOSITORY "https://github.com/madler/zlib.git"
        FIND_PACKAGE_ARGS NAMES ZLIB
)
FetchContent_MakeAvailable(zlib)

add_library(ZLIB::ZLIB ALIAS zlibstatic)

#include_directories(${BIO_SOURCE_DIR})

# PROJECTS
add_subdirectory(Core)
add_subdirectory(Common)
add_subdirectory(Level)
add_subdirectory(Conversion)

# DEFINITIONS
target_compile_definitions(Lodestone.Common PUBLIC
        LODESTONE_COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}"
        LODESTONE_PLATFORM_NAME="${CMAKE_SYSTEM_NAME}"
        LODESTONE_PLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
        LODESTONE_VERSION="${PROJECT_VERSION}${VERSION_SUFFIX}"
        LODESTONE_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
)

add_custom_target(Lodestone.Libraries ALL DEPENDS
        LodestoneScripts.CheckIncludePaths
        Lodestone.Common
        Lodestone.Level
        Lodestone.Conversion
        Lodestone.Core
)


