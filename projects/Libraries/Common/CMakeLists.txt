cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Common)

set(CMAKE_CXX_STANDARD 20)

set(FILES
        include/Lodestone.Common/LodestoneCommon.h
        src/LodestoneCommon.cpp

        include/Lodestone.Common/Defines.h
        include/Lodestone.Common/string/OperatorStringBuilder.h
        include/Lodestone.Common/registry/Identifier.h
        include/Lodestone.Common/Indexing.h
        include/Lodestone.Common/Constants.h
        include/Lodestone.Common/string/StringSerializable.h
        src/io/DataBuffer.cpp
        include/Lodestone.Common/io/DataBuffer.h
        src/util/Math.cpp
        include/Lodestone.Common/util/Math.h
        include/Lodestone.Common/util/Logging.h
)

add_library(Lodestone.Common OBJECT ${FILES})
target_link_libraries(Lodestone.Common PRIVATE gtl)
target_include_directories(Lodestone.Common
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
setupLinter(Lodestone.Common)