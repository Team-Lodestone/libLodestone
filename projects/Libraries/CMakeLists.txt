cmake_minimum_required(VERSION 3.30)
project(Lodestone VERSION 1.0.0)

set(PROJECT_VERSION_PRE_RELEASE "-dev.36") # used for non-stable versions, otherwise blank
set(CMAKE_CXX_STANDARD 20)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DCMAKE_BUILD_DEBUG)
endif ()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BIO_TESTS "Build libBIO tests" OFF)

# BIO
include(FetchContent)
FetchContent_Declare(
        bio
        GIT_REPOSITORY https://codeberg.org/Dexrn/libBIO.git
        GIT_TAG 3.1.0
)
FetchContent_MakeAvailable(bio)

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

#add_library(ZLIB::ZLIB ALIAS zlibstatic)

FetchContent_Declare(
        msft_proxy4
        GIT_TAG 4.0.0
        GIT_REPOSITORY https://github.com/ngcpp/proxy.git
)
FetchContent_MakeAvailable(msft_proxy4)

#include_directories(${BIO_SOURCE_DIR})

# PROJECTS
add_subdirectory(Core)
add_subdirectory(Common)
add_subdirectory(Level)
add_subdirectory(Conversion)

# DEFINITIONS
target_compile_definitions(Lodestone.Common PUBLIC
        LODESTONE_BUILD_TYPE="${CMAKE_BUILD_TYPE}"
        LODESTONE_COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}"
        LODESTONE_PLATFORM_NAME="${CMAKE_SYSTEM_NAME}"
        LODESTONE_PLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
        LODESTONE_VERSION="${PROJECT_VERSION}${PROJECT_VERSION_PRE_RELEASE}"
        LODESTONE_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
)

add_custom_target(Lodestone.Libraries ALL DEPENDS
        LodestoneScripts.CheckIncludePaths
        Lodestone.Common
        Lodestone.Level
        Lodestone.Conversion
        Lodestone.Core
)


