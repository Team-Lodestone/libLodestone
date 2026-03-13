cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Conversion)

set(CMAKE_CXX_STANDARD 20)

OPTION(USE_FALLBACK_BLOCK "Use fallback block when conversion of a block fails" ON)

set(FILES
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
        include/Lodestone.Conversion/Identifiers.h
        src/block/data/ExtendedNumericBlockData.cpp
        include/Lodestone.Conversion/block/data/ExtendedNumericBlockData.h
        include/Lodestone.Conversion/registry/SimpleRegistry.h
        include/Lodestone.Conversion/registry/SimpleRegistry.tpp
        include/Lodestone.Conversion/io/AbstractObjectIo.h
        include/Lodestone.Conversion/io/types/Writable.h
        include/Lodestone.Conversion/io/types/Readable.h
        include/Lodestone.Conversion/io/options/versioned/VersionedOptions.h
        include/Lodestone.Conversion/io/options/fs/file/FileWriterOptions.h
        include/Lodestone.Conversion/io/options/fs/file/FileReaderOptions.h
        include/Lodestone.Conversion/io/IObjectIo.h
        include/Lodestone.Conversion/io/types/ReadableAdapter.h
        include/Lodestone.Conversion/io/types/WritableAdapter.h
        include/Lodestone.Conversion/io/interfaces/IPlayerIo.h
        include/Lodestone.Conversion/io/interfaces/IRegionIo.h
        include/Lodestone.Conversion/io/interfaces/ILevelIo.h
        include/Lodestone.Conversion/io/interfaces/IWorldIo.h
        include/Lodestone.Conversion/io/interfaces/IChunkIo.h
        include/Lodestone.Conversion/io/options/OptionsBuilder.h
        include/Lodestone.Conversion/registry/Registries.h
        include/Lodestone.Conversion/registry/RegistryRelations.h
        include/Lodestone.Conversion/io/options/fs/FilesystemPathOptions.h
        include/Lodestone.Conversion/registry/SingletonRegistry.h
        include/Lodestone.Conversion/io/ObjectIOs.h
        src/registry/Registries.cpp
)

add_library(Lodestone.Conversion SHARED ${FILES})
target_include_directories(Lodestone.Conversion
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Lodestone.Conversion PUBLIC Lodestone.Common Lodestone.Level msft_proxy4::proxy)

if (USE_FALLBACK_BLOCK STREQUAL ON)
    target_compile_definitions(Lodestone.Conversion PRIVATE USE_FALLBACK_BLOCK)
endif ()
setupLinter(Lodestone.Conversion)