cmake_minimum_required(VERSION 3.30)
project(Lodestone.Core)

set(CMAKE_CXX_STANDARD 20)

set(FILES
        include/Lodestone.Core/Lodestone.h
        src/Lodestone.cpp
        src/LodestoneExtension.cpp
        include/Lodestone.Core/LodestoneExtension.h
        include/Lodestone.Core/loader/ExtensionLoader.h
        include/Lodestone.Core/loader/NativeExtensionLoader.h
        include/Lodestone.Core/loader/LibraryHandle.h
        src/loader/ExtensionLoader.cpp
        src/loader/NativeExtensionLoader.cpp
        src/loader/LibraryHandle.cpp
)

add_library(Lodestone.Core SHARED ${FILES})
target_include_directories(Lodestone.Core PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(Lodestone.Core PRIVATE Lodestone.Common gtl)
setupLinter(Lodestone.Core)