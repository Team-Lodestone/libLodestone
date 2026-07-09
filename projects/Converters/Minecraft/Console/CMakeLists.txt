cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Minecraft.Console VERSION 1.0.0)
set(PROJECT_VERSION_DEV 1) # used for dev versions, otherwise blank

set(LODESTONE_PROJECT_DESCRIPTION "Minecraft: Legacy Console Edition converters")

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(FILES
        src/LodestoneLce.cpp
        include/Lodestone.Minecraft.Console/LodestoneLce.h

)

if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    add_library(Lodestone.Minecraft.Console STATIC ${FILES})
else()
    add_library(Lodestone.Minecraft.Console SHARED ${FILES})
endif()
target_include_directories(Lodestone.Minecraft.Console
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Lodestone.Minecraft.Console PRIVATE Lodestone.Level Lodestone.Conversion nbt++ bio-cpp20)
target_link_libraries(Lodestone.Minecraft.Console PUBLIC Lodestone.Core Lodestone.Minecraft.Common Lodestone.Threading)

set(VERSIONS
        MAJOR
        MINOR
        PATCH
        DEV
)

foreach(k IN LISTS VERSIONS)
    if (DEFINED PROJECT_VERSION_${k})
        target_compile_definitions(Lodestone.Minecraft.Console PUBLIC
                LODESTONE_MINECRAFT_CONSOLE_${k}_VERSION=${PROJECT_VERSION_${k}}
        )
    else()
        target_compile_definitions(Lodestone.Minecraft.Console PUBLIC
                LODESTONE_MINECRAFT_CONSOLE_${k}_VERSION=-1
        )
    endif()
endforeach ()

option(ENABLE_RISKY_OPTIMIZATIONS "Enable risky optimizations" ON)
if (ENABLE_RISKY_OPTIMIZATIONS STREQUAL ON)
    target_compile_definitions(Lodestone.Minecraft.Console PRIVATE USE_RISKY_OPTIMIZATIONS)
endif ()
unset(ENABLE_RISKY_OPTIMIZATIONS CACHE)

setupLinter(Lodestone.Minecraft.Console)
setupDoxygen()
