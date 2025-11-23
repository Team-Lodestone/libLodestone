cmake_minimum_required(VERSION 3.30)
project(Lodestone.Converters)

# PROJECTS
add_subdirectory(Minecraft)

add_custom_target(Lodestone.Converters ALL DEPENDS
        Lodestone.Minecraft
)
