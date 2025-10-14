cmake_minimum_required(VERSION 4.0)
project(Lodestone.Level)

set(CMAKE_CXX_STANDARD 17)

set(HEADERS
        include/Level.h
)

set(SOURCES
        src/Level.cpp
)

add_library(Lodestone.Level SHARED ${HEADERS} ${SOURCES})
target_include_directories(Lodestone.Level PUBLIC include src)
target_link_libraries(Lodestone.Level PRIVATE Lodestone.Common)