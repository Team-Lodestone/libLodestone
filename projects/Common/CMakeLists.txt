cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Common)

set(CMAKE_CXX_STANDARD 20)

set(FILES
        include/Lodestone.Common/LodestoneCommon.h
        src/LodestoneCommon.cpp

        include/Lodestone.Common/Defines.h
        include/Lodestone.Common/string/OperatorStringBuilder.h
        include/Lodestone.Common/registry/NamespacedString.h
        include/Lodestone.Common/Indexing.h
        include/Lodestone.Common/Constants.h
        include/Lodestone.Common/string/StringSerializable.h
        src/string/OperatorStringBuilder.cpp
        src/io/DataBuffer.cpp
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