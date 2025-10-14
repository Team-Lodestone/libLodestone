cmake_minimum_required(VERSION 4.0)
project(Lodestone.Common)

set(CMAKE_CXX_STANDARD 17)

set(FILES
        include/Lodestone.h
        src/Lodestone.cpp

        include/Defines.h
)

# hm I wonder if there will be problems if I link against 2 libs that both compile this
add_library(Lodestone.Common OBJECT ${FILES})
target_include_directories(Lodestone.Common PUBLIC include src)