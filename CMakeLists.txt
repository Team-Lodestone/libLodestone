cmake_minimum_required(VERSION 3.30)
project(Lodestone)

include(${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake/linting.cmake)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DCMAKE_BUILD_DEBUG)
endif ()

option(BIO_TESTS "Build libBIO tests" OFF)

# BIO
if (NOT TARGET bio)
    include(FetchContent)
    FetchContent_Declare(
            bio
            GIT_REPOSITORY https://codeberg.org/Dexrn/libBIO.git
            GIT_TAG 4.0.0-dev.3
    )

    FetchContent_MakeAvailable(bio)
endif()

# PROJECTS
add_subdirectory(projects/Libraries)
add_subdirectory(projects/Utilities)
add_subdirectory(projects/Converters)

add_custom_target(Lodestone.All ALL DEPENDS
        Lodestone.Libraries
        Lodestone.Converters
#        Lodestone.Utilities
)


