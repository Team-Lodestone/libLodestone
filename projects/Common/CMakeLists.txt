cmake_minimum_required(VERSION 4.0)
project(Lodestone.Common)

set(CMAKE_CXX_STANDARD 17)

set(HEADERS
        include/Lodestone.h
        include/Defines.h
)

set(SOURCES
        src/Lodestone.cpp
)

add_library(Lodestone.Common SHARED ${HEADERS} ${SOURCES})
target_include_directories(Lodestone.Common PUBLIC include src)