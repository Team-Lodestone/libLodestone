cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Level)

set(CMAKE_CXX_STANDARD 20)

set(FILES
        include/Lodestone.Level/Level.h
        src/Level.cpp

        include/Lodestone.Level/types/Vec2.h
        src/chunk/Chunk.cpp
        include/Lodestone.Level/chunk/Chunk.h
        include/Lodestone.Level/types/Vec3.h
        src/block/Block.cpp

        include/Lodestone.Level/block/Block.h
        src/material/Material.cpp
        include/Lodestone.Level/material/Material.h
        include/Lodestone.Level/types/Color.h
        include/Lodestone.Level/block/BlockRegistry.h
        src/block/BlockRegistry.cpp
        include/Lodestone.Level/item/ItemRegistry.h
        src/item/ItemRegistry.cpp
        src/material/MaterialRegistry.cpp
        include/Lodestone.Level/material/MaterialRegistry.h
        src/block/instance/BlockInstance.cpp
        include/Lodestone.Level/block/instance/BlockInstance.h
        src/chunk/section/EmptySection.cpp
        include/Lodestone.Level/chunk/section/ImmutableSection.h
        src/chunk/section/Section.cpp
        include/Lodestone.Level/chunk/section/Section.h
        include/Lodestone.Level/chunk/section/LevelSection.h
        src/chunk/section/LevelSection.cpp
        include/Lodestone.Level/chunk/section/LevelSection.h
        include/Lodestone.Level/chunk/LevelChunk.h
        src/chunk/LevelChunk.cpp
        include/Lodestone.Level/chunk/LevelChunk.h
        src/chunk/EmptyChunk.cpp
        include/Lodestone.Level/chunk/ImmutableChunk.h

        src/world/World.cpp
        include/Lodestone.Level/world/World.h

        include/Lodestone.Level/types/Bounds3.h
        include/Lodestone.Level/types/Bounds2.h
        include/Lodestone.Level/block/Blocks.h
        src/region/Region.cpp
        include/Lodestone.Level/region/Region.h
        src/chunk/ChunkContainer.cpp
        include/Lodestone.Level/chunk/ChunkContainer.h
        src/FiniteLevel.cpp
        include/Lodestone.Level/FiniteLevel.h
        src/entity/Player.cpp
        include/Lodestone.Level/entity/Player.h
        src/entity/Entity.cpp
        include/Lodestone.Level/entity/Entity.h
        src/entity/LevelEntity.cpp
        include/Lodestone.Level/entity/ChunkEntity.h
        include/Lodestone.Level/entity/Entities.h
        src/container/ItemContainer.cpp
        include/Lodestone.Level/container/ItemContainer.h
        src/item/Item.cpp
        include/Lodestone.Level/item/Item.h
        src/item/block/BlockItem.cpp
        include/Lodestone.Level/item/block/BlockItem.h
        src/item/ItemInstance.cpp
        include/Lodestone.Level/item/ItemInstance.h
        include/Lodestone.Level/properties/AbstractProperty.h
        include/Lodestone.Level/Identifiers.h
        include/Lodestone.Level/properties/TemplatedProperty.h
        include/Lodestone.Level/item/Items.h
        src/block/instance/ImmutableBlockInstance.cpp
        include/Lodestone.Level/block/instance/ImmutableBlockInstance.h
        include/Lodestone.Level/properties/ReflectiveProperties.h
        src/properties/ReflectiveProperties.cpp
        include/Lodestone.Level/block/blocks/TranslucentBlock.h
        include/Lodestone.Level/block/blocks/AirBlock.h
        include/Lodestone.Level/entity/WorldSpaceObject.cpp
        include/Lodestone.Level/entity/WorldSpaceObject.h
        include/Lodestone.Level/properties/definition/ObjectDefinition.h
        src/properties/definition/ObjectDefinition.cpp
        include/Lodestone.Level/LodestoneLevel.h
        src/LodestoneLevel.cpp
        include/Lodestone.Level/internal/Exports.h
)

# if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#     add_compile_options(
#             "-D_GLIBCXX_DEBUG"
#             "-D_LIBCPP_DEBUG"
#     )
# endif ()

add_library(Lodestone.Level SHARED ${FILES})
target_include_directories(Lodestone.Level PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Lodestone.Level PUBLIC Lodestone.Common gtl)

setupExports(Lodestone.Level)
setupLinter(Lodestone.Level)