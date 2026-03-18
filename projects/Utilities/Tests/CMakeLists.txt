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
)

# NBT
if (NOT nbt++_FOUND)
set(NBT_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
        nbt++
        GIT_REPOSITORY https://github.com/Team-Lodestone/libnbtplusplus.git
        GIT_TAG master
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(nbt++)
endif()

include(FetchContent)
FetchContent_Declare(
        tfw
        GIT_REPOSITORY https://codeberg.org/Dexrn/tfw.git
        GIT_TAG 1.0.1
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(tfw)

add_executable(Lodestone.Tests ${FILES})
target_include_directories(Lodestone.Tests
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Lodestone.Tests PRIVATE Lodestone.Level nbt++ bio-cpp20 tfw)
target_link_libraries(Lodestone.Tests PRIVATE Lodestone.Minecraft.Java Lodestone.Conversion)

# Should we allow for exceptions to throw for debugging
target_compile_definitions(Lodestone.Tests PRIVATE
        ALLOW_THROW=true)

# ENABLE TEST GROUPS HERE
target_compile_definitions(Lodestone.Tests PRIVATE
        RUN_MAIN_TESTS=true
)

# ENABLE INDIVIDUAL TESTS HERE
target_compile_definitions(Lodestone.Tests PRIVATE
        GENERATE_WATER_CHUNK=true
        READ_ANVIL_WORLD=false
        WRITE_ANVIL_WORLD=true
        READ_MCR_WORLD=false
        READ_MCR_CHUNK=false
        READ_MCR_FILE=false
        READ_MINEV2_WORLD=false
        READ_ALPHA_WORLD=false
        WRITE_ALPHA_WORLD=false
)

setupLinter(Lodestone.Tests)