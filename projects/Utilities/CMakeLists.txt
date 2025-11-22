cmake_minimum_required(VERSION 3.30)
project(Lodestone.Utilities VERSION 1.0.0)

# PROJECTS
add_subdirectory(Tests)
if (BUILD_VIEWER STREQUAL "ON")
    add_subdirectory(Viewer)
endif()

add_custom_target(Lodestone.Utilities ALL DEPENDS
        Lodestone.Tests
)