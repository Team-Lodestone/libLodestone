cmake_minimum_required(VERSION 3.30)
project(Lodestone)

option(LODESTONE_DOCS_TARGET "Create documentation target" ON)
if (LODESTONE_DOCS_TARGET STREQUAL "ON")
    set(LODESTONE_ROOT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    set(LODESTONE_ROOT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

    set(LODESTONE_DOCUMENTATION_TASKS "" CACHE INTERNAL "Documentation Tasks")
    set(LODESTONE_DOCUMENTATION_TAGS "" CACHE INTERNAL "Documentation Tags")
    set(LODESTONE_DOCUMENTATION_TABS "" CACHE INTERNAL "Documentation Tabs")
    set(LODESTONE_DOCUMENTATION_INCLUDE_PATHS "" CACHE INTERNAL "Include Paths")
    set(LODESTONE_AT_ESCAPE "@")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake/linting.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake/doxygen.cmake)

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

# PROJECTS
add_subdirectory(projects/Libraries)
add_subdirectory(projects/Utilities)
add_subdirectory(projects/Converters)

include(${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake/rootDoxygen.cmake)
configureRootDoxygen()
unset(LODESTONE_DOCS_TARGET CACHE)

add_custom_target(Lodestone.All ALL DEPENDS
        Lodestone.Libraries
        Lodestone.Converters
        Lodestone.Utilities
)

