cmake_minimum_required(VERSION 3.30)
project(Lodestone.Converters.Minecraft)

set(NBT_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
        nbt++
        GIT_REPOSITORY https://github.com/Team-Lodestone/libnbtplusplus.git
        GIT_TAG master
)
FetchContent_MakeAvailable(nbt++)

# PROJECTS
add_subdirectory(Java)

add_custom_target(Lodestone.Minecraft ALL DEPENDS
        Lodestone.Java
)


