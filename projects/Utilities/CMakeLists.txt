cmake_minimum_required(VERSION 3.30)
project(Lodestone.Utilities VERSION 1.0.2)

# PROJECTS
option(LODESTONE_UTILITIES_BUILD_TESTS "Build Lodestone.Tests" ON)

if (LODESTONE_UTILITIES_BUILD_TESTS)
    add_subdirectory(Tests)
endif()

unset(LODESTONE_UTILITIES_BUILD_TESTS CACHE)

if (BUILD_VIEWER STREQUAL "ON")
    add_subdirectory(Viewer)
endif()

#add_custom_target(Lodestone.Utilities ALL DEPENDS
#        Lodestone.Tests
#)