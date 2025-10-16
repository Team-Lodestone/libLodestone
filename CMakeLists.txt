cmake_minimum_required(VERSION 4.0)
project(Lodestone VERSION 1.0.0)

set(VERSION_SUFFIX "-dev.6") # used for non-stable versions, otherwise blank
set(CMAKE_CXX_STANDARD 17)

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

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 12.0.0
)

FetchContent_MakeAvailable(fmt)

include_directories(${BIO_SOURCE_DIR})

# PROJECTS
add_subdirectory(projects/Tests)
add_subdirectory(projects/Common)
add_subdirectory(projects/Level)
add_subdirectory(projects/Java)

target_link_libraries(Lodestone.Tests PRIVATE fmt BIO)
target_link_libraries(Lodestone.Common PRIVATE fmt BIO)
target_link_libraries(Lodestone.Level PRIVATE fmt BIO)
target_link_libraries(Lodestone.Java PRIVATE fmt BIO)

# DEFINITIONS
target_compile_definitions(Lodestone.Common PUBLIC
        COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}"
        PLATFORM_NAME="${CMAKE_SYSTEM_NAME}"
        PLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
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


