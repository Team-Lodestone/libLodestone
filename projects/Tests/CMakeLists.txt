cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Tests)

set(CMAKE_CXX_STANDARD 20)

set(FILES
        src/LodestoneTests.cpp
        include/Lodestone.Tests/util.h
        include/Lodestone.Tests/LodestoneTests.h
        include/Lodestone.Tests/test/Test.h
        src/tests/MainTests.cpp
        include/Lodestone.Tests/tests/MainTests.h
)

# if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#     add_compile_options(
#             "-D_GLIBCXX_DEBUG"
#             "-D_LIBCPP_DEBUG"
#     )
# endif ()

add_executable(Lodestone.Tests ${FILES})
target_include_directories(Lodestone.Tests
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include/Lodestone.Tests
)

target_link_libraries(Lodestone.Tests PRIVATE Lodestone.Level)
target_link_libraries(Lodestone.Tests PRIVATE Lodestone.Java)

# Should we allow for exceptions to throw for debugging
target_compile_definitions(Lodestone.Tests PRIVATE
        ALLOW_THROW=true)

# ENABLE TEST GROUPS HERE
target_compile_definitions(Lodestone.Tests PRIVATE
        RUN_MAIN_TESTS=true
)

# ENABLE INDIVIDUAL TESTS HERE
target_compile_definitions(Lodestone.Tests PRIVATE
        READ_MCR_CHUNK=true
        READ_MCR_FILE=true
)