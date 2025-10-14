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
)

add_library(Lodestone.Level SHARED ${FILES})
target_include_directories(Lodestone.Level PUBLIC include src)

target_link_libraries(Lodestone.Level PRIVATE Lodestone.Common)