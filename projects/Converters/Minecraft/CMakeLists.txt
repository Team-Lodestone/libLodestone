cmake_minimum_required(VERSION 3.30)
project(Lodestone.Minecraft)

set(NBT_BUILD_TESTS OFF CACHE BOOL "" FORCE)
if (NOT TARGET nbt++)
    FetchContent_Declare(
            nbt++
            GIT_REPOSITORY https://github.com/Team-Lodestone/libnbtplusplus.git
            GIT_TAG master
    )
    FetchContent_MakeAvailable(nbt++)
endif()

# PROJECTS
add_subdirectory(Common)
add_subdirectory(Java)
add_subdirectory(Console)

add_custom_target(Lodestone.Minecraft ALL DEPENDS
        Lodestone.Minecraft.Java
        Lodestone.Minecraft.Console
        Lodestone.Minecraft.Common
)


