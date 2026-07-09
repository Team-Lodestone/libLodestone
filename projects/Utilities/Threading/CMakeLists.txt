cmake_minimum_required(VERSION VERSION 3.30)
project(Lodestone.Threading)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(Lodestone.Threading INTERFACE)

#None/TBB/STL-TBB/OpenMP/STL
set(THREADING_TYPE TBB CACHE STRING "Threading type")
set(APPLIED_THREADING_TYPE "None")
set(APPLIED_THREADING_TYPE_ID 0)

message(STATUS "Attempting to use threading type ${THREADING_TYPE}")

if (NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        if (THREADING_TYPE STREQUAL "TBB")
            find_package(TBB)

            if (TBB_FOUND)
                set(APPLIED_THREADING_TYPE "TBB")
                set(APPLIED_THREADING_TYPE_ID 1)

                target_link_libraries(Lodestone.Threading INTERFACE TBB::tbb)
            endif ()
        elseif (THREADING_TYPE STREQUAL "STL-TBB" AND TBB_FOUND)
            find_package(TBB)

            if (TBB_FOUND)
                set(APPLIED_THREADING_TYPE "STL-TBB")
                set(APPLIED_THREADING_TYPE_ID 2)

                target_link_libraries(Lodestone.Threading INTERFACE TBB::tbb)
            endif ()
        elseif (THREADING_TYPE STREQUAL "OpenMP")
            find_package(OpenMP COMPONENTS C CXX)

            if (OpenMP_CXX_FOUND AND OpenMP_C_FOUND)
                set(APPLIED_THREADING_TYPE "OpenMP")
                set(APPLIED_THREADING_TYPE_ID 3)

                target_link_libraries(Lodestone.Threading INTERFACE OpenMP::OpenMP_CXX)
            endif ()
        elseif (THREADING_TYPE STREQUAL "STL")
            set(APPLIED_THREADING_TYPE "STL")
            set(APPLIED_THREADING_TYPE_ID 4)
        elseif (THREADING_TYPE STREQUAL "NONE")
            set(APPLIED_THREADING_TYPE "NONE")
            set(APPLIED_THREADING_TYPE_ID 0)
        endif()
    endif ()
endif()

message(STATUS "Using threading type ${APPLIED_THREADING_TYPE}")
target_compile_definitions(Lodestone.Threading INTERFACE
        LODESTONE_THREADING_TYPE=${APPLIED_THREADING_TYPE_ID}
)

unset(THREADING_TYPE CACHE)

target_include_directories(Lodestone.Threading
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

setupLinter(Lodestone.Threading)