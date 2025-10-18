cmake_minimum_required(VERSION 4.0)
project(Lodestone.Tests)

set(CMAKE_CXX_STANDARD 20)

set(FILES
    src/Tests.cpp
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
            "-D_GLIBCXX_DEBUG"
    )
endif ()

add_executable(Lodestone.Tests ${FILES})
target_include_directories(Lodestone.Tests
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include/Lodestone.Tests
)

target_link_libraries(Lodestone.Tests PRIVATE Lodestone.Level)
target_link_libraries(Lodestone.Tests PRIVATE Lodestone.Java)
