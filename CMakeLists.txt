cmake_minimum_required(VERSION 4.0)
project(Lodestone VERSION 1.0.0)

set(VERSION_SUFFIX "-dev.0") # used for non-stable versions, otherwise blank
set(CMAKE_CXX_STANDARD 17)

# DEFINITIONS
add_definitions(-DCOMPILER_NAME="${CMAKE_CXX_COMPILER_ID}")
add_definitions(-DPLATFORM_NAME="${CMAKE_SYSTEM_NAME}")
add_definitions(-DPLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}")

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

include_directories(${BIO_SOURCE_DIR})

# PROJECTS
add_subdirectory(projects/Common)
add_subdirectory(projects/Level)

# VERSION
target_compile_definitions(Lodestone.Common PRIVATE
        LODESTONE_VERSION="${PROJECT_VERSION}${VERSION_SUFFIX}"
        LODESTONE_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
)


