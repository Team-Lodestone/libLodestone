cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Conversion)

set(CMAKE_CXX_STANDARD 20)

OPTION(USE_FALLBACK_BLOCK "Use fallback block when conversion of a block fails" ON)

set(FILES
        src/chunk/ChunkIORegistry.cpp
        include/Lodestone.Conversion/chunk/ChunkIORegistry.h
        src/chunk/ChunkIO.cpp
        include/Lodestone.Conversion/chunk/ChunkIO.h
        src/level/LevelIORegistry.cpp
        include/Lodestone.Conversion/level/LevelIORegistry.h
        src/level/LevelIO.cpp
        include/Lodestone.Conversion/level/LevelIO.h
        src/player/PlayerIORegistry.cpp
        include/Lodestone.Conversion/player/PlayerIORegistry.h
        src/player/PlayerIO.cpp
        include/Lodestone.Conversion/player/PlayerIO.h
        src/world/WorldIO.cpp
        include/Lodestone.Conversion/world/WorldIO.h
        src/world/WorldIORegistry.cpp
        include/Lodestone.Conversion/world/WorldIORegistry.h
        include/Lodestone.Conversion/region/RegionIO.h
        src/region/RegionIORegistry.cpp
        include/Lodestone.Conversion/region/RegionIORegistry.h
        include/Lodestone.Conversion/block/VersionedBlockIO.h
        include/Lodestone.Conversion/block/BlockIO.h
        src/block/BlockIO.cpp
        include/Lodestone.Conversion/block/data/NumericBlockData.h
        include/Lodestone.Conversion/block/data/ClassicBlockData.h
        src/block/data/ClassicBlockData.cpp
        include/Lodestone.Conversion/block/data/FlattenedBlockData.h
        src/block/data/FlattenedBlockData.cpp
        include/Lodestone.Conversion/block/data/AbstractBlockData.h
        src/block/data/NumericBlockData.cpp
        src/block/VersionedBlockIO.cpp
        include/Lodestone.Conversion/world/FileWorldIo.h
        include/Lodestone.Conversion/world/DirectoryWorldIo.h
        include/Lodestone.Conversion/Identifiers.h
        include/Lodestone.Conversion/types/hash/BlockDataHash.h
)

# if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#     add_compile_options(
#             "-D_GLIBCXX_DEBUG"
#             "-D_LIBCPP_DEBUG"
#     )
# endif ()

add_library(Lodestone.Conversion SHARED ${FILES})
target_include_directories(Lodestone.Conversion
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Lodestone.Conversion PUBLIC Lodestone.Common Lodestone.Level)

if (USE_FALLBACK_BLOCK STREQUAL ON)
    target_compile_definitions(Lodestone.Conversion PRIVATE USE_FALLBACK_BLOCK)
endif ()