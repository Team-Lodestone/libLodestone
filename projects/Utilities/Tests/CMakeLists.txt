cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Tests)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(FILES
        src/LodestoneTests.cpp
        include/Lodestone.Tests/util.h
        include/Lodestone.Tests/LodestoneTests.h
        include/Lodestone.Tests/test/Test.h
        src/tests/MainTests.cpp
        include/Lodestone.Tests/tests/MainTests.h
        src/util/Visualizer.cpp
        include/Lodestone.Tests/util/Visualizer.h
)

# NBT
set(NBT_BUILD_TESTS OFF CACHE BOOL "" FORCE)
if (NOT TARGET nbt++)
    FetchContent_Declare(
            nbt++
            GIT_REPOSITORY https://github.com/Team-Lodestone/libnbtplusplus.git
            GIT_TAG master
            GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(nbt++)
endif ()

if (NOT TARGET tfw)
    include(FetchContent)
    FetchContent_Declare(
            tfw
            GIT_REPOSITORY https://codeberg.org/Dexrn/tfw.git
            GIT_TAG 1.2.0
            GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(tfw)
endif ()

add_executable(Lodestone.Tests ${FILES})

if (WIN32)
    target_link_libraries(Lodestone.Tests PRIVATE "-lstdc++exp")
endif ()

target_include_directories(Lodestone.Tests
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Lodestone.Tests PRIVATE Lodestone.Level nbt++ bio-cpp20 tfw)
target_link_libraries(Lodestone.Tests PRIVATE Lodestone.Minecraft.Java Lodestone.Conversion)

get_filename_component(INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/input" ABSOLUTE)
get_filename_component(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/output" ABSOLUTE)

target_compile_definitions(Lodestone.Tests PRIVATE
        LODESTONE_TESTS_INPUT_FOLDER="${INPUT_DIR}"
        LODESTONE_TESTS_OUTPUT_FOLDER="${OUTPUT_DIR}"
)

# Should we allow for exceptions to throw for debugging
target_compile_definitions(Lodestone.Tests PRIVATE
        ALLOW_THROW=true)

# ENABLE TEST GROUPS HERE
target_compile_definitions(Lodestone.Tests PRIVATE
        RUN_MAIN_TESTS=true
)

# ENABLE INDIVIDUAL TESTS HERE
target_compile_definitions(Lodestone.Tests PRIVATE
        GENERATE_WATER_CHUNK=false
        READ_ANVIL_WORLD=false
        WRITE_ANVIL_WORLD=false
        READ_MCR_WORLD=false
        READ_MCR_CHUNK=false
        READ_MCR_FILE=false
        READ_MINEV2_WORLD=false
        READ_ALPHA_WORLD=false
        WRITE_ALPHA_WORLD=false
        READ_INDEV_WORLD=false
        READ_INFDEV_624_WORLD=false
        WRITE_INFDEV_624_WORLD=false
        VISUALIZE_INFDEV_624_WORLD=false
        VISUALIZE_MCR_WORLD=false
        VISUALIZE_ALPHA_WORLD=true
)

setupLinter(Lodestone.Tests)