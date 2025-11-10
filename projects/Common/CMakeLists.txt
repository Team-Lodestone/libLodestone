cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Common)

set(CMAKE_CXX_STANDARD 20)

set(FILES
        include/Lodestone.Common/Lodestone.h
        src/Lodestone.cpp

        include/Lodestone.Common/Defines.h
        include/Lodestone.Common/String/OperatorStringBuilder.h
        include/Lodestone.Common/Constants.h
        include/Lodestone.Common/String/StringSerializable.h
        src/String/OperatorStringBuilder.cpp
        include/Lodestone.Common/io/DataBuffer.cpp
        include/Lodestone.Common/io/DataBuffer.h
)

# hm I wonder if there will be problems if I link against 2 libs that both compile this
add_library(Lodestone.Common OBJECT ${FILES})
target_include_directories(Lodestone.Common
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Lodestone.Common
)