cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Common)

set(CMAKE_CXX_STANDARD 23)

set(FILES
        include/Lodestone.Common/LodestoneCommon.h
        src/LodestoneCommon.cpp

        include/Lodestone.Common/Defines.h
        include/Lodestone.Common/registry/Identifier.h
        include/Lodestone.Common/Indexing.h
        include/Lodestone.Common/Constants.h
        include/Lodestone.Common/string/StringSerializable.h
        src/io/DataBuffer.cpp
        include/Lodestone.Common/io/DataBuffer.h
        src/util/Math.cpp
        include/Lodestone.Common/util/Math.h
        include/Lodestone.Common/util/Logging.h
        src/storage/bits/BitStorage.cpp
        include/Lodestone.Common/storage/bits/BitStorage.h
        include/Lodestone.Common/storage/bits/ImmutableBitStorage.h
        src/storage/bits/ImmutableBitStorage.cpp
        src/storage/bits/AbstractBitStorage.cpp
        include/Lodestone.Common/storage/bits/AbstractBitStorage.h
        include/Lodestone.Common/storage/palette/PalletizedStorage.tpp
        include/Lodestone.Common/storage/palette/PalletizedStorage.h
        include/Lodestone.Common/exception/PaletteIndexTooLargeException.h
        include/Lodestone.Common/exception/InvalidPaletteReferenceCountException.h
        include/Lodestone.Common/registry/Identifiable.h
        include/Lodestone.Common/util/Concepts.h
        include/Lodestone.Common/util/Util.h
        include/Lodestone.Common/event/Event.h
        include/Lodestone.Common/event/Cancellable.h
        src/util/Util.cpp
)

add_library(Lodestone.Common OBJECT ${FILES})
target_link_libraries(Lodestone.Common PRIVATE gtl)
target_include_directories(Lodestone.Common
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
setupLinter(Lodestone.Common)