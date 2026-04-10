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

add_library(Lodestone.Minecraft.Console SHARED ${FILES})
target_include_directories(Lodestone.Minecraft.Console
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Lodestone.Minecraft.Console PRIVATE Lodestone.Level Lodestone.Conversion nbt++ bio-cpp20)
target_link_libraries(Lodestone.Minecraft.Console PUBLIC Lodestone.Core Lodestone.Minecraft.Common)

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

#None/TBB/STL-TBB/OpenMP/STL
set(THREADING_TYPE TBB CACHE STRING "Threading type")
set(APPLIED_THREADING_TYPE "None")
set(APPLIED_THREADING_TYPE_ID 0)

message(STATUS "Attempting to use threading type ${THREADING_TYPE}")

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (THREADING_TYPE STREQUAL "TBB")
        find_package(TBB)

        if (TBB_FOUND)
            set(APPLIED_THREADING_TYPE "TBB")
            set(APPLIED_THREADING_TYPE_ID 1)

            target_link_libraries(Lodestone.Minecraft.Console PRIVATE TBB::tbb)
        endif ()
    elseif (THREADING_TYPE STREQUAL "STL-TBB" AND TBB_FOUND)
        find_package(TBB)

        if (TBB_FOUND)
            set(APPLIED_THREADING_TYPE "STL-TBB")
            set(APPLIED_THREADING_TYPE_ID 2)

            target_link_libraries(Lodestone.Minecraft.Console PRIVATE TBB::tbb)
        endif ()
    elseif (THREADING_TYPE STREQUAL "OpenMP")
        find_package(OpenMP COMPONENTS C CXX)

        if (OpenMP_CXX_FOUND AND OpenMP_C_FOUND)
            set(APPLIED_THREADING_TYPE "OpenMP")
            set(APPLIED_THREADING_TYPE_ID 3)

            target_link_libraries(Lodestone.Minecraft.Console PRIVATE OpenMP::OpenMP_CXX)
        endif ()
    elseif (THREADING_TYPE STREQUAL "STL")
        set(APPLIED_THREADING_TYPE "STL")
        set(APPLIED_THREADING_TYPE_ID 4)
    endif ()
endif ()

message(STATUS "Using threading type ${APPLIED_THREADING_TYPE}")
target_compile_definitions(Lodestone.Minecraft.Console PRIVATE
        LODESTONE_MINECRAFT_CONSOLE_THREADING_TYPE=${APPLIED_THREADING_TYPE_ID}
)

unset(THREADING_TYPE CACHE)

option(ENABLE_RISKY_OPTIMIZATIONS "Enable risky optimizations" ON)
if (ENABLE_RISKY_OPTIMIZATIONS STREQUAL ON)
    target_compile_definitions(Lodestone.Minecraft.Console PRIVATE USE_RISKY_OPTIMIZATIONS)
endif ()
unset(ENABLE_RISKY_OPTIMIZATIONS CACHE)

setupLinter(Lodestone.Minecraft.Console)
setupDoxygen()
