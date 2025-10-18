cmake_minimum_required(VERSION 4.0)
project(Lodestone.Level)

set(CMAKE_CXX_STANDARD 20)

OPTION(USE_FALLBACK_BLOCK "Use fallback block when conversion of a block fails" ON)

set(FILES
        include/Lodestone.Level/Level.h
        src/Level.cpp

        include/Lodestone.Level/Types/Vec2i.h
        src/Chunk/Chunk.cpp
        include/Lodestone.Level/Chunk/Chunk.h
        include/Lodestone.Level/Types/Vec3i.h
        include/Lodestone.Level/Indexing.h
        src/Block/Block.cpp

        include/Lodestone.Level/Block/Block.h
        include/Lodestone.Level/Block/BlockRegistry.h
        src/Material/Material.cpp
        include/Lodestone.Level/Material/Material.h
        include/Lodestone.Level/Types/Color.h
        src/Block/BlockRegistry.cpp
        src/Material/MaterialRegistry.cpp
        include/Lodestone.Level/Material/MaterialRegistry.h
        src/Block/State/BlockState.cpp
        include/Lodestone.Level/Block/State/BlockState.h
        src/Chunk/Section/EmptySection.cpp
        include/Lodestone.Level/Chunk/Section/EmptySection.h
        src/Chunk/Section/Section.cpp
        include/Lodestone.Level/Chunk/Section/Section.h
        include/Lodestone.Level/Chunk/Section/LevelSection.h
        src/Chunk/Section/LevelSection.cpp
        include/Lodestone.Level/Chunk/Section/LevelSection.h
        include/Lodestone.Level/Chunk/LevelChunk.h
        src/Chunk/LevelChunk.cpp
        include/Lodestone.Level/Chunk/LevelChunk.h
        src/Chunk/EmptyChunk.cpp
        include/Lodestone.Level/Chunk/EmptyChunk.h
        src/Conversion/Chunk/ChunkIORegistry.cpp
        include/Lodestone.Level/Conversion/Chunk/ChunkIORegistry.h
        src/Conversion/Chunk/ChunkIO.cpp
        include/Lodestone.Level/Conversion/Chunk/ChunkIO.h
        src/Conversion/Level/LevelIORegistry.cpp
        include/Lodestone.Level/Conversion/Level/LevelIORegistry.h
        src/Conversion/Level/LevelIO.cpp
        include/Lodestone.Level/Conversion/Level/LevelIO.h
        src/Conversion/Block/BlockIO.cpp
        include/Lodestone.Level/Conversion/Block/BlockIO.h
        src/World/World.cpp
        include/Lodestone.Level/World/World.h
        src/Conversion/World/WorldIO.cpp
        include/Lodestone.Level/Conversion/World/WorldIO.h
        src/Conversion/World/WorldIORegistry.cpp
        include/Lodestone.Level/Conversion/World/WorldIORegistry.h
        include/Lodestone.Level/Types/Bounds.h
        include/Lodestone.Level/Block/Blocks.h
        include/Lodestone.Level/Registry/NamespacedString.h
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
            "-D_GLIBCXX_DEBUG"
    )
endif ()

if (USE_FALLBACK_BLOCK)
    add_compile_definitions(USE_FALLBACK_BLOCK)
endif()

add_library(Lodestone.Level SHARED ${FILES})
target_include_directories(Lodestone.Level
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include/Lodestone.Level
)

target_link_libraries(Lodestone.Level PUBLIC Lodestone.Common)