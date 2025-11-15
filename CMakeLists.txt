cmake_minimum_required(VERSION 3.30)
project(Lodestone VERSION 1.0.0)

set(VERSION_SUFFIX "-dev.25") # used for non-stable versions, otherwise blank
set(CMAKE_CXX_STANDARD 20)

option(ENABLE_LINTERS "Enable source linters" ON)
option(BUILD_VIEWER "Build Lodestone.Viewer" OFF)

if (ENABLE_LINTERS STREQUAL "ON")
    add_custom_target(LodestoneScripts.CheckIncludePaths
            COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/script/checkIncludePaths.py
    )
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DCMAKE_BUILD_DEBUG)
endif ()

option(ENABLE_OPTIMIZATIONS "Enable compiler optimizations" ON)
if (ENABLE_OPTIMIZATIONS STREQUAL "ON")
    message(NOTICE "Compiler optimizations enabled")
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

# GTL
include(FetchContent)
FetchContent_Declare(
        gtl
        GIT_REPOSITORY https://github.com/greg7mdp/gtl.git
        GIT_TAG        main
)
FetchContent_MakeAvailable(gtl)

find_package(ZLIB)

#include_directories(${BIO_SOURCE_DIR})

# PROJECTS
add_subdirectory(projects/Tests)
add_subdirectory(projects/Common)
add_subdirectory(projects/Level)
add_subdirectory(projects/Conversion)
add_subdirectory(projects/Java)
if (BUILD_VIEWER STREQUAL "ON")
    add_subdirectory(projects/Viewer)
endif()

# TODO: this is probably a bad idea incase one wants to only include certain libraries
target_link_libraries(Lodestone.Tests PRIVATE BIO gtl)
target_link_libraries(Lodestone.Common PRIVATE BIO gtl)
target_link_libraries(Lodestone.Level PRIVATE BIO gtl)
target_link_libraries(Lodestone.Conversion PRIVATE BIO gtl)
target_link_libraries(Lodestone.Java PRIVATE BIO ZLIB::ZLIB gtl)

add_dependencies(Lodestone.Tests LodestoneScripts.CheckIncludePaths)
add_dependencies(Lodestone.Common LodestoneScripts.CheckIncludePaths)
add_dependencies(Lodestone.Level LodestoneScripts.CheckIncludePaths)
add_dependencies(Lodestone.Conversion LodestoneScripts.CheckIncludePaths)
add_dependencies(Lodestone.Java LodestoneScripts.CheckIncludePaths)

# DEFINITIONS
target_compile_definitions(Lodestone.Common PUBLIC
        LODESTONE_COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}"
        LODESTONE_PLATFORM_NAME="${CMAKE_SYSTEM_NAME}"
        LODESTONE_PLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
        LODESTONE_VERSION="${PROJECT_VERSION}${VERSION_SUFFIX}"
        LODESTONE_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
)

# because otherwise jetbrains implodes
# if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#     add_compile_options(
#             "-D_GLIBCXX_DEBUG"
#             "-D_LIBCPP_DEBUG"
#     )
# endif ()

add_custom_target(Lodestone.All ALL DEPENDS
        LodestoneScripts.CheckIncludePaths
        Lodestone.Common
        Lodestone.Level
        Lodestone.Conversion
        Lodestone.Tests
        Lodestone.Java
#        Lodestone.Viewer
)


