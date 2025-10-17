cmake_minimum_required(VERSION 4.0)
project(Lodestone.Level)

set(CMAKE_CXX_STANDARD 17)

set(FILES
        include/Level.h
        src/Level.cpp

        include/Types/Vec2i.h
        src/Chunk/Chunk.cpp
        include/Chunk/Chunk.h
        include/Types/Vec3i.h
        include/Indexing.h
        src/Block/Block.cpp

        include/Block/Block.h
        include/Block/Blocks.h
        src/Material/Material.cpp
        include/Material/Material.h
        include/Types/Color.h
        src/Block/Blocks.cpp
        src/Material/Materials.cpp
        include/Material/Materials.h
        src/Block/State/BlockState.cpp
        include/Block/State/BlockState.h
        src/Chunk/Section/EmptySection.cpp
        include/Chunk/Section/EmptySection.h
        src/Chunk/Section/Section.cpp
        include/Chunk/Section/Section.h
        include/Chunk/Section/LevelSection.h
        src/Chunk/Section/LevelSection.cpp
        include/Chunk/Section/LevelSection.h
        include/Chunk/LevelChunk.h
        src/Chunk/LevelChunk.cpp
        include/Chunk/LevelChunk.h
        src/Chunk/EmptyChunk.cpp
        include/Chunk/EmptyChunk.h
        src/Conversion/Chunk/ChunkIORegistry.cpp
        include/Conversion/Chunk/ChunkIORegistry.h
        src/Conversion/Chunk/ChunkIO.cpp
        include/Conversion/Chunk/ChunkIO.h
        src/Conversion/Level/LevelIORegistry.cpp
        include/Conversion/Level/LevelIORegistry.h
        src/Conversion/Level/LevelIO.cpp
        include/Conversion/Level/LevelIO.h
        src/Conversion/Block/BlockIo.cpp
        include/Conversion/Block/BlockIo.h
        src/World/World.cpp
        include/World/World.h
        src/Conversion/World/WorldIo.cpp
        include/Conversion/World/WorldIo.h
        src/Conversion/World/WorldIoRegistry.cpp
        include/Conversion/World/WorldIoRegistry.h
        src/Types/Colors.cpp
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
            "-D_GLIBCXX_DEBUG"
    )
endif ()

add_library(Lodestone.Level SHARED ${FILES})
target_include_directories(Lodestone.Level PUBLIC include)

target_link_libraries(Lodestone.Level PRIVATE Lodestone.Common)