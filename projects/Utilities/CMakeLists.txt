cmake_minimum_required(VERSION 3.30)
project(Lodestone.Utilities VERSION 1.0.2)

set(LODESTONE_UTILITIES_PROJECTS )

# PROJECTS
option(LODESTONE_UTILITIES_BUILD_TESTS "Build Lodestone.Tests" ON)

if (LODESTONE_UTILITIES_BUILD_TESTS)
    add_subdirectory(Tests)
    list(APPEND LODESTONE_UTILITIES_PROJECTS
            Lodestone.Tests
    )
endif()

unset(LODESTONE_UTILITIES_BUILD_TESTS CACHE)

if (BUILD_VIEWER STREQUAL "ON")
    add_subdirectory(Viewer)
    list(APPEND LODESTONE_UTILITIES_PROJECTS
            Lodestone.Viewer
    )
endif()

message(STATUS "Lodestone.Utilities: ${LODESTONE_UTILITIES_PROJECTS}")
add_custom_target(Lodestone.Utilities ALL DEPENDS
        ${LODESTONE_UTILITIES_BUILD_TESTS}
)