cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Tests)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(FILES
        src/LodestoneTests.cpp
        include/Lodestone.Tests/util.h
        include/Lodestone.Tests/LodestoneTests.h
        include/Lodestone.Tests/test/Test.h
        src/util/Visualizer.cpp
        include/Lodestone.Tests/util/Visualizer.h
        include/Lodestone.Tests/tests/AlphaTests.h
        src/tests/AlphaTests.cpp
        src/tests/ReleaseTests.cpp
        src/tests/InfdevTests.cpp
        src/tests/Infdev624Tests.cpp
        src/tests/IndevTests.cpp
        src/tests/ClassicTests.cpp
        src/tests/PreclassicTests.cpp
        src/tests/BetaTests.cpp
        include/Lodestone.Tests/tests/BetaTests.h
        include/Lodestone.Tests/tests/ClassicTests.h
        include/Lodestone.Tests/tests/PreclassicTests.h
        include/Lodestone.Tests/tests/ReleaseTests.h
        include/Lodestone.Tests/tests/Infdev624Tests.h
        include/Lodestone.Tests/tests/InfdevTests.h
        include/Lodestone.Tests/tests/IndevTests.h
        include/Lodestone.Tests/tests/InternalTests.h
        src/tests/InternalTests.cpp
        include/Lodestone.Tests/util/ZipUtils.h
        src/util/ZipUtils.cpp
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

if (NOT TARGET minizip)
    include(FetchContent)
    set(MZ_OPENSSL OFF CACHE INTERNAL "")
    FetchContent_Declare(
            minizip
            GIT_REPOSITORY https://github.com/zlib-ng/minizip-ng.git
            GIT_TAG master
            GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(minizip)
endif ()


add_executable(Lodestone.Tests ${FILES})

if (NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    find_package(TBB REQUIRED)

    target_link_libraries(Lodestone.Tests
            PRIVATE
            TBB::tbb
            minizip
    )
else()
    target_link_libraries(Lodestone.Tests
            PRIVATE
            minizip
    )
endif()

if (WIN32)
    target_link_libraries(Lodestone.Tests PRIVATE "-lstdc++exp")
endif ()

target_include_directories(Lodestone.Tests
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Lodestone.Tests PRIVATE Lodestone.Level nbt++ bio-cpp20 tfw)
target_link_libraries(Lodestone.Tests PRIVATE Lodestone.Minecraft.Java Lodestone.Conversion)

get_filename_component(INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/TestResources/input" ABSOLUTE)
get_filename_component(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/TestResources/output" ABSOLUTE)

target_compile_definitions(Lodestone.Tests PRIVATE
        LODESTONE_TESTS_INPUT_FOLDER="${INPUT_DIR}"
        LODESTONE_TESTS_OUTPUT_FOLDER="${OUTPUT_DIR}"
)

# Should we allow for exceptions to throw for debugging
target_compile_definitions(Lodestone.Tests PRIVATE
        ALLOW_THROW=true)

# ENABLE TEST GROUPS HERE
target_compile_definitions(Lodestone.Tests PRIVATE
        RUN_PRECLASSIC_TESTS=true
        RUN_CLASSIC_TESTS=true
        RUN_INDEV_TESTS=true
        RUN_INFDEV_TESTS=true
        RUN_INFDEV624_TESTS=true
        RUN_ALPHA_TESTS=true
        RUN_BETA_TESTS=true
        RUN_RELEASE_TESTS=true
)

# ENABLE INDIVIDUAL TESTS HERE
target_compile_definitions(Lodestone.Tests PRIVATE
        # Preclassic tests
        READ_PRECLASSIC_WORLD_ZERO=false

        # Classic tests
        READ_CLASSIC_WORLD_ZERO=false

        # Indev tests
        READ_INDEV_HUGE_FLOATING=true

        # Infdev 624 tests
        READ_INFDEV_624_WORLD4=false

        # Infdev/Alpha tests
        READ_SNOW_WORLD_ZERO=false
        READ_NETHER_WORLD_ZERO=false

        # Beta tests
        READ_BETA_SERVER_WORLD=false

        # Release tests
        READ_SNOW_RELEASE_WORLD_ZERO=false
)

setupLinter(Lodestone.Tests)