cmake_minimum_required(VERSION 4.0)
project(Lodestone.Level)

set(CMAKE_CXX_STANDARD 17)

set(FILES
        include/Level.h
        src/Level.cpp

        include/Chunk/ChunkCoords.h
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
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
            "-D_GLIBCXX_DEBUG"
    )
endif ()

add_library(Lodestone.Level SHARED ${FILES})
target_include_directories(Lodestone.Level PUBLIC include src)

target_link_libraries(Lodestone.Level PRIVATE Lodestone.Common)