cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Level)

set(CMAKE_CXX_STANDARD 20)

OPTION(USE_FALLBACK_BLOCK "Use fallback block when conversion of a block fails" ON)

set(FILES
        include/Lodestone.Level/Level.h
        src/Level.cpp

        include/Lodestone.Level/types/Vec2.h
        src/chunk/Chunk.cpp
        include/Lodestone.Level/chunk/Chunk.h
        include/Lodestone.Level/types/Vec3.h
        src/block/Block.cpp

        include/Lodestone.Level/block/Block.h
        include/Lodestone.Level/block/BlockRegistry.h
        src/material/Material.cpp
        include/Lodestone.Level/material/Material.h
        include/Lodestone.Level/types/Color.h
        src/block/BlockRegistry.cpp
        src/material/MaterialRegistry.cpp
        include/Lodestone.Level/material/MaterialRegistry.h
        src/block/state/BlockState.cpp
        include/Lodestone.Level/block/state/BlockState.h
        src/chunk/section/EmptySection.cpp
        include/Lodestone.Level/chunk/section/EmptySection.h
        src/chunk/section/Section.cpp
        include/Lodestone.Level/chunk/section/Section.h
        include/Lodestone.Level/chunk/section/LevelSection.h
        src/chunk/section/LevelSection.cpp
        include/Lodestone.Level/chunk/section/LevelSection.h
        include/Lodestone.Level/chunk/LevelChunk.h
        src/chunk/LevelChunk.cpp
        include/Lodestone.Level/chunk/LevelChunk.h
        src/chunk/EmptyChunk.cpp
        include/Lodestone.Level/chunk/EmptyChunk.h
        src/conversion/chunk/ChunkIORegistry.cpp
        include/Lodestone.Level/conversion/chunk/ChunkIORegistry.h
        src/conversion/chunk/ChunkIO.cpp
        include/Lodestone.Level/conversion/chunk/ChunkIO.h
        src/conversion/level/LevelIORegistry.cpp
        include/Lodestone.Level/conversion/level/LevelIORegistry.h
        src/conversion/level/LevelIO.cpp
        include/Lodestone.Level/conversion/level/LevelIO.h
        src/world/World.cpp
        include/Lodestone.Level/world/World.h
        src/conversion/world/WorldIO.cpp
        include/Lodestone.Level/conversion/world/WorldIO.h
        src/conversion/world/WorldIORegistry.cpp
        include/Lodestone.Level/conversion/world/WorldIORegistry.h
        include/Lodestone.Level/conversion/region/RegionIO.h
        src/conversion/region/RegionIORegistry.cpp
        include/Lodestone.Level/conversion/region/RegionIORegistry.h
        include/Lodestone.Level/types/Bounds3.h
        include/Lodestone.Level/types/Bounds2.h
        include/Lodestone.Level/block/Blocks.h
        include/Lodestone.Level/conversion/block/VersionedBlockIO.h
        include/Lodestone.Level/conversion/block/BlockIO.h
        src/conversion/block/BlockIO.cpp
        include/Lodestone.Level/conversion/block/data/NumericBlockData.h
        include/Lodestone.Level/conversion/block/data/ClassicBlockData.h
        src/conversion/block/data/ClassicBlockData.cpp
        include/Lodestone.Level/conversion/block/data/FlattenedBlockData.h
        src/conversion/block/data/FlattenedBlockData.cpp
        include/Lodestone.Level/conversion/block/data/AbstractBlockData.h
        src/conversion/block/data/NumericBlockData.cpp
        src/conversion/block/VersionedBlockIO.cpp
        include/Lodestone.Level/types/hash/BlockDataHash.h
        include/Lodestone.Level/conversion/world/FileWorldIo.h
        include/Lodestone.Level/conversion/world/DirectoryWorldIo.h
        src/region/Region.cpp
        include/Lodestone.Level/region/Region.h
        src/chunk/ChunkContainer.cpp
        include/Lodestone.Level/chunk/ChunkContainer.h
        src/FiniteLevel.cpp
        include/Lodestone.Level/FiniteLevel.h
        include/Lodestone.Level/Identifiers.h
        src/player/Player.cpp
        include/Lodestone.Level/player/Player.h
)

# if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#     add_compile_options(
#             "-D_GLIBCXX_DEBUG"
#             "-D_LIBCPP_DEBUG"
#     )
# endif ()

add_library(Lodestone.Level SHARED ${FILES})
target_include_directories(Lodestone.Level
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Lodestone.Level
)

target_link_libraries(Lodestone.Level PUBLIC Lodestone.Common)

if (USE_FALLBACK_BLOCK)
    target_compile_definitions(Lodestone.Level PRIVATE USE_FALLBACK_BLOCK)
endif ()