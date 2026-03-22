cmake_minimum_required(VERSION 3.30)
project(Lodestone VERSION 1.0.0)

# after we hit full 1.0.0, we should version all 4 libs.
set(PROJECT_VERSION_DEV 53) # used for dev versions, otherwise blank
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BIO_TESTS "Build libBIO tests" OFF)

# BIO
if (NOT TARGET bio)
    include(FetchContent)
    FetchContent_Declare(
            bio
            GIT_REPOSITORY https://codeberg.org/Dexrn/libBIO.git
            GIT_TAG 4.0.0-dev.4
    )

    FetchContent_MakeAvailable(bio)
endif()

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
        GIT_TAG 4.0.2
        GIT_REPOSITORY https://github.com/ngcpp/proxy.git
)
FetchContent_MakeAvailable(msft_proxy4)

#include_directories(${BIO_SOURCE_DIR})

# PROJECTS
add_subdirectory(Core)
add_subdirectory(Common)
add_subdirectory(Level)
add_subdirectory(Conversion)

set(VERSIONS
        MAJOR
        MINOR
        PATCH
        DEV
)

foreach(k IN LISTS VERSIONS)
    if (DEFINED PROJECT_VERSION_${k})
        target_compile_definitions(Lodestone.Common PUBLIC
                LODESTONE_${k}_VERSION=${PROJECT_VERSION_${k}}
        )
    else()
        target_compile_definitions(Lodestone.Common PUBLIC
                LODESTONE_${k}_VERSION=-1
        )
    endif()
endforeach ()

if (DEFINED PROJECT_VERSION_DEV)
    set(PROJECT_VERSION_SUFFIX -dev.${PROJECT_VERSION_DEV})
endif()

# DEFINITIONS
target_compile_definitions(Lodestone.Common PUBLIC
        LODESTONE_BUILD_TYPE="${CMAKE_BUILD_TYPE}"
        LODESTONE_COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}"
        LODESTONE_PLATFORM_NAME="${CMAKE_SYSTEM_NAME}"
        LODESTONE_PLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
        LODESTONE_VERSION="${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}${PROJECT_VERSION_SUFFIX}"
)

add_custom_target(Lodestone.Libraries ALL DEPENDS
        LodestoneScripts.CheckIncludePaths
        Lodestone.Common
        Lodestone.Level
        Lodestone.Conversion
        Lodestone.Core
)


